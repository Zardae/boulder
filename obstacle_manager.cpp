#include "obstacle_manager.h"
#include <corecrt_math.h>
#include <random>
#include "progression_manager.h"

namespace Boulder
{
	ObstacleManager obstacleManager;

	void ObstacleManager::Init()
	{
		// Reset obstacles array to dummy obstacles
		Obstacle dummy;
		for (int i = 0; i < 10; i++)
		{
			obstacles[i] = dummy;
		}
		obstacleAmount = 0;

		// Add 4 obstacles
		AddObstacle();
		AddObstacle();
		AddObstacle();
		AddObstacle();

		// Place obstacles further in the level
		obstacles[0].Move(300);
		obstacles[1].Move(200);
		obstacles[2].Move(100);

	}

	void ObstacleManager::OnTick(int distance)
	{
		for (int i = 0; i < obstacleAmount; i++)
		{
			obstacles[i].Move(distance);
		}

		// Try to add a new Obstacle if distance is large enough

		distanceSinceLast += distance;

		if (distanceSinceLast >= 100)
		{
			AddObstacle();
			distanceSinceLast = 0;
		}

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

	// Obstacle Management
	Obstacle* ObstacleManager::GetObstacles()
	{
		return obstacles;
	}

	int ObstacleManager::GetObstacleAmount()
	{
		return obstacleAmount;
	}


	void ObstacleManager::AddObstacle()
	{
		Obstacle obstacle = progressionManager.GenObstacle();
		obstacles[obstacleAmount] = obstacle;
		obstacleAmount++;
	}

	Obstacle ObstacleManager::RemoveObstacle()
	{
		Obstacle removed = obstacles[0];
		// Overwriting every obstacle with the next one.
		for (int i = 0; i < obstacleAmount - 1; i++)
		{
			obstacles[i] = obstacles[i + 1];
		}
		obstacleAmount--;
		return removed;
	}
}