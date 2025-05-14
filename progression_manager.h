#pragma once
#include "material.h"
#include "obstacle.h"



namespace Boulder
{
	class ProgressionManager
	{
	public:
		// Resets temporary changes
		void ResetRun();

		// Base difficulty management
		void IncreaseBaseDifficulty();
		void DecreaseBaseDifficulty();

		// Selection level management
		void IncreaseSelectionLevel();
		void DecreaseSelectionLevel();

		// Change selection weights
		void ChangeWeight(Material::RockType type, int value);

		// Run difficulty
		void IncreaseRunDifficulty();
		// Generates an obstacle based on Weights, size and difficulty
		Obstacle GenObstacle();

		// Generates a boulder material based on weights
		Material GenBoulderMaterial();
		// Generates a boulder size based on range
		int GenBoulderSize(Material material);

	private:
		int baseDifficulty = 1;
		// Stores material weights for Obstacles
		double obstacleWeights[5] = {
			20,			// IGNEOUS
			20,			// SEDIMENTARY
			20,			// METAMORPHIC
			1,			// EXTRATERRESTRIAL
			5			// METAL
		};
		// Stores the min and max sizes for possible obstacles
		int obstacleSizes[5][2] = {
			{5, 10},
			{5, 10},
			{5, 10},
			{3, 7},
			{3, 7}
		};


		int runDifficulty = 0;
		
		// Stores selection level (improves size of selectable Boulders)
		int selectionLevel = 1;
		// Stores selection weights
		double selectionWeights[5] = {
			20,
			20,
			20,
			0,
			1
		};
		int selectionSizes[5][2] = {
			{5, 10},
			{7, 12},
			{5, 10},
			{4, 7},
			{4, 7}
		};
	};

	extern ProgressionManager progressionManager;
}