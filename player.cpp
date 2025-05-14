#include "player.h"
#include <corecrt_math.h>
#include "progression_manager.h"

namespace Boulder
{
	Player::Player()
	{
		Material mat = progressionManager.GenBoulderMaterial();
		InitNewBoulder(mat, progressionManager.GenBoulderSize(mat));


		// Init Currencies
		igneous = 100;
		sedimentary = 100;
		metamorphic = 100;
		extraterrestrial = 0;
		metal = 0;
	}

	void Player::InitNewBoulder(Material pmaterial, int psize)
	{
		material = pmaterial;
		size = psize;

		density = material.GenDensity();
		brittleness = material.GenBrittleness();
		hardness = material.GenHardness();
		smoothness = material.GenSmoothness();

		UpdateSecondaryStats();

	}
	
	Material Player::GetMaterial()
	{
		return material;
	}

	unsigned int Player::GetColorCode()
	{
		return material.GetColorCode();
	}

	//
	// Adds currency of the specified type to the player
	//

	void Player::AddCurrency(Material::RockType currencyType, int value)
	{
		switch (currencyType) {
		case Material::RockType::IGNEOUS:
			igneous += value;
			break;
		case Material::RockType::SEDIMENTARY:
			sedimentary += value;
			break;
		case Material::RockType::METAMORPHIC:
			metamorphic += value;
			break;
		case Material::RockType::EXTRATERRESTRIAL:
			extraterrestrial += value;
			break;
		case Material::RockType::METAL:
			metal += value;
			break;
		}
	}

	//
	//  Subtracts currency of specified type from the player
	//

	void Player::SubCurrency(Material::RockType currencyType, int value)
	{
		switch (currencyType) {
		case Material::RockType::IGNEOUS:
			igneous -= value;
			break;
		case Material::RockType::SEDIMENTARY:
			sedimentary -= value;
			break;
		case Material::RockType::METAMORPHIC:
			metamorphic -= value;
			break;
		case Material::RockType::EXTRATERRESTRIAL:
			extraterrestrial -= value;
			break;
		case Material::RockType::METAL:
			metal -= value;
			break;
		}
	}

	//
	// Getter methods
	//
	int Player::GetIgneous()
	{
		return igneous;
	}

	int Player::GetSedimentary()
	{
		return sedimentary;
	}

	int Player::GetMetamorphic()
	{
		return metamorphic;
	}

	int Player::GetExtraterrestrial()
	{
		return extraterrestrial;
	}

	int Player::GetMetal()
	{
		return metal;
	}

	int Player::CurrByType(Material::RockType type)
	{
		switch (type) {
		case Material::RockType::IGNEOUS:
			return igneous;
		case Material::RockType::SEDIMENTARY:
			return sedimentary;
		case Material::RockType::METAMORPHIC:
			return metamorphic;
		case Material::RockType::EXTRATERRESTRIAL:
			return extraterrestrial;
		case Material::RockType::METAL:
			return metal;
		}
		return 0;
	}

	// Upgrade realted methods
	void Player::AddStat(float value, Stat stat)
	{
		switch (stat)
		{
		case Stat::DENSITY:
			density += value;
			break;
		case Stat::BRITTLENESS:
			brittleness += value;
			if (brittleness < 0)
			{
				brittleness = 0;
			}
			break;
		case Stat::HARDNESS:
			hardness += value;
			break;
		case Stat::SMOOTHNESS:
			smoothness += value;
			break;
		}
		UpdateSecondaryStats();
	}

	void Player::MultStat(float value, Stat stat)
	{
		switch (stat)
		{
		case Stat::DENSITY:
			density *= value;
			break;
		case Stat::BRITTLENESS:
			brittleness *= value;
			break;
		case Stat::HARDNESS:
			hardness *= value;
			break;
		case Stat::SMOOTHNESS:
			smoothness *= value;
			break;
		}
		UpdateSecondaryStats();
	}


	// Drawing related methods

	int Player::GetDensityInt()
	{
		return (int)density;
	}

	int Player::GetBrittlenessInt()
	{
		return (int)brittleness;
	}

	int Player::GetHardnessInt()
	{
		return (int)hardness;
	}

	int Player::GetSmoothnessInt()
	{
		return (int)smoothness;
	}

	int Player::GetSize()
	{
		return size;
	}

	float Player::GetIntegrity()
	{
		return integrity;
	}

	float Player::GetMaxIntegrity()
	{
		return max_integrity;
	}

	float Player::GetSpeed()
	{
		return speed;
	}

	float Player::GetMaxSpeed()
	{
		return max_speed;
	}

	// Update Stats
	void Player::UpdateSecondaryStats()
	{
		const float BaseIntegrity = 100.0;
		max_integrity = BaseIntegrity * pow(1.1, density) * size;
		integrity = max_integrity;

		speed = 0;
		const float BaseMaxSpeed = 10;
		max_speed = BaseMaxSpeed * pow(1.25, smoothness);

		const float BaseSpeedChange = 5.0;
		acceleration = BaseSpeedChange * pow(1.1, smoothness);
		deceleration = BaseSpeedChange * pow(0.99, smoothness);
	}

	// Rolling related methods
	void Player::Accelerate(float deltaTime)
	{
		speed += acceleration * deltaTime / 1000;
		if (speed > max_speed)
		{
			speed = max_speed;
		}
	}

	void Player::Decelerate(float deltaTime)
	{
		speed -= deceleration * deltaTime / 1000;
		if (speed < 0)
		{
			speed = 0;
		}
	}

	void Player::DecreaseSpeed(float value)
	{
		speed -= value;
		if (speed < 0)
		{
			speed = 0;
		}
	}

	

	
	// Collision related methods
	float Player::RemainingIntegrity(float damageTaken)
	{
		integrity -= damageTaken;
		if (integrity < 0)
		{
			integrity = 0;
		}
		return integrity;
	}

	float Player::CalcAtk()
	{
		float base = density * size;
		float hardMult = pow(1.05, hardness);
		float speedMult = pow(1.01, speed);
		return base * hardMult * speedMult;
	}

	float Player::CalcDef()
	{
		float base = density * size;
		float britMult = pow(0.9, brittleness);
		return base * britMult;
	}
}