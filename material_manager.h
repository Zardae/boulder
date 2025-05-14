#pragma once
#include "material.h"

namespace Boulder
{
	class MaterialManager
	{
	public:
		MaterialManager();

		// Manage Selection weights
		void IncreaseWeight(Material::RockType prockType, int value);
		void DecreaseWeight(Material::RockType prockType, int value);

		// Sample a type based on weights
		Material::RockType GetTypeSample();

		// Sample a Material based on given type
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