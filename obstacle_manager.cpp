#include "obstacle_manager.h"
#include <corecrt_math.h>

namespace Boulder
{
	void ObstacleManager::Init()
	{

	}

	void ObstacleManager::OnTick(float deltaTime, float playerSpeed)
	{

	}

	bool ObstacleManager::Collided(int centerX, int centerY, int radius)
	{
		Obstacle first = obstacles[0];

		if (first.GetX() <= centerX)
		{
			// Edge case Boulder is too fast to register a collision
			return true;
		}
		else if (first.GetY() >= centerY && first.GetX() <= centerX + radius)
		{
			// Edge case Obstacle is too large to detect a collision with it's X and Y values
			return true;
		}
		else if (pow((centerX - first.GetX()), 2) + pow((centerY - first.GetY()), 2) <= pow(radius, 2))
		{
			// Obstacle popsition (upper left corner) intersects with the boulder
			return true;
		}
		
		return false;
	}
}