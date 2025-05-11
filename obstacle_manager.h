#pragma once
#include "obstacle.h"

namespace Boulder
{
	class ObstacleManager
	{
	public:
		void Init();
		void OnTick(float deltaTime, float playerSpeed);
		bool Collided(int centerX, int centerY, int radius);

	private:
		int obstacle_amount = 0;
		Obstacle obstacles[10];
	};
}