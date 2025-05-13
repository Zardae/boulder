#include "obstacle.h"
#include <corecrt_math.h>

namespace Boulder
{
	Obstacle::Obstacle()
	{
		material;
		size = 10;
		density = 5;
		brittleness = 5;
		hardness = 5;

		reward = 10;
		
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
		
		reward = 5 * size;

		pos_x = 800 - size - 5;
		pos_y = 490 - (5 + size);
	}

	// Collision related
	float Obstacle::CalcAtk()
	{
		float base = density * size;
		float hardMult = pow(1.05, hardness);
		return base * hardMult;
	}

	float Obstacle::CalcDef()
	{
		float base = density * size;
		float britMult = pow(0.9, brittleness);
		return base * britMult;
	}

	float Obstacle::CalcSlowdown()
	{
		const float SlowdownFactor = 0.075;
		return density * size * SlowdownFactor;
	}

	// Move Method
	void Obstacle::Move(int distance)
	{
		pos_x -= distance;
	}

	// Position Getter Methods
	int Obstacle::GetX()
	{
		return pos_x;
	}

	int Obstacle::GetY()
	{
		return pos_y;
	}

	Material Obstacle::GetMaterial()
	{
		return material;
	}

	int Obstacle::GetSize()
	{
		return size;
	}

	int Obstacle::GetReward()
	{
		return reward;
	}

	Pixel Obstacle::GetColor()
	{
		return material.GetColorCode();
	}
}