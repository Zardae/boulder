#include "obstacle_manager.h"
#include <corecrt_math.h>
#include <random>

namespace Boulder
{
	void ObstacleManager::Init(MaterialManager materialManager)
	{
		// Reset obstacles array to dummy obstacles
		Obstacle dummy;
		for (int i = 0; i < 10; i++)
		{
			obstacles[i] = dummy;
		}
		obstacleAmount = 0;

		// Add 2 obstacles
		AddObstacle(materialManager);
		AddObstacle(materialManager);

		// Place first obstacle 10 pixels in front
		obstacles[0].Move(100);

	}

	void ObstacleManager::OnTick(int distance, MaterialManager materialManager)
	{
		for (int i = 0; i < obstacleAmount; i++)
		{
			obstacles[i].Move(distance);
		}

		distanceSinceLast += distance;

		if (distanceSinceLast >= 80)
		{
			AddObstacle(materialManager);
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


	void ObstacleManager::AddObstacle(MaterialManager materialManager)
	{
		// Size generation
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(5, maxSize);
		int rnd = distr(gen);
		Material material = materialManager.GetMaterial(materialManager.GetObstacleType());

		Obstacle obstacle(material, rnd);
		obstacles[obstacleAmount] = obstacle;
		obstacleAmount++;
	}

	void ObstacleManager::RemoveObstacle()
	{
		// Overwriting every obstacle with the next one.
		for (int i = 0; i < obstacleAmount - 1; i++)
		{
			obstacles[i] = obstacles[i + 1];
		}
		obstacleAmount--;
	}
}