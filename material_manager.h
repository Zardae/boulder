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
		Material igneousMaterials[1];
		Material sedimentaryMaterials[1];
		Material metamorphicMaterials[1];
		Material extraterrestrialMaterials[1];
		Material metalMaterials[1];

		double igneousWeight;
		double sedimentaryWeight;
		double metamorphicWeight;
		double extraterrestrialWeight;
		double metalWeight;
	};
}