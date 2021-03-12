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

    void SolverPBF::calcDensities(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Real* densities)
    {

    }

    void SolverPBF::calcLambda(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Real* densities, Real* buffer0)
    {

    }

    void SolverPBF::calcDeltaPos(Vector3* newPos, int32_t* phases, int32_t* neighbors, int32_t* numNeighbors, Vector3* deltaPs, Real* buffer0)
    {

    }
}
