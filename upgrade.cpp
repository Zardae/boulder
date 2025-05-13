#include "upgrade.h"

namespace Boulder
{
	Upgrade::Upgrade()
	{
		mode = UpgradeMode::ADDITIVE;
		target = UpgradeTarget::DENSITY;
		name = "NULL UPGRADE";
		baseCostIgneous = 100000;
		baseCostSedimentary = 100000;
		baseCostMetamorphic = 100000;
		baseCostExtraterrestrial = 100000;
		baseCostMetal = 100000;
		timesPurchased = 0;
		costCreepMult = 100.0;
	}

	Upgrade::Upgrade(UpgradeMode pmode, UpgradeTarget ptarget, std::string pname, int pbaseCostIgneous, int pbaseCostSedimentary, int pbaseCostMetamorphic, int pbaseCostExtraterrestrial, int pbaseCostMetal, float pcostCreepMult)
	{
		mode = pmode;
		target = ptarget;
		name = pname;
		baseCostIgneous = pbaseCostIgneous;
		baseCostSedimentary = pbaseCostSedimentary;
		baseCostMetamorphic = pbaseCostMetamorphic;
		baseCostExtraterrestrial = pbaseCostExtraterrestrial;
		baseCostMetal = pbaseCostMetal;
		timesPurchased = 0;
		costCreepMult = pcostCreepMult;
	}

	bool Upgrade::CanPurchase(Player& player)
	{
		// Return false if player balance is too low for upgrade
		if (player.GetIgneous() < (int)baseCostIgneous * pow(costCreepMult, timesPurchased))
		{
			return false;
		}
		if (player.GetSedimentary() < (int)baseCostSedimentary * pow(costCreepMult, timesPurchased))
		{
			return false;
		}
		if (player.GetMetamorphic() < (int)baseCostMetamorphic * pow(costCreepMult, timesPurchased))
		{
			return false;
		}
		if (player.GetExtraterrestrial() < (int)baseCostExtraterrestrial * pow(costCreepMult, timesPurchased))
		{
			return false;
		}
		if (player.GetMetal() < (int)baseCostMetal * pow(costCreepMult, timesPurchased))
		{
			return false;
		}


		return true;
	}
}