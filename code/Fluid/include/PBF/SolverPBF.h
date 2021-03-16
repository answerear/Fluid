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

		Real WPoly6(const Vector3& pi, const Vector3& pj);
		Vector3 WSpiky(const Vector3& pi, const Vector3& pj);
		Real sCorrCalc(const Vector3& pi, const Vector3& pj);
		Vector3 eta(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, int32_t& index, Real& vorticityMag);

		void calcDensities(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Real* densities);
		void calcLambda(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Real* densities, Real* buffer0);
		void calcDeltaPos(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Vector3* deltaPs, Real* buffer0);
		void applyDeltaPos(Vector3* newPos, Vector3* deltaPos, Real* buffer0, int32_t flag);
		void updateVelocities(Vector3* oldPos, Vector3* newPos, Vector3* velocities, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Vector3* deltaPos);
		Vector3 vorticityForce(Vector3* newPos, Vector3* velocities, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, int32_t index);
		Vector3 xsphViscosity(Vector3* newPos, Vector3* velocities, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, int32_t index);
	private:
		SolverParams mSolverParams;
		Real deltaT = 0.0083f;
	};
}


#endif  /*__SOLVER_PBF_H__*/
