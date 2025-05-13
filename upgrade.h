#pragma once
#include "surface.h"
#include <string>
#include "player.h"
#include "material_manager.h"

namespace Boulder
{
	class Upgrade
	{
	public:
		enum UpgradeMode {
			ADDITIVE,
			MULTIPLICATIVE
		};
		enum UpgradeTarget {
			DENSITY,
			BRITTLENESS,
			HARDNESS,
			SMOOTHNESS,
			CHANCE_IGNEOUS,
			CHANCE_SEDIMENTARY,
			CHANCE_METAMORPHIC,
			CHANCE_EXTRATERRESTRIAL,
			CHANCE_METAL
		};

		Upgrade();
		Upgrade(UpgradeMode pmode, UpgradeTarget ptarget, std::string pname, int pbaseCostIgneous, int pbaseCostSedimentary, int pbaseCostMetamorphic, int pbaseCostExtraterrestrial, int pbaseCostMetal, float pcostCreepMult);

		bool CanPurchase(Player& player);
		void PurchaseUpgrade(Player& player);


		void Draw(Surface& screen, Player& player, int posX, int posY);
	private:
		UpgradeMode mode;
		UpgradeTarget target;
		std::string name;
		int baseCostIgneous;
		int baseCostSedimentary;
		int baseCostMetamorphic;
		int baseCostExtraterrestrial;
		int baseCostMetal;
		int timesPurchased;
		float costCreepMult;
	};
}