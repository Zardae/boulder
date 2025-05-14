#include "upgrade.h"
#include <iostream>

namespace Boulder
{
	Upgrade::Upgrade()
	{
		mode = Mode::ADDITIVE;
		target = Target::DENSITY;
		name = "NULL UPGRADE";
		value = 100.0;
		baseCostIgneous = 100000;
		baseCostSedimentary = 100000;
		baseCostMetamorphic = 100000;
		baseCostExtraterrestrial = 100000;
		baseCostMetal = 100000;
		timesPurchased = 0;
		costCreepMult = 100.0;
		posX = 0;
		posY = 0;
	}

	Upgrade::Upgrade(Mode pmode, Target ptarget, std::string pname, float pvalue, int pbaseCostIgneous, int pbaseCostSedimentary, int pbaseCostMetamorphic, int pbaseCostExtraterrestrial, int pbaseCostMetal, float pcostCreepMult, int pX, int pY)
	{
		mode = pmode;
		target = ptarget;
		name = pname;
		value = pvalue;
		baseCostIgneous = pbaseCostIgneous;
		baseCostSedimentary = pbaseCostSedimentary;
		baseCostMetamorphic = pbaseCostMetamorphic;
		baseCostExtraterrestrial = pbaseCostExtraterrestrial;
		baseCostMetal = pbaseCostMetal;
		timesPurchased = 0;
		costCreepMult = pcostCreepMult;
		posX = pX;
		posY = pY;
	}

	Upgrade::Upgrade(Target ptarget, std::string pname, float pvalue, int baseCost, Material::RockType rockType, float pcostCreepMult, int pX, int pY)
	{
		mode = Mode::ADDITIVE;
		target = ptarget;
		name = pname;
		value = pvalue;
		switch (rockType)
		{
		case Material::RockType::IGNEOUS:
			baseCostIgneous = baseCost;
			break;
		case Material::RockType::SEDIMENTARY:
			baseCostSedimentary = baseCost;
			break;
		case Material::RockType::METAMORPHIC:
			baseCostMetamorphic = baseCost;
			break;
		case Material::RockType::EXTRATERRESTRIAL:
			baseCostExtraterrestrial = baseCost;
			break;
		case Material::RockType::METAL:
			baseCostMetal = baseCost;
			break;
		}
		timesPurchased = 0;
		costCreepMult = pcostCreepMult;
		posX = pX;
		posY = pY;
	}

	Upgrade::Upgrade(Target ptarget, std::string pname,  int pbaseCostIgneous, int pbaseCostSedimentary, int pbaseCostMetamorphic, int pbaseCostExtraterrestrial, int pbaseCostMetal, float pcostCreepMult, int pX, int pY)
	{
		mode = Mode::ADDITIVE;
		target = ptarget;
		name = pname;
		baseCostIgneous = pbaseCostIgneous;
		baseCostSedimentary = pbaseCostSedimentary;
		baseCostMetamorphic = pbaseCostMetamorphic;
		baseCostExtraterrestrial = pbaseCostExtraterrestrial;
		baseCostMetal = pbaseCostMetal;
		timesPurchased = 0;
		costCreepMult = pcostCreepMult;
		value = 1;
		posX = pX;
		posY = pY;
	}


	void Upgrade::UpdateCanPurchase(Player& player)
	{
		// Return false if player balance is too low for upgrade
		if (player.GetIgneous() < (int)(baseCostIgneous * pow(costCreepMult, timesPurchased)))
		{
			canPurchase = false;
			return;
		}
		if (player.GetSedimentary() < (int)(baseCostSedimentary * pow(costCreepMult, timesPurchased)))
		{
			canPurchase = false;
			return;
		}
		if (player.GetMetamorphic() < (int)(baseCostMetamorphic * pow(costCreepMult, timesPurchased)))
		{
			canPurchase = false;
			return;
		}
		if (player.GetExtraterrestrial() < (int)(baseCostExtraterrestrial * pow(costCreepMult, timesPurchased)))
		{
			canPurchase = false;
			return;
		}
		if (player.GetMetal() < (int)(baseCostMetal * pow(costCreepMult, timesPurchased)))
		{
			canPurchase = false;
			return;
		}
		canPurchase = true;
	}

	bool Upgrade::CanPurchase()
	{
		return canPurchase;
	}

