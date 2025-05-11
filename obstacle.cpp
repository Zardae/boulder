#include "obstacle.h"

namespace Boulder
{
	Obstacle::Obstacle()
	{
		material;
		size = 5;
		density = 5;
		brittleness = 5;
		hardness = 5;
	}

	Obstacle::Obstacle(Material pmaterial, float psize)
	{
		material = pmaterial;
		size = psize;
		density = material.GenDensity();
		brittleness = material.GenBrittleness();
		hardness = material.GenHardness();
	}
}