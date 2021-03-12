#ifndef __SCENE_H__
#define __SCENE_H__

#include <FluidPrerequisites.h>
#include "Solver/Solver.h"
#include "Solver/SolverParams.h"

namespace Fluid
{
	class FLUID_API Scene
	{
	public:
		Scene(const std::string& name) : mName(name) {}
		virtual void Initialize(Solver* solver, SolverParams* solverParam) = 0;

	private:
		std::string mName;
	};
}


#endif  /*__SCENE_H__*/
