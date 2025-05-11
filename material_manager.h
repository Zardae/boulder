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
		Material::RockType* GetTypeSample();

	private:
		Material igneousMaterials[1];
		Material sedimentaryMaterials[1];
		Material metamorphicMaterials[1];
		Material extraterrestrialMaterials[1];
		Material metalMaterials[1];

		int igneousWeight;
		int sedimentaryWeight;
		int metamorphicWeight;
		int extraterrestrialWeight;
		int metalWeight;
	};
}