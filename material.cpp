#include "material.h"
#include <random>

//
// Implements the material class
//

namespace Boulder
{
	//
	// Default Constructor for the Material class
	//

	Material::Material()
	{
		name = "NULL MATERIAL";
		rock_type = Material::RockType::IGNEOUS;
		density_mean = 5;
		density_var = 1;
		brittleness_mean = 5;
		brittleness_var = 1;
		hardness_mean = 5;
		hardness_var = 1;
		smoothness_mean = 5;
		smoothness_var = 1;
		color_code = 0x909090;
	}

	Material::Material(std::string pname, Material::RockType ptype, float pden_mean, float pden_var, float pbrit_mean, float pbrit_var, float phard_mean, float phard_var, float psmooth_mean, float psmooth_var, Pixel pcolor)
	{
		name = pname;
		rock_type = ptype;
		density_mean = pden_mean;
		density_var = pden_var;
		brittleness_mean = pbrit_mean;
		brittleness_var = pbrit_var;
		hardness_mean = phard_mean;
		hardness_var = phard_var;
		smoothness_mean = psmooth_mean;
		smoothness_var = psmooth_var;
		color_code = pcolor;
	}

	//
	// Getter Functions for members needing one
	//

	std::string Material::GetName()
	{
		return name;
	}

	Material::RockType Material::GetRockType()
	{
		//TODO
		return rock_type;
	}

	unsigned int Material::GetColorCode()
	{
		return color_code;
	}

	//
	// The following methods generate a random value using normal distribution to give some randomness to each boulder and obstacle
	//

	float Material::GenDensity()
	{
		std::random_device rd{};

		std::mt19937 gen{ rd() };

		std::normal_distribution<float> d{ density_mean, density_var };

		float ret = d(gen);

		// Safeguard against negative numbers and zero. Those would mess with the calculations later on.

		while (ret <= 0)
		{
			ret = d(gen);
		}

		return ret;
	}

	float Material::GenBrittleness()
	{
		std::random_device rd{};
		
		std::mt19937 gen{ rd() };

		std::normal_distribution<float> d{ brittleness_mean, brittleness_var };

		float ret = d(gen);

		while (ret <= 0)
		{
			ret = d(gen);
		}

		return ret;
	}

	float Material::GenHardness()
	{
		std::random_device rd{};

		std::mt19937 gen{ rd() };

		std::normal_distribution<float> d{ hardness_mean, hardness_var };

		float ret = d(gen);

		while (ret <= 0)
		{
			ret = d(gen);
		}

		return ret;
	}

	float Material::GenSmoothness()
	{
		std::random_device rd{};

		std::mt19937 gen{ rd() };

		std::normal_distribution<float> d{ smoothness_mean, smoothness_var };

		float ret = d(gen);

		while (ret <= 0)
		{
			ret = d(gen);
		}

		return ret;
	}
}