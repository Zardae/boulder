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

		// Material Getter
		Material GetMaterial();

		// Size Getter
		int GetSize();

		// Reward Getter
		int GetReward();

		// Color Getter
		Pixel GetColor();

	private:
		Material material;
		float size;
		// Smoothness not needed as it only affects speed and acceleration. Obstacles are stationary.
		float density;
		float brittleness;
		float hardness;

		// Reward
		int reward;


		int pos_x;
		int pos_y;
	};
}