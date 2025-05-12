#pragma once
#include "obstacle.h"
#include "material_manager.h"

namespace Boulder
{
	class ObstacleManager
	{
	public:
		void Init(MaterialManager materialManager);
		void OnTick(int distance, MaterialManager materialManager);
		bool Collided(int centerX, int centerY, int radius);
		
		// Obstacle Management
		void AddObstacle(MaterialManager materialManager);
		void RemoveObstacle();

	private:
		int obstacle_amount = 0;
		Obstacle obstacles[10];

		// Obstacle generation related
		int distanceSinceLast = 0;
		int maxSize = 10;
	};
}