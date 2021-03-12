#ifndef __FOAM_PARTICLE_H__
#define __FOAM_PARTICLE_H__

#include "FluidPrerequisites.h"

namespace Fluid
{
	struct FLUID_API FoamParticle
	{
		Vector3 pos;
		Vector3 velocity;
		Real ttl;
		int32_t type; // Spray, Foam, Bubble
	};
}

#endif  /*__FOAM_PARTICLE_H__*/