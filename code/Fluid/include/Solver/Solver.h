#ifndef __SOLVER_H__
#define __SOLVER_H__


#include <FluidPrerequisites.h>

namespace Fluid
{
	class FLUID_API Solver 
	{
	public:
		virtual void initialize(SolverParams* solverParam) = 0;
		virtual void update(SolverParams* solverParam) = 0;

		//void createParticles(SolverParams* solverParam);

	protected:
		// particle info
		Vector3* mOldPos;
		Vector3* mNewPos;
		Vector3* mVelocities;
		int32_t* mPhases;
		Real* mDensities;

		// diffuse info
		Vector3* mDiffusePos;
		Vector3* mDiffuseVelocities;

		// neighbor finding
		int32_t* mNeighbors;
		int32_t* mNumNeighbors;
		int32_t* mGridCells;
		int32_t* mGridCounters;

		Vector3* mDeltaPos;

		Real* mBuffer0;
	};
}

#endif  /*__SOLVER_H__*/
