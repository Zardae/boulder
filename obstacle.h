#pragma once
#include "material.h"

//
// Defines the obstacles
//

namespace Boulder
{
	class Obstacle
	{
	public:
		Obstacle();
		Obstacle(Material pmaterial, float psize);

		float CalcAtk();
		float CalcDef();
		float CalcSlowdown();

	private:
		Material material;
		float size;
		// Smoothness not needed as it only affects speed and acceleration. Obstacles are stationary.
		float density;
		float brittleness;
		float hardness;
	};
}