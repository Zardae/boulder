#pragma once
#include "material.h"

namespace Boulder
{
	class MaterialManager
	{
	public:
		MaterialManager();

		void IncreaseWeight(Material::RockType prockType, int value);
		void DecreaseWeight(Material::RockType prockType, int value);
		Material::RockType GetTypeSample();
		Material::RockType GetObstacleType();
		Material GetMaterial(Material::RockType rockType);

	private:
		Material igneousMaterials[2];
		Material sedimentaryMaterials[2];
		Material metamorphicMaterials[2];
		Material extraterrestrialMaterials[2];
		Material metalMaterials[2];

		double igneousWeight;
		double sedimentaryWeight;
		double metamorphicWeight;
		double extraterrestrialWeight;
		double metalWeight;
	};

	extern MaterialManager materialManager;
}