#include "material_manager.h"
#include <random>
#include <iostream>

namespace Boulder
{
	MaterialManager materialManager;

	MaterialManager::MaterialManager()
	{
		Material granite((std::string)"Granite", Material::RockType::IGNEOUS, 10, 2, 4, 1, 10, 2, 4, 1, 0xaaaaaa);
		igneousMaterials[0] = granite;
		igneousWeight = 20;


		Material sandstone((std::string)"Sandstone", Material::RockType::SEDIMENTARY, 5, 1, 7, 1, 5, 2, 9, 2, 0xb29082);
		sedimentaryMaterials[0] = sandstone;
		sedimentaryWeight = 40;

		Material gneiss((std::string)"Gneiss", Material::RockType::METAMORPHIC, 8, 1, 4, 1, 8, 2, 6, 2, 0x808080);
		metamorphicMaterials[0] = gneiss;
		metamorphicWeight = 20;

		Material meteorIron((std::string)"Meteoritic Iron", Material::RockType::EXTRATERRESTRIAL, 12, 1, 2, 1, 10, 1, 6, 2, 0x505060);
		extraterrestrialMaterials[0] = meteorIron;
		extraterrestrialWeight = 0;

		Material iron((std::string)"Iron", Material::RockType::METAL, 10, 1, 4, 1, 8, 1, 8, 1, 0x606070);
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
		case Material::RockType::EXTRATERRESTRIAL:
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
		case Material::RockType::EXTRATERRESTRIAL:
			extraterrestrialWeight -= value;
			break;
		case Material::RockType::METAL:
			metalWeight -= value;
			break;
		}
	}

	Material::RockType MaterialManager::GetTypeSample()
	{
		// This method of weighted sampling was found on StackOverflow
		double sumOfWeight = igneousWeight + sedimentaryWeight + metamorphicWeight + extraterrestrialWeight + metalWeight;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, sumOfWeight);
		int rnd = distr(gen);
		if (rnd < igneousWeight)
		{
			return Material::RockType::IGNEOUS;
		}
		else if (rnd - igneousWeight < sedimentaryWeight) 
		{
			return Material::RockType::SEDIMENTARY;
		}
		else if (rnd - igneousWeight - sedimentaryWeight < metamorphicWeight)
		{
			return Material::RockType::METAMORPHIC;
		}
		else if (rnd - igneousWeight - sedimentaryWeight - metamorphicWeight < extraterrestrialWeight)
		{
			return Material::RockType::EXTRATERRESTRIAL;
		}
		else
		{
			return Material::RockType::METAL;
		}
	}


	Material* MaterialManager::GetMaterial(Material::RockType rockType)
	{
		// Method for the case that more Materials per type are added
		std::random_device rd;
		std::mt19937 gen(rd());

		// This approach may seem a bit overcomplicated, but I ran into an issue earlier with variables inside switch statements
		// so I am doing it this way for now
		int typeAmount = 0;
		switch (rockType)
		{
		case Material::RockType::IGNEOUS:
			typeAmount = std::size(igneousMaterials);
			break;
		case Material::RockType::SEDIMENTARY:
			typeAmount = std::size(sedimentaryMaterials);
			break;
		case Material::RockType::METAMORPHIC:
			typeAmount = std::size(metamorphicMaterials);
			break;
		case Material::RockType::EXTRATERRESTRIAL:
			typeAmount = std::size(extraterrestrialMaterials);
			break;
		case Material::RockType::METAL:
			typeAmount = std::size(metalMaterials);
			break;
		}
		// Generating the distribution of the material type.
		// The Max amount is reduced by 2 to account for arrays starting at 0 and the last place of the array being empty to ensure
		// the types with only one material are still handled correctly.
		std::uniform_int_distribution<> distr(0, typeAmount - 2);
		int rnd = distr(gen);
		Material* ret;

		switch (rockType)
		{
		case Material::RockType::IGNEOUS:
			ret = &igneousMaterials[rnd];
			break;
		case Material::RockType::SEDIMENTARY:
			ret = &sedimentaryMaterials[rnd];
			break;
		case Material::RockType::METAMORPHIC:
			ret = &metamorphicMaterials[rnd];
			break;
		case Material::RockType::EXTRATERRESTRIAL:
			ret = &extraterrestrialMaterials[rnd];
			break;
		case Material::RockType::METAL:
			ret = &metalMaterials[rnd];
			break;
		default:
			ret = &igneousMaterials[0];
			break;
		}
		return ret;
	}
}