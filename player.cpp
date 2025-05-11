#include "player.h"
#include <corecrt_math.h>

namespace Boulder
{
	Player::Player()
	{
		material;
		density = 5.0;
		brittleness = 5.0;
		hardness = 5.0;
		smoothness = 5.0;

		size = 10;
		mass = 15.0;
		integrity = 45.0;
		max_integrity = 4.0;
		speed = 0.0;
		max_speed = 15.0;
		acceleration = 2.5;
		deceleration = 2.5;


		igneous = 1000;
		sedimentary = 100;
		metamorphic = 100;
		extraterrestrial = 0;
		metal = 0;
	}

	void Player::SetMaterial(Material pmaterial)
	{
		material = pmaterial;
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
		case Material::RockType::EXTRATERRESTIAL:
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
		case Material::RockType::EXTRATERRESTIAL:
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

	// Upgrade realted methods



	// Drawing related methods

	int Player::GetSize()
	{
		return size;
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

	float Player::GetSpeed()
	{
		return speed;
	}

	
	// Collision related methods
	float Player::RemainingIntegrity(float damageTaken)
	{
		integrity -= damageTaken;
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