// Copyright (c) 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "source/fuzz/fuzzer.h"

#include <cassert>
#include <memory>

#include "source/fuzz/fact_manager/fact_manager.h"
#include "source/fuzz/fuzzer_context.h"
#include "source/fuzz/fuzzer_pass_add_access_chains.h"
#include "source/fuzz/fuzzer_pass_add_composite_inserts.h"
#include "source/fuzz/fuzzer_pass_add_composite_types.h"
#include "source/fuzz/fuzzer_pass_add_copy_memory.h"
#include "source/fuzz/fuzzer_pass_add_dead_blocks.h"
#include "source/fuzz/fuzzer_pass_add_dead_breaks.h"
#include "source/fuzz/fuzzer_pass_add_dead_continues.h"
#include "source/fuzz/fuzzer_pass_add_equation_instructions.h"
#include "source/fuzz/fuzzer_pass_add_function_calls.h"
#include "source/fuzz/fuzzer_pass_add_global_variables.h"
#include "source/fuzz/fuzzer_pass_add_image_sample_unused_components.h"
#include "source/fuzz/fuzzer_pass_add_loads.h"
#include "source/fuzz/fuzzer_pass_add_local_variables.h"
#include "source/fuzz/fuzzer_pass_add_loop_preheaders.h"
#include "source/fuzz/fuzzer_pass_add_no_contraction_decorations.h"
#include "source/fuzz/fuzzer_pass_add_opphi_synonyms.h"
#include "source/fuzz/fuzzer_pass_add_parameters.h"
#include "source/fuzz/fuzzer_pass_add_relaxed_decorations.h"
#include "source/fuzz/fuzzer_pass_add_stores.h"
#include "source/fuzz/fuzzer_pass_add_synonyms.h"
#include "source/fuzz/fuzzer_pass_add_vector_shuffle_instructions.h"
#include "source/fuzz/fuzzer_pass_adjust_branch_weights.h"
#include "source/fuzz/fuzzer_pass_adjust_function_controls.h"
#include "source/fuzz/fuzzer_pass_adjust_loop_controls.h"
#include "source/fuzz/fuzzer_pass_adjust_memory_operands_masks.h"
#include "source/fuzz/fuzzer_pass_adjust_selection_controls.h"
#include "source/fuzz/fuzzer_pass_apply_id_synonyms.h"
#include "source/fuzz/fuzzer_pass_construct_composites.h"
#include "source/fuzz/fuzzer_pass_copy_objects.h"
#include "source/fuzz/fuzzer_pass_donate_modules.h"
#include "source/fuzz/fuzzer_pass_inline_functions.h"
#include "source/fuzz/fuzzer_pass_interchange_signedness_of_integer_operands.h"
#include "source/fuzz/fuzzer_pass_interchange_zero_like_constants.h"
#include "source/fuzz/fuzzer_pass_invert_comparison_operators.h"
#include "source/fuzz/fuzzer_pass_make_vector_operations_dynamic.h"
#include "source/fuzz/fuzzer_pass_merge_blocks.h"
#include "source/fuzz/fuzzer_pass_mutate_pointers.h"
#include "source/fuzz/fuzzer_pass_obfuscate_constants.h"
#include "source/fuzz/fuzzer_pass_outline_functions.h"
#include "source/fuzz/fuzzer_pass_permute_blocks.h"
#include "source/fuzz/fuzzer_pass_permute_function_parameters.h"
#include "source/fuzz/fuzzer_pass_permute_instructions.h"
#include "source/fuzz/fuzzer_pass_permute_phi_operands.h"
#include "source/fuzz/fuzzer_pass_propagate_instructions_up.h"
#include "source/fuzz/fuzzer_pass_push_ids_through_variables.h"
#include "source/fuzz/fuzzer_pass_replace_adds_subs_muls_with_carrying_extended.h"
#include "source/fuzz/fuzzer_pass_replace_copy_memories_with_loads_stores.h"
#include "source/fuzz/fuzzer_pass_replace_copy_objects_with_stores_loads.h"
#include "source/fuzz/fuzzer_pass_replace_irrelevant_ids.h"
#include "source/fuzz/fuzzer_pass_replace_linear_algebra_instructions.h"
#include "source/fuzz/fuzzer_pass_replace_loads_stores_with_copy_memories.h"
#include "source/fuzz/fuzzer_pass_replace_opphi_ids_from_dead_predecessors.h"
#include "source/fuzz/fuzzer_pass_replace_parameter_with_global.h"
#include "source/fuzz/fuzzer_pass_replace_params_with_struct.h"
#include "source/fuzz/fuzzer_pass_split_blocks.h"
#include "source/fuzz/fuzzer_pass_swap_commutable_operands.h"
#include "source/fuzz/fuzzer_pass_swap_conditional_branch_operands.h"
#include "source/fuzz/fuzzer_pass_toggle_access_chain_instruction.h"
#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/fuzz/pseudo_random_generator.h"
#include "source/fuzz/transformation_context.h"
#include "source/opt/build_module.h"
#include "source/spirv_fuzzer_options.h"
#include "source/util/make_unique.h"

namespace spvtools {
namespace fuzz {

namespace {
const uint32_t kIdBoundGap = 100;

const uint32_t kTransformationLimit = 500;

const uint32_t kChanceOfApplyingAnotherPass = 85;

// A convenience method to add a fuzzer pass to |passes| with probability 0.5.
// All fuzzer passes take |ir_context|, |transformation_context|,
// |fuzzer_context| and |transformation_sequence_out| as parameters.  Extra
// arguments can be provided via |extra_args|.
template <typename T, typename... Args>
void MaybeAddPass(
    std::vector<std::unique_ptr<FuzzerPass>>* passes,
    opt::IRContext* ir_context, TransformationContext* transformation_context,
    FuzzerContext* fuzzer_context,
    protobufs::TransformationSequence* transformation_sequence_out,
    Args&&... extra_args) {
  if (fuzzer_context->ChooseEven()) {
    passes->push_back(MakeUnique<T>(ir_context, transformation_context,
                                    fuzzer_context, transformation_sequence_out,
                                    std::forward<Args>(extra_args)...));
  }
}

}  // namespace

Fuzzer::Fuzzer(spv_target_env target_env, uint32_t seed,
               bool validate_after_each_fuzzer_pass,
               spv_validator_options validator_options)
    : target_env_(target_env),
      seed_(seed),
      validate_after_each_fuzzer_pass_(validate_after_each_fuzzer_pass),
      validator_options_(validator_options) {}

Fuzzer::~Fuzzer() = default;

void Fuzzer::SetMessageConsumer(MessageConsumer consumer) {
  consumer_ = std::move(consumer);
}

bool Fuzzer::ApplyPassAndCheckValidity(
    FuzzerPass* pass, const opt::IRContext& ir_context,
    const spvtools::SpirvTools& tools) const {
  pass->Apply();
  if (validate_after_each_fuzzer_pass_) {
    std::vector<uint32_t> binary_to_validate;
    ir_context.module()->ToBinary(&binary_to_validate, false);
    if (!tools.Validate(&binary_to_validate[0], binary_to_validate.size(),
                        validator_options_)) {
      consumer_(SPV_MSG_INFO, nullptr, {},
                "Binary became invalid during fuzzing (set a breakpoint to "
                "inspect); stopping.");
      return false;
    }
  }
  return true;
}

Fuzzer::FuzzerResultStatus Fuzzer::Run(
    const std::vector<uint32_t>& binary_in,
    const protobufs::FactSequence& initial_facts,
    const std::vector<fuzzerutil::ModuleSupplier>& donor_suppliers,
    std::vector<uint32_t>* binary_out,
    protobufs::TransformationSequence* transformation_sequence_out) const {
  // Check compatibility between the library version being linked with and the
  // header files being used.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  spvtools::SpirvTools tools(target_env_);
  tools.SetMessageConsumer(consumer_);
  if (!tools.IsValid()) {
    consumer_(SPV_MSG_ERROR, nullptr, {},
              "Failed to create SPIRV-Tools interface; stopping.");
    return Fuzzer::FuzzerResultStatus::kFailedToCreateSpirvToolsInterface;
  }

  // Initial binary should be valid.
  if (!tools.Validate(&binary_in[0], binary_in.size(), validator_options_)) {
    consumer_(SPV_MSG_ERROR, nullptr, {},
              "Initial binary is invalid; stopping.");
    return Fuzzer::FuzzerResultStatus::kInitialBinaryInvalid;
  }

  // Build the module from the input binary.
  std::unique_ptr<opt::IRContext> ir_context =
      BuildModule(target_env_, consumer_, binary_in.data(), binary_in.size());
  assert(ir_context);

  // Make a PRNG from the seed passed to the fuzzer on creation.
  PseudoRandomGenerator random_generator(seed_);

  // The fuzzer will introduce new ids into the module.  The module's id bound
  // gives the smallest id that can be used for this purpose.  We add an offset
  // to this so that there is a sizeable gap between the ids used in the
  // original module and the ids used for fuzzing, as a readability aid.
  //
  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/2541) consider the
  //  case where the maximum id bound is reached.
  auto minimum_fresh_id = ir_context->module()->id_bound() + kIdBoundGap;
  FuzzerContext fuzzer_context(&random_generator, minimum_fresh_id);

  FactManager fact_manager;
  fact_manager.AddFacts(consumer_, initial_facts, ir_context.get());
  TransformationContext transformation_context(&fact_manager,
                                               validator_options_);

  // Apply some semantics-preserving passes.
  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3764): Enable
  //  certain passes to run with a higher priority than the others.
  std::vector<std::unique_ptr<FuzzerPass>> passes;
  while (passes.empty()) {
    MaybeAddPass<FuzzerPassAddAccessChains>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddCompositeInserts>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddCompositeTypes>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddCopyMemory>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddDeadBlocks>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddDeadBreaks>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddDeadContinues>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddEquationInstructions>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddFunctionCalls>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddGlobalVariables>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddImageSampleUnusedComponents>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddLoads>(&passes, ir_context.get(),
                                     &transformation_context, &fuzzer_context,
                                     transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddLocalVariables>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddLoopPreheaders>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddOpPhiSynonyms>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddParameters>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddRelaxedDecorations>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddStores>(&passes, ir_context.get(),
                                      &transformation_context, &fuzzer_context,
                                      transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddSynonyms>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassAddVectorShuffleInstructions>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassApplyIdSynonyms>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassConstructComposites>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassCopyObjects>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassDonateModules>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out, donor_suppliers);
    MaybeAddPass<FuzzerPassInlineFunctions>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassInvertComparisonOperators>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassMakeVectorOperationsDynamic>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassMergeBlocks>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassMutatePointers>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassObfuscateConstants>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassOutlineFunctions>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassPermuteBlocks>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassPermuteFunctionParameters>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassPermuteInstructions>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassPropagateInstructionsUp>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassPushIdsThroughVariables>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassReplaceAddsSubsMulsWithCarryingExtended>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassReplaceCopyMemoriesWithLoadsStores>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassReplaceCopyObjectsWithStoresLoads>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassReplaceLoadsStoresWithCopyMemories>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassReplaceParameterWithGlobal>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassReplaceLinearAlgebraInstructions>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassReplaceParamsWithStruct>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassSplitBlocks>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
    MaybeAddPass<FuzzerPassSwapBranchConditionalOperands>(
        &passes, ir_context.get(), &transformation_context, &fuzzer_context,
        transformation_sequence_out);
  }

  bool is_first = true;
  while (static_cast<uint32_t>(
             transformation_sequence_out->transformation_size()) <
             kTransformationLimit &&
         (is_first ||
          fuzzer_context.ChoosePercentage(kChanceOfApplyingAnotherPass))) {
    is_first = false;
    if (!ApplyPassAndCheckValidity(
            passes[fuzzer_context.RandomIndex(passes)].get(), *ir_context,
            tools)) {
      return Fuzzer::FuzzerResultStatus::kFuzzerPassLedToInvalidModule;
    }
  }

  // Now apply some passes that it does not make sense to apply repeatedly,
  // as they do not unlock other passes.
  std::vector<std::unique_ptr<FuzzerPass>> final_passes;
  MaybeAddPass<FuzzerPassAdjustBranchWeights>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassAdjustFunctionControls>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassAdjustLoopControls>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassAdjustMemoryOperandsMasks>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassAdjustSelectionControls>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassAddNoContractionDecorations>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassInterchangeSignednessOfIntegerOperands>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassInterchangeZeroLikeConstants>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassPermutePhiOperands>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassReplaceOpPhiIdsFromDeadPredecessors>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassReplaceIrrelevantIds>(
      &passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassSwapCommutableOperands>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  MaybeAddPass<FuzzerPassToggleAccessChainInstruction>(
      &final_passes, ir_context.get(), &transformation_context, &fuzzer_context,
      transformation_sequence_out);
  for (auto& pass : final_passes) {
    if (!ApplyPassAndCheckValidity(pass.get(), *ir_context, tools)) {
      return Fuzzer::FuzzerResultStatus::kFuzzerPassLedToInvalidModule;
    }
  }

  // Encode the module as a binary.
  ir_context->module()->ToBinary(binary_out, false);

  return Fuzzer::FuzzerResultStatus::kComplete;
}

}  // namespace fuzz
}  // namespace spvtools
