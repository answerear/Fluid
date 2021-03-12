#ifndef __SOLVER_PARAM_H__
#define __SOLVER_PARAM_H__

#include <FluidPrerequisites.h>

namespace Fluid
{
	struct FLUID_API SolverParams
	{
		int32_t maxNeighbors;
		int32_t maxParticles;
		int32_t maxContacts;
		int32_t gridWidth, gridHeight, gridDepth;
		int32_t gridSize;

		int32_t numParticles;
		int32_t numDiffuse;

		Vector3 gravity;
		Vector3 bounds;

		int32_t numIterations;
		Real radius;

		Real KPOLY;
		Real SPIKY;
		Real restDensity;
		Real lambdaEps;
		Real vorticityEps;
		Real C;
		Real K;
		Real dqMag;
		Real wQH;
	};
}

#endif  /*__SOLVER_PARAM_H__*/
