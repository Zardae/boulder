#pragma once
#include "material.h"
#include "obstacle.h"

namespace Boulder
{
	class Player
	{
	public:
		enum Stat {
			DENSITY,
			BRITTLENESS,
			HARDNESS,
			SMOOTHNESS
		};
		Player();
		void InitNewBoulder(Material* pmaterial, int psize);
		Material* GetMaterial();
		unsigned int GetColorCode();

		// Currency related methods
		void AddCurrency(Material::RockType currencyType, int value);
		void SubCurrency(Material::RockType currencyType, int value);

		int GetIgneous();
		int GetSedimentary();
		int GetMetamorphic();
		int GetExtraterrestrial();
		int GetMetal();
		int CurrByType(Material::RockType type);


		// Upgrade related methods
		void AddStat(float value, Stat stat);
		void MultStat(float value, Stat stat);

		// Drawing related methods
		int GetDensityInt();
		int GetBrittlenessInt();
		int GetHardnessInt();
		int GetSmoothnessInt();


		int GetSize();
		float GetIntegrity();
		float GetMaxIntegrity();
		float GetSpeed();			// Also important for Rolling
		float GetMaxSpeed();

		// Update Max Integrity, Max Speed, Acceleration and Decceleration
		// Called after creating Boulder and Updating Stat
		void UpdateSecondaryStats();

		// Rolling related methods
		void Accelerate(float deltaTime);
		void Decelerate(float deltaTime);
		void DecreaseSpeed(float value);

		// Collision related methods
		float RemainingIntegrity(float damageTaken);
		float CalcAtk();
		float CalcDef();


	private:
		// Boulder related members
		Material* material;
		float density;
		float brittleness;
		float hardness;
		float smoothness;

		int size;
		float integrity;
		float max_integrity;
		float speed;
		float max_speed;
		float acceleration;
		float deceleration;


		// Shop related members
		int igneous;
		int sedimentary;
		int metamorphic;
		int extraterrestrial;
		int metal;
	};
}