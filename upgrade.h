#pragma once
#include "surface.h"
#include <string>
#include "material_manager.h"
#include "progression_manager.h"
#include "player.h"

namespace Boulder
{
	class Upgrade
	{
	public:
		enum Mode {
			ADDITIVE,
			MULTIPLICATIVE
		};
		enum Target {
			DENSITY,
			BRITTLENESS,
			HARDNESS,
			SMOOTHNESS,
			IGNEOUS,
			SEDIMENTARY,
			METAMORPHIC,
			EXTRATERRESTRIAL,
			METAL,
			SELECTION,
			DIFFICULTY
		};

		Upgrade();
		Upgrade(Mode pmode, Target ptarget, std::string pname, float pvalue, int pbaseCostIgneous, int pbaseCostSedimentary, int pbaseCostMetamorphic, int pbaseCostExtraterrestrial, int pbaseCostMetal, float pcostCreepMult, int pX, int pY);
		// Constructor for chance upgrades to reduce clutter
		Upgrade(Target ptarget, std::string pname, float pvalue, int baseCost, Material::RockType rockType, float pcostCreepMult, int pX, int pY);
		// Constructor for meta progression upgrades
		Upgrade(Target ptarget, std::string pname, int pbaseCostIgneous, int pbaseCostSedimentary, int pbaseCostMetamorphic, int pbaseCostExtraterrestrial, int pbaseCostMetal, float pcostCreepMult, int pX, int pY);

		// Purchase related methods
		void UpdateCanPurchase(Player& player);
		bool CanPurchase();
		void Purchase(Player& player);

		void Draw(Surface* screen);
	private:
		// Cost related values
		Mode mode;
		Target target;
		std::string name;
		float value;
		int baseCostIgneous = 0;
		int baseCostSedimentary = 0;
		int baseCostMetamorphic = 0;
		int baseCostExtraterrestrial = 0;
		int baseCostMetal = 0;
		int timesPurchased;
		float costCreepMult;

		// Position in upgrade screen
		int posX;
		int posY;

		// Bool to see if the upgrade can be purchased
		// This was added to not check every upgrade every frame
		bool canPurchase = false;
	};
}