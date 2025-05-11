#include "material_manager.h"
#include <random>

namespace Boulder
{
	MaterialManager::MaterialManager()
	{
		Material granite{ "Granite", Material::RockType::IGNEOUS, 10, 2, 4, 1, 10, 2, 4, 1, 0xaaaaaa };
		igneousMaterials[0] = granite;
		igneousWeight = 20;


		Material sandstone{ "Sandstone", Material::RockType::SEDIMENTARY, 5, 1, 7, 1, 5, 2, 9, 2, 0xb29082 };
		sedimentaryMaterials[0] = sandstone;
		sedimentaryWeight = 40;

		Material gneiss{ "Gneiss", Material::RockType::METAMORPHIC, 8, 1, 4, 1, 8, 2, 6, 2, 0x808080 };
		metamorphicMaterials[0] = gneiss;
		metamorphicWeight = 20;

		Material meteorIron("Meteoritic Iron", Material::RockType::EXTRATERRESTIAL, 12, 1, 2, 1, 10, 1, 6, 2, 0x505060);
		extraterrestrialMaterials[0] = meteorIron;
		extraterrestrialWeight = 0;

		Material iron("Iron", Material::RockType::METAL, 10, 1, 4, 1, 8, 1, 8, 1, 0x606070);
		metalMaterials[0] = iron;
		metalWeight = 0;
	}

	void MaterialManager::IncreaseWeight(Material::RockType prockType, int value)
	{
		switch (prockType)
		{
		case Material::RockType::IGNEOUS:
			igneousWeight += value;
			break;
		case Material::RockType::SEDIMENTARY:
			sedimentaryWeight += value;
			break;
		case Material::RockType::METAMORPHIC:
			metamorphicWeight += value;
			break;
		case Material::RockType::EXTRATERRESTIAL:
			extraterrestrialWeight += value;
			break;
		case Material::RockType::METAL:
			metalWeight += value;
			break;
		}
	}

	void MaterialManager::DecreaseWeight(Material::RockType prockType, int value)
	{
		switch (prockType)
		{
		case Material::RockType::IGNEOUS:
			igneousWeight -= value;
			break;
		case Material::RockType::SEDIMENTARY:
			sedimentaryWeight -= value;
			break;
		case Material::RockType::METAMORPHIC:
			metamorphicWeight -= value;
			break;
		case Material::RockType::EXTRATERRESTIAL:
			extraterrestrialWeight -= value;
			break;
		case Material::RockType::METAL:
			metalWeight -= value;
			break;
		}
	}

	Material::RockType* MaterialManager::GetTypeSample()
	{
		int sumOfWeight = igneousWeight + sedimentaryWeight + metamorphicWeight + extraterrestrialWeight + metalWeight;

		Material::RockType ret[3];
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, sumOfWeight);
		int rnd;
		for (int i = 0; i < 3; i++)
		{
			rnd = distr(gen);
			if (rnd < igneousWeight)
			{
				ret[i] = Material::RockType::IGNEOUS;
			}
			else if (rnd - igneousWeight < sedimentaryWeight) 
			{
				ret[i] = Material::RockType::SEDIMENTARY;
			}
			else if (rnd - igneousWeight - sedimentaryWeight < metamorphicWeight)
			{
				ret[i] = Material::RockType::METAMORPHIC;
			}
			else if (rnd - igneousWeight - sedimentaryWeight - metamorphicWeight < extraterrestrialWeight)
			{
				ret[i] = Material::RockType::EXTRATERRESTIAL;
			}
			else
			{
				ret[i] = Material::RockType::METAL;
			}
		}

		return ret;
	}
}