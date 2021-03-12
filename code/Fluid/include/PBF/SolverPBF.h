#ifndef __SOLVER_PBF_H__
#define __SOLVER_PBF_H__

#include <FluidPrerequisites.h>
#include "Solver/Solver.h"
#include "Solver/SolverParams.h"

namespace Fluid
{
	class FLUID_API SolverPBF : Solver
	{
	public:
		SolverPBF();
		virtual ~SolverPBF();

		virtual void initialize(SolverParams* solverParam);
		virtual void update(SolverParams* solverParam);

	private:
		void calcDensities(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Real* densities);
		void calcLambda(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Real* densities, Real* buffer0);
		void calcDeltaPos(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Vector3* deltaPs, Real* buffer0);
	};
}


#endif  /*__SOLVER_PBF_H__*/
