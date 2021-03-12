#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "FluidPrerequisites.h"

namespace Fluid
{
	struct FLUID_API Particle
	{
		Vector3 oldPos;
		Vector3 newPos;
		Vector3 velocity;

		Real invMass;
		int32_t phase;
	};
}

#endif  /*__PARTICLE_H__*/