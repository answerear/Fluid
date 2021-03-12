#ifndef __SCENE_DAMBREAK_H__
#define __SCENE_DAMBREAK_H__

#include <FluidPrerequisites.h>
#include "Scene/Scene.h"

namespace Fluid
{
	class FLUID_API SceneDamBreak : Scene
	{
	public:
		SceneDamBreak(const std::string& name) : Scene(name) {}
		virtual void Initialize(Solver* solver, SolverParams* solverParam);
	};
}

#endif  /*__SCENE_DAMBREAK_H__*/
