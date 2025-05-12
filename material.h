#pragma once
#include "surface.h"
#include <string>

//
// Defines the material class used both for the player and the obstacles.
//

namespace Boulder
{
	class Material
	{
	public:
		// Enum for Material Types
		enum RockType {
			IGNEOUS,
			SEDIMENTARY,
			METAMORPHIC,
			EXTRATERRESTRIAL,
			METAL
		};

		// Material functions
		Material();
		Material(std::string pname, Material::RockType type, float pden_mean, float pden_var, float pbrit_mean, float pbrit_var, float phard_mean, float phard_var, float psmooth_mean, float psmooth_var, Pixel pcolor);
		std::string GetName();
		Material::RockType GetRockType();
		unsigned int GetColorCode();
		float GenDensity();
		float GenBrittleness();
		float GenHardness();
		float GenSmoothness();

	private:
		std::string name;
		RockType rock_type;
		float density_mean;
		float density_var;
		float brittleness_mean;
		float brittleness_var;
		float hardness_mean;
		float hardness_var;
		float smoothness_mean;
		float smoothness_var;
		unsigned int color_code;
	};
};