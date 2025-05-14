#include "progression_manager.h"
#include <corecrt_math.h>
#include <random>
#include "material_manager.h"

namespace Boulder
{
	ProgressionManager progressionManager;

	void ProgressionManager::ResetRun()
	{
		runDifficulty = 0;
	}

	void ProgressionManager::IncreaseBaseDifficulty()
	{
		baseDifficulty++;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				obstacleSizes[i][j] += 2;
			}
		}
	}

	void ProgressionManager::DecreaseBaseDifficulty()
	{
		baseDifficulty--;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				obstacleSizes[i][j] -= 2;
			}
		}
	}

	void ProgressionManager::IncreaseSelectionLevel()
	{
		selectionLevel++;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				selectionSizes[i][j] += 2;
			}
		}
	}

	void ProgressionManager::DecreaseSelectionLevel()
	{
		if (selectionLevel == 1)
		{
			// Guard clause against decreasing the selection level too far
			return;
		}
		selectionLevel--;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				selectionSizes[i][j] -= 2;
			}
		}
	}

	void ProgressionManager::ChangeWeight(Material::RockType type, int value)
	{
		// type can be used here as the weights are in the same order as the enum declaration
		selectionWeights[type] += value;
	}


	void ProgressionManager::IncreaseRunDifficulty()
	{
		runDifficulty++;
	}

	Obstacle ProgressionManager::GenObstacle()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		// Generate Type
		std::discrete_distribution<> distrType({
			obstacleWeights[0],
			obstacleWeights[1],
			obstacleWeights[2],
			obstacleWeights[3],
			obstacleWeights[4],
		});

		Material::RockType rockType = static_cast<Material::RockType>(distrType(gen));	// According to a stack overflow answer
																						// the static cast is dangerous, but I
																						// was unable to find something better as of yet

		Material* material = materialManager.GetMaterial(rockType);
		// Generate Size
		std::uniform_int_distribution<> distrSize(obstacleSizes[rockType][0], obstacleSizes[rockType][1]);
		int size = distrSize(gen);

		// Increase size realted to the run difficulty
		size = (int)size * pow(1.05, runDifficulty);

		// Cap size at 80
		if (size > 80)
		{
			size = 80;
		}

		Obstacle ret(material, size);
		return ret;
	}

	Material* ProgressionManager::GenBoulderMaterial()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::discrete_distribution<> distr({
			selectionWeights[0],
			selectionWeights[1],
			selectionWeights[2],
			selectionWeights[3],
			selectionWeights[4]
			});
		
		Material::RockType rockType = static_cast<Material::RockType>(distr(gen));
		Material* material = materialManager.GetMaterial(rockType);
		return material;
	}

	int ProgressionManager::GenBoulderSize(Material* material)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		// WTF
		int i = material->GetRockType();

		std::uniform_int_distribution<> distr(selectionSizes[i][0], selectionSizes[i][1]);

		return distr(gen);
	}

}