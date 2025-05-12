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

		Material meteorIron("Meteoritic Iron", Material::RockType::EXTRATERRESTRIAL, 12, 1, 2, 1, 10, 1, 6, 2, 0x505060);
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

	Material::RockType MaterialManager::GetObstacleType()
	{
		// This method of sampling was suggested by Jeremiah.
		std::random_device rd;
		std::mt19937 gen(rd());
		std::discrete_distribution<> distr({
			10,		// Igneous
			10,		// Sedimentary
			10,		// Metamorphic
			1,		// Extraterrestrial
			2		// Metal
			});

		Material::RockType ret = static_cast<Material::RockType>(distr(gen));	// According to a stack overflow answer
																				// the static cast is dangerous, but I
																				// was unable to find something better as of yet
		return ret;
	}

	Material MaterialManager::GetMaterial(Material::RockType rockType)
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
			typeAmount = sizeof(igneousMaterials);
		case Material::RockType::SEDIMENTARY:
			typeAmount = sizeof(sedimentaryMaterials);
		case Material::RockType::METAMORPHIC:
			typeAmount = sizeof(metamorphicMaterials);
		case Material::RockType::EXTRATERRESTRIAL:
			typeAmount = sizeof(extraterrestrialMaterials);
		case Material::RockType::METAL:
			typeAmount = sizeof(metalMaterials);
		}

		std::uniform_int_distribution<> distr(0, typeAmount);
		int rnd = distr(gen);

		switch (rockType)
		{
		case Material::RockType::IGNEOUS:
			return igneousMaterials[rnd];
		case Material::RockType::SEDIMENTARY:
			return sedimentaryMaterials[rnd];
		case Material::RockType::METAMORPHIC:
			return metamorphicMaterials[rnd];
		case Material::RockType::EXTRATERRESTRIAL:
			return extraterrestrialMaterials[rnd];
		case Material::RockType::METAL:
			return metalMaterials[rnd];
		}
	}
}