#pragma once
#include "obstacle.h"
#include "material_manager.h"

namespace Boulder
{
	class ObstacleManager
	{
	public:
		void Init();
		void OnTick(int distance);
		bool Collided(int centerX, int centerY, int radius);
		
		// Obstacle Management
		Obstacle* GetObstacles();
		int GetObstacleAmount();
		void AddObstacle();
		Obstacle RemoveObstacle();

	private:
		int obstacleAmount = 0;
		Obstacle obstacles[10];

		// Obstacle generation related
		int distanceSinceLast = 0;
		int minSize = 10;
		int maxSize = 20; 
	};

	extern ObstacleManager obstacleManager;
}