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

		// Collision related 
		float CalcAtk();
		float CalcDef();
		float CalcSlowdown();

		// Move Method
		void Move(int distance);

		// Position Getter Methods
		int GetX();
		int GetY();

		// Size Getter Method
		int GetSize();

		// Color Getter
		Pixel GetColor();

	private:
		Material material;
		float size;
		// Smoothness not needed as it only affects speed and acceleration. Obstacles are stationary.
		float density;
		float brittleness;
		float hardness;

		int pos_x;
		int pos_y;
	};
}