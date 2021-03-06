// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MetaScriptObject.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_MetaScriptObject_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_MetaScriptObject_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_MetaScriptObject_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_MetaScriptObject_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_MetaScriptObject_2eproto;
namespace Tiny3D {
namespace Script {
namespace MetaSystem {
class MetaData;
class MetaDataDefaultTypeInternal;
extern MetaDataDefaultTypeInternal _MetaData_default_instance_;
}  // namespace MetaSystem
}  // namespace Script
}  // namespace Tiny3D
PROTOBUF_NAMESPACE_OPEN
template<> ::Tiny3D::Script::MetaSystem::MetaData* Arena::CreateMaybeMessage<::Tiny3D::Script::MetaSystem::MetaData>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Tiny3D {
namespace Script {
namespace MetaSystem {

enum MetaData_FileType : int {
  MetaData_FileType_File = 0,
  MetaData_FileType_Dir = 1,
  MetaData_FileType_MetaData_FileType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  MetaData_FileType_MetaData_FileType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool MetaData_FileType_IsValid(int value);
constexpr MetaData_FileType MetaData_FileType_FileType_MIN = MetaData_FileType_File;
constexpr MetaData_FileType MetaData_FileType_FileType_MAX = MetaData_FileType_Dir;
constexpr int MetaData_FileType_FileType_ARRAYSIZE = MetaData_FileType_FileType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MetaData_FileType_descriptor();
template<typename T>
inline const std::string& MetaData_FileType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MetaData_FileType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MetaData_FileType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MetaData_FileType_descriptor(), enum_t_value);
}
inline bool MetaData_FileType_Parse(
    const std::string& name, MetaData_FileType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MetaData_FileType>(
    MetaData_FileType_descriptor(), name, value);
}
// ===================================================================

class MetaData :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Tiny3D.Script.MetaSystem.MetaData) */ {
 public:
  MetaData();
  virtual ~MetaData();

  MetaData(const MetaData& from);
  MetaData(MetaData&& from) noexcept
    : MetaData() {
    *this = ::std::move(from);
  }

  inline MetaData& operator=(const MetaData& from) {
    CopyFrom(from);
    return *this;
  }
  inline MetaData& operator=(MetaData&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const MetaData& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MetaData* internal_default_instance() {
    return reinterpret_cast<const MetaData*>(
               &_MetaData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(MetaData& a, MetaData& b) {
    a.Swap(&b);
  }
  inline void Swap(MetaData* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline MetaData* New() const final {
    return CreateMaybeMessage<MetaData>(nullptr);
  }

  MetaData* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MetaData>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const MetaData& from);
  void MergeFrom(const MetaData& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MetaData* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Tiny3D.Script.MetaSystem.MetaData";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_MetaScriptObject_2eproto);
    return ::descriptor_table_MetaScriptObject_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  typedef MetaData_FileType FileType;
  static constexpr FileType File =
    MetaData_FileType_File;
  static constexpr FileType Dir =
    MetaData_FileType_Dir;
  static inline bool FileType_IsValid(int value) {
    return MetaData_FileType_IsValid(value);
  }
  static constexpr FileType FileType_MIN =
    MetaData_FileType_FileType_MIN;
  static constexpr FileType FileType_MAX =
    MetaData_FileType_FileType_MAX;
  static constexpr int FileType_ARRAYSIZE =
    MetaData_FileType_FileType_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  FileType_descriptor() {
    return MetaData_FileType_descriptor();
  }
  template<typename T>
  static inline const std::string& FileType_Name(T enum_t_value) {
    static_assert(::std::is_same<T, FileType>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function FileType_Name.");
    return MetaData_FileType_Name(enum_t_value);
  }
  static inline bool FileType_Parse(const std::string& name,
      FileType* value) {
    return MetaData_FileType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kUuidFieldNumber = 1,
    kNameFieldNumber = 2,
    kTypeFieldNumber = 3,
  };
  // string uuid = 1;
  void clear_uuid();
  const std::string& uuid() const;
  void set_uuid(const std::string& value);
  void set_uuid(std::string&& value);
  void set_uuid(const char* value);
  void set_uuid(const char* value, size_t size);
  std::string* mutable_uuid();
  std::string* release_uuid();
  void set_allocated_uuid(std::string* uuid);
  private:
  const std::string& _internal_uuid() const;
  void _internal_set_uuid(const std::string& value);
  std::string* _internal_mutable_uuid();
  public:

  // string name = 2;
  void clear_name();
  const std::string& name() const;
  void set_name(const std::string& value);
  void set_name(std::string&& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  std::string* mutable_name();
  std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // .Tiny3D.Script.MetaSystem.MetaData.FileType type = 3;
  void clear_type();
  ::Tiny3D::Script::MetaSystem::MetaData_FileType type() const;
  void set_type(::Tiny3D::Script::MetaSystem::MetaData_FileType value);
  private:
  ::Tiny3D::Script::MetaSystem::MetaData_FileType _internal_type() const;
  void _internal_set_type(::Tiny3D::Script::MetaSystem::MetaData_FileType value);
  public:

  // @@protoc_insertion_point(class_scope:Tiny3D.Script.MetaSystem.MetaData)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr uuid_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  int type_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_MetaScriptObject_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MetaData

// string uuid = 1;
inline void MetaData::clear_uuid() {
  uuid_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& MetaData::uuid() const {
  // @@protoc_insertion_point(field_get:Tiny3D.Script.MetaSystem.MetaData.uuid)
  return _internal_uuid();
}
inline void MetaData::set_uuid(const std::string& value) {
  _internal_set_uuid(value);
  // @@protoc_insertion_point(field_set:Tiny3D.Script.MetaSystem.MetaData.uuid)
}
inline std::string* MetaData::mutable_uuid() {
  // @@protoc_insertion_point(field_mutable:Tiny3D.Script.MetaSystem.MetaData.uuid)
  return _internal_mutable_uuid();
}
inline const std::string& MetaData::_internal_uuid() const {
  return uuid_.GetNoArena();
}
inline void MetaData::_internal_set_uuid(const std::string& value) {
  
  uuid_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void MetaData::set_uuid(std::string&& value) {
  
  uuid_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Tiny3D.Script.MetaSystem.MetaData.uuid)
}
inline void MetaData::set_uuid(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  uuid_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Tiny3D.Script.MetaSystem.MetaData.uuid)
}
inline void MetaData::set_uuid(const char* value, size_t size) {
  
  uuid_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Tiny3D.Script.MetaSystem.MetaData.uuid)
}
inline std::string* MetaData::_internal_mutable_uuid() {
  
  return uuid_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* MetaData::release_uuid() {
  // @@protoc_insertion_point(field_release:Tiny3D.Script.MetaSystem.MetaData.uuid)
  
  return uuid_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void MetaData::set_allocated_uuid(std::string* uuid) {
  if (uuid != nullptr) {
    
  } else {
    
  }
  uuid_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), uuid);
  // @@protoc_insertion_point(field_set_allocated:Tiny3D.Script.MetaSystem.MetaData.uuid)
}

// string name = 2;
inline void MetaData::clear_name() {
  name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& MetaData::name() const {
  // @@protoc_insertion_point(field_get:Tiny3D.Script.MetaSystem.MetaData.name)
  return _internal_name();
}
inline void MetaData::set_name(const std::string& value) {
  _internal_set_name(value);
  // @@protoc_insertion_point(field_set:Tiny3D.Script.MetaSystem.MetaData.name)
}
inline std::string* MetaData::mutable_name() {
  // @@protoc_insertion_point(field_mutable:Tiny3D.Script.MetaSystem.MetaData.name)
  return _internal_mutable_name();
}
inline const std::string& MetaData::_internal_name() const {
  return name_.GetNoArena();
}
inline void MetaData::_internal_set_name(const std::string& value) {
  
  name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void MetaData::set_name(std::string&& value) {
  
  name_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Tiny3D.Script.MetaSystem.MetaData.name)
}
inline void MetaData::set_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Tiny3D.Script.MetaSystem.MetaData.name)
}
inline void MetaData::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Tiny3D.Script.MetaSystem.MetaData.name)
}
inline std::string* MetaData::_internal_mutable_name() {
  
  return name_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* MetaData::release_name() {
  // @@protoc_insertion_point(field_release:Tiny3D.Script.MetaSystem.MetaData.name)
  
  return name_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void MetaData::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:Tiny3D.Script.MetaSystem.MetaData.name)
}

// .Tiny3D.Script.MetaSystem.MetaData.FileType type = 3;
inline void MetaData::clear_type() {
  type_ = 0;
}
inline ::Tiny3D::Script::MetaSystem::MetaData_FileType MetaData::_internal_type() const {
  return static_cast< ::Tiny3D::Script::MetaSystem::MetaData_FileType >(type_);
}
inline ::Tiny3D::Script::MetaSystem::MetaData_FileType MetaData::type() const {
  // @@protoc_insertion_point(field_get:Tiny3D.Script.MetaSystem.MetaData.type)
  return _internal_type();
}
inline void MetaData::_internal_set_type(::Tiny3D::Script::MetaSystem::MetaData_FileType value) {
  
  type_ = value;
}
inline void MetaData::set_type(::Tiny3D::Script::MetaSystem::MetaData_FileType value) {
  _internal_set_type(value);
  // @@protoc_insertion_point(field_set:Tiny3D.Script.MetaSystem.MetaData.type)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace MetaSystem
}  // namespace Script
}  // namespace Tiny3D

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::Tiny3D::Script::MetaSystem::MetaData_FileType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Tiny3D::Script::MetaSystem::MetaData_FileType>() {
  return ::Tiny3D::Script::MetaSystem::MetaData_FileType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_MetaScriptObject_2eproto