	void Upgrade::Purchase(Player& player)
	{
		// Calculate Cost and remove from player balance
		int costIgneous = (int)(baseCostIgneous * pow(costCreepMult, timesPurchased));
		int costSedimentary = (int)(baseCostSedimentary * pow(costCreepMult, timesPurchased));
		int costMetamorphic = (int)(baseCostMetamorphic * pow(costCreepMult, timesPurchased));
		int costExtraterrestrial = (int)(baseCostExtraterrestrial * pow(costCreepMult, timesPurchased));
		int costMetal = (int)(baseCostMetal * pow(costCreepMult, timesPurchased));

		player.SubCurrency(Material::RockType::IGNEOUS, costIgneous);
		player.SubCurrency(Material::RockType::SEDIMENTARY, costSedimentary);
		player.SubCurrency(Material::RockType::METAMORPHIC, costMetamorphic);
		player.SubCurrency(Material::RockType::EXTRATERRESTRIAL, costExtraterrestrial);
		player.SubCurrency(Material::RockType::METAL, costMetal);

		// Increase times purchased
		timesPurchased++;

		// Apply effect
		switch (target)
		{
			// Boulder Upgrades
		case Target::DENSITY:
			if (mode == Mode::ADDITIVE)
			{
				player.AddStat(value, Player::Stat::DENSITY);
			}
			else
			{
				player.MultStat(value, Player::Stat::DENSITY);
			}
			break;
		case Target::BRITTLENESS:
			if (mode == Mode::ADDITIVE)
			{
				player.AddStat(value, Player::Stat::BRITTLENESS);
			}
			else
			{
				player.MultStat(value, Player::Stat::BRITTLENESS);
			}
			break;
		case Target::HARDNESS:
			if (mode == Mode::ADDITIVE)
			{
				player.AddStat(value, Player::Stat::HARDNESS);
			}
			else
			{
				player.MultStat(value, Player::Stat::HARDNESS);
			}
			break;
		case Target::SMOOTHNESS:
			if (mode == Mode::ADDITIVE)
			{
				player.AddStat(value, Player::Stat::SMOOTHNESS);
			}
			else
			{
				player.MultStat(value, Player::Stat::SMOOTHNESS);
			}
			break;
			
			// Chance Upgrades
		case Target::IGNEOUS:
			progressionManager.ChangeWeight(Material::RockType::IGNEOUS, (int)value);
			break;
		case Target::SEDIMENTARY:
			progressionManager.ChangeWeight(Material::RockType::SEDIMENTARY, (int)value);
			break;
		case Target::METAMORPHIC:
			progressionManager.ChangeWeight(Material::RockType::METAMORPHIC, (int)value);
			break;
		case Target::EXTRATERRESTRIAL:
			progressionManager.ChangeWeight(Material::RockType::EXTRATERRESTRIAL, (int)value);
			break;
		case Target::METAL:
			progressionManager.ChangeWeight(Material::RockType::METAL, (int)value);
			break;

			// Meta upgrades
		case Target::SELECTION:
			if (value > 0)
			{
				progressionManager.IncreaseSelectionLevel();
			}
			else 
			{
				progressionManager.DecreaseSelectionLevel();
			}
			break;
		case Target::DIFFICULTY:
			if (value > 0)
			{
				progressionManager.IncreaseBaseDifficulty();
			}
			else
			{
				progressionManager.DecreaseBaseDifficulty();
			}
			break;
		}

	}

	void Upgrade::ResetTimesPurchased()
	{
		timesPurchased = 0;
	}


	void Upgrade::Draw(Surface* screen)
	{
		// Draw Box
		Pixel boxCol = 0xff0000;
		if (canPurchase)
		{
			boxCol = 0x00ff00;
		}
		int width = 200;
		if (target == Target::IGNEOUS || target == Target::SEDIMENTARY || target == Target::METAMORPHIC || target == Target::EXTRATERRESTRIAL || target == Target::METAL)
		{
			// Adjust width if chance upgrade, meaning 5 upgrades in the row
			width = 160;
		}
		int height = 70;

		screen->Box(posX, posY, posX + width - 1, posY + height - 1, boxCol);
		// Draw info
		screen->Print(name.data(), posX + 5, posY + 5, 0xffffff);

		std::string ignCost = std::to_string((int)(baseCostIgneous * pow(costCreepMult, timesPurchased)));
		screen->Print(ignCost.data(), posX + 5, posY + 15, 0xaaaaaa);
		std::string sedCost = std::to_string((int)(baseCostSedimentary * pow(costCreepMult, timesPurchased)));
		screen->Print(sedCost.data(), posX + 5, posY + 25, 0xb29082);
		std::string mtmCost = std::to_string((int)(baseCostMetamorphic * pow(costCreepMult, timesPurchased)));
		screen->Print(mtmCost.data(), posX + 5, posY + 35, 0x808080);
		std::string extCost = std::to_string((int)(baseCostExtraterrestrial * pow(costCreepMult, timesPurchased)));
		screen->Print(extCost.data(), posX + 5, posY + 45, 0x505060);
		std::string metCost = std::to_string((int)(baseCostMetal * pow(costCreepMult, timesPurchased)));
		screen->Print(metCost.data(), posX + 5, posY + 55, 0x606070);

	}
}