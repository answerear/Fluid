#ifndef __PARTICLE_SYSTEM_H__
#define  __PARTICLE_SYSTEM_H__

#include "FluidPrerequisites.h"

namespace Fluid
{
	class FLUID_API ParticleSystem
	{
	protected:
		bool mRunning;
		bool mMoveWall;

	public:
		ParticleSystem();
		~ParticleSystem();

		void initialize();
		void updateWrapper();
		void getPositions();
		void getDiffuse();

	protected:
		int getIndex(Real i, Real j);
		float easeInOutQuad(Real t, Real b, Real c, Real d);
	};
}

#endif  /*__PARTICLE_SYSTEM_H__*/
