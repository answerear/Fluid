#include "PBF/SolverPBF.h"

namespace Fluid
{
	SolverPBF::SolverPBF()
	{

	}

	SolverPBF::~SolverPBF()
	{
		if (mOldPos != NULL) delete mOldPos;
		if (mNewPos != NULL) delete mNewPos;
		if (mVelocities != NULL) delete mVelocities;
		if (mPhases != NULL) delete mPhases;
		if (mDensities != NULL) delete mDensities;

		if (mDiffusePos != NULL) delete mDiffusePos;
		if (mDiffuseVelocities != NULL) delete mDiffuseVelocities;

		if (mNeighbors != NULL) delete mNeighbors;
		if (mNumNeighbors != NULL) delete mNumNeighbors;
		if (mGridCells != NULL) delete mGridCells;
		if (mGridCounters != NULL) delete mGridCounters;

		if (mDeltaPos != NULL) delete mDeltaPos;

		if (mBuffer0 != NULL) delete mBuffer0;
	}

	void SolverPBF::initialize(SolverParams* solverParams)
	{
		mOldPos = new Vector3[solverParams->numParticles];
		mNewPos = new Vector3[solverParams->numParticles];
		mVelocities = new Vector3[solverParams->numParticles];
		mPhases = new int32_t[solverParams->numParticles];
		mDensities = new Real[solverParams->numParticles];

		mDiffusePos = new Vector3[solverParams->numDiffuse];
		mDiffuseVelocities = new Vector3[solverParams->numDiffuse];

		mNeighbors = new int32_t[solverParams->maxNeighbors * solverParams->numParticles];
		mNumNeighbors = new int32_t[solverParams->numParticles];
		mGridCells = new int32_t[solverParams->maxParticles * solverParams->gridSize];
		mGridCounters = new int32_t[solverParams->gridSize];

		mDeltaPos = new Vector3[solverParams->numParticles];

		mBuffer0 = new Real[solverParams->numParticles];
	}

	void SolverPBF::update(SolverParams* solverParam)
	{

	}

	float SolverPBF::WPoly6(const Vector3& pi, const Vector3& pj)
	{
		Vector3 r = pi - pj;
		Real rLen = r.length();
		if (rLen > mSolverParams.radius || rLen == 0)
			return .0;

		return mSolverParams.KPOLY * pow((mSolverParams.radius * mSolverParams.radius - pow(rLen, 2)), 3);
	}

	Vector3 SolverPBF::WSpiky(const Vector3& pi, const Vector3& pj)
	{
		Vector3 r = pi - pj;
		Real rLen = r.length();
		if (rLen > mSolverParams.radius || rLen == 0)
			return Vector3(.0);

		Real coeff = (mSolverParams.radius - rLen) * (mSolverParams.radius - rLen);
		coeff *= mSolverParams.SPIKY;
		coeff /= rLen;
		return r * -coeff;
	}

	Real SolverPBF::sCorrCalc(const Vector3& pi, const Vector3& pj)
	{
		//Get Density from WPoly6
		float corr = WPoly6(Vector3(pi), Vector3(pj)) / mSolverParams.wQH;
		corr *= corr * corr * corr;
		return -mSolverParams.K * corr;
	}

	Vector3 SolverPBF::eta(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, int32_t& index, Real& vorticityMag)
	{
		Vector3 eta = Vector3(.0f);
		for (int i = 0; i < numNeighbors[index]; ++i)
		{
			if (phases[neighbors[(index * mSolverParams.maxNeighbors) + i]] == 0)
				eta += WSpiky(Vector3(newPos[index]), Vector3(newPos[neighbors[(index * mSolverParams.maxNeighbors) + i]])) * vorticityMag;
		}

		return eta;
	}



	void SolverPBF::calcDensities(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Real* densities)
	{
		for (int32_t i = 0; i < mSolverParams.numParticles; ++i)
		{
			if (phases[i] != 0)
				continue;

			Real rhoSum = 0.0f;
			for (int32_t j = 0; j < numNeighbors[i]; ++j)
			{
				if (phases[neighbors[(i * mSolverParams.maxNeighbors) + j]] == 0)
					rhoSum += WPoly6(Vector3(newPos[i]), Vector3(newPos[neighbors[(i * mSolverParams.maxNeighbors) + j]]));
			}

			densities[i] = rhoSum;
		}
	}

	void SolverPBF::calcLambda(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Real* densities, Real* buffer0)
	{
		for (int32_t i = 0; i < mSolverParams.numParticles; ++i)
		{
			if (phases[i] != 0)
				continue;

			Real densityConstraint = (densities[i] / mSolverParams.restDensity) - 1;
			Vector3 gradientI = Vector3(Real(0.0f));
			Real sumGradients = 0.0f;
			for (int32_t j = 0; j < numNeighbors[i]; j++)
			{
				if (phases[neighbors[(i * mSolverParams.maxNeighbors) + j]] == 0)
				{
					//Calculate gradient with respect to j
					Vector3 gradientJ = WSpiky(Vector3(newPos[i]), Vector3(newPos[neighbors[(i * mSolverParams.maxNeighbors) + j]])) / mSolverParams.restDensity;

					//Add magnitude squared to sum
					sumGradients += pow(gradientJ.length(), 2);
					gradientI += gradientJ;
				}
			}

			//Add the particle i gradient magnitude squared to sum
			sumGradients = sumGradients + pow(gradientI.length(), 2);
			buffer0[i] = (-1 * densityConstraint) / (sumGradients + mSolverParams.lambdaEps);
		}
	}

	void SolverPBF::calcDeltaPos(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Vector3* deltaPs, Real* buffer0)
	{
		for (int32_t i = 0; i < mSolverParams.numParticles; ++i)
		{
			if (phases[i] != 0)
				continue;

			deltaPs[i] = Vector3(0);

			Vector3 deltaP = Vector3(0.0f);
			for (int j = 0; j < numNeighbors[i]; j++)
			{
				if (phases[neighbors[(i * mSolverParams.maxNeighbors) + j]] == 0)
				{
					float lambdaSum = buffer0[i] + buffer0[neighbors[(i * mSolverParams.maxNeighbors) + j]];
					float sCorr = sCorrCalc(newPos[i], newPos[neighbors[(i * mSolverParams.maxNeighbors) + j]]);
					deltaP += WSpiky(Vector3(newPos[i]), Vector3(newPos[neighbors[(i * mSolverParams.maxNeighbors) + j]])) * (lambdaSum + sCorr);

				}
			}

			deltaPs[i] = deltaP / mSolverParams.restDensity;
		}
	}

	void SolverPBF::applyDeltaPos(Vector3* newPos, Vector3* deltaPos, Real* buffer0, int32_t flag)
	{
		for (int32_t i = 0; i < mSolverParams.numParticles; ++i)
		{
			if (buffer0[i] > 0 && flag == 1)
				newPos[i] += Vector3(deltaPos[i] / buffer0[i]);
			else if (flag == 0)
				newPos[i] += Vector3(deltaPos[i]);
		}
	}

	void SolverPBF::updateVelocities(Vector3* oldPos, Vector3* newPos, Vector3* velocities, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Vector3* deltaPos)
	{
		for (int32_t i = 0; i < mSolverParams.numParticles; ++i)
		{
			if (phases[i] != 0)
				continue;

			//set new velocity vi = (x*i - xi) / dt
			velocities[i] = (Vector3(newPos[i]) - Vector3(oldPos[i])) / deltaT;

			//apply vorticity confinement
			velocities[i] += vorticityForce(newPos, velocities, phases, neighbors, numNeighbors, i) * deltaT;

			//apply XSPH viscosity
			deltaPos[i] = xsphViscosity(newPos, velocities, phases, neighbors, numNeighbors, i);

			//update position xi = x*i
			oldPos[i] = newPos[i];
		}
	}

	Vector3 SolverPBF::vorticityForce(Vector3* newPos, Vector3* velocities, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, int32_t index)
	{
		//Calculate omega_i
		Vector3 omega = Vector3(0.0f);
		Vector3 velocityDiff;
		Vector3 gradient;

		for (int i = 0; i < numNeighbors[index]; i++)
		{
			if (phases[neighbors[(index * mSolverParams.maxNeighbors) + i]] == 0)
			{
				velocityDiff = velocities[neighbors[(index * mSolverParams.maxNeighbors) + i]] - velocities[index];
				gradient = WSpiky(Vector3(newPos[index]), Vector3(newPos[neighbors[(index * mSolverParams.maxNeighbors) + i]]));
				omega += velocityDiff.cross(gradient);
			}
		}

		float omegaLength = omega.length();
		if (omegaLength == 0.0f) {
			//No direction for eta
			return Vector3(0.0f);
		}

		Vector3 etaVal = eta(newPos, phases, neighbors, numNeighbors, index, omegaLength);
		if (etaVal.x() == 0 && etaVal.y() == 0 && etaVal.z() == 0)
		{
			//Particle is isolated or net force is 0
			return Vector3(0.0f);
		}
		
		Vector3 n = etaVal.normalize();

		return (n.cross(omega) * mSolverParams.vorticityEps);
	}

	Vector3 SolverPBF::xsphViscosity(Vector3* newPos, Vector3* velocities, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, int32_t index)
	{
		Vector3 visc = Vector3(0.0f);
		for (int i = 0; i < numNeighbors[index]; i++)
		{
			if (phases[neighbors[(index * mSolverParams.maxNeighbors) + i]] == 0)
			{
				Vector3 velocityDiff = velocities[neighbors[(index * mSolverParams.maxNeighbors) + i]] - velocities[index];
				velocityDiff *= WPoly6(Vector3(newPos[index]), Vector3(newPos[neighbors[(index * mSolverParams.maxNeighbors) + i]]));
				visc += velocityDiff;
			}
		}

		return visc * mSolverParams.C;
	}

}
