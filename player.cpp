#include "player.h"

namespace Boulder
{
	Player::Player()
	{
		material;
		density = 5.0;
		brittleness = 5.0;
		hardness = 5.0;
		smoothness = 5.0;

		size = 3;
		mass = 15.0;
		integrity = 45.0;
		max_integrity = 4.05;
		speed = 0.0;
		max_speed = 50.0;
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

}