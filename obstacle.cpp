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

		pos_x = 800 - size;
		pos_y = 490 - (5 + size);
	}

	Obstacle::Obstacle(Material pmaterial, float psize)
	{
		material = pmaterial;
		size = psize;
		density = material.GenDensity();
		brittleness = material.GenBrittleness();
		hardness = material.GenHardness();

		pos_x = 800 - size;
		pos_y = 490 - (5 + size);
	}

	int Obstacle::GetX()
	{
		return pos_x;
	}

	int Obstacle::GetY()
	{
		return pos_y;
	}
}