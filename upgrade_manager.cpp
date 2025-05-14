#include "upgrade_manager.h"

namespace Boulder
{
	UpgradeManager upgradeManager;

	void UpgradeManager::Init()
	{
		// Initialize additive boulder upgrades
		Upgrade denAdd(Upgrade::Mode::ADDITIVE, Upgrade::Target::DENSITY, "Density (Add)", 1, 10, 10, 10, 50, 50, 1.2, 0, 60);
		boulderUpgrades[0][0] = denAdd;
		Upgrade britAdd(Upgrade::Mode::ADDITIVE, Upgrade::Target::BRITTLENESS, "Brittleness (Sub)", -1, 10, 10, 10, 0, 0, 1.2, 200, 60);
		boulderUpgrades[0][1] = britAdd;
		Upgrade hardAdd(Upgrade::Mode::ADDITIVE, Upgrade::Target::HARDNESS, "Hardness (Add)", 1, 10, 10, 10, 10, 0, 1.2, 400, 60);
		boulderUpgrades[0][2] = hardAdd;
		Upgrade smooAdd(Upgrade::Mode::ADDITIVE, Upgrade::Target::SMOOTHNESS, "Smoothness (Add)", 1, 10, 10, 40, 0, 0, 1.2, 600, 60);
		boulderUpgrades[0][3] = smooAdd;

		// Initialize multiplicative boulder upgrades
		Upgrade denMult(Upgrade::Mode::MULTIPLICATIVE, Upgrade::Target::DENSITY, "Density (Mult)", 1.1, 50, 50, 50, 100, 100, 1.5, 0, 130);
		boulderUpgrades[1][0] = denMult;
		Upgrade britMult(Upgrade::Mode::MULTIPLICATIVE, Upgrade::Target::BRITTLENESS, "Brittleness (Mult)", 0.9, 50, 50, 50, 0, 0, 1.5, 200, 130);
		boulderUpgrades[1][1] = britMult;
		Upgrade hardMult(Upgrade::Mode::MULTIPLICATIVE, Upgrade::Target::HARDNESS, "Hardness (Mult)", 1.1, 80, 40, 40, 50, 60, 1.5, 400, 130);
		boulderUpgrades[1][2] = hardMult;
		Upgrade smooMult(Upgrade::Mode::MULTIPLICATIVE, Upgrade::Target::SMOOTHNESS, "Smoothness (Mult)", 1.1, 20, 20, 100, 0, 0, 1.5, 600, 130);
		boulderUpgrades[1][3] = smooMult;

		// Initialize chance upgrades
		Upgrade ignAdd(Upgrade::Target::IGNEOUS, "Igneous (Add)", 5, 100, Material::RockType::IGNEOUS, 2, 0, 200);
		chanceUpgrades[0][0] = ignAdd;
		Upgrade sedAdd(Upgrade::Target::SEDIMENTARY, "Sedimentary (Add)", 5, 100, Material::RockType::SEDIMENTARY, 2, 160, 200);
		chanceUpgrades[0][1] = sedAdd;
		Upgrade mtaAdd(Upgrade::Target::METAMORPHIC, "Metamorphic (Add)", 5, 100, Material::RockType::METAMORPHIC, 2, 320, 200);
		chanceUpgrades[0][2] = mtaAdd;
		Upgrade extAdd(Upgrade::Target::EXTRATERRESTRIAL, "Extraterrestrial (Add)", 1, 100, Material::RockType::EXTRATERRESTRIAL, 2, 480, 200);
		chanceUpgrades[0][3] = extAdd;
		Upgrade metAdd(Upgrade::Target::METAL, "Metal (Add)", 1, 100, Material::RockType::METAL, 2, 640, 200);
		chanceUpgrades[0][4] = metAdd;

		Upgrade ignSub(Upgrade::Target::IGNEOUS, "Igneous (Sub)", -5, 100, Material::RockType::IGNEOUS, 2, 0, 270);
		chanceUpgrades[1][0] = ignSub;
		Upgrade sedSub(Upgrade::Target::SEDIMENTARY, "Sedimentary (Sub)", -5, 100, Material::RockType::SEDIMENTARY, 2, 160, 270);
		chanceUpgrades[1][1] = sedSub;
		Upgrade mtaSub(Upgrade::Target::METAMORPHIC, "Metamorphic (Sub)", -5, 100, Material::RockType::METAMORPHIC, 2,  320, 270);
		chanceUpgrades[1][2] = mtaSub;
		Upgrade extSub(Upgrade::Target::EXTRATERRESTRIAL, "Extraterrestrial (Sub)", -1, 100, Material::RockType::EXTRATERRESTRIAL, 2, 480, 270);
		chanceUpgrades[1][3] = extSub;
		Upgrade metSub(Upgrade::Target::METAL, "Metal (Sub)", -1, 100, Material::RockType::METAL, 2, 640, 270);
		chanceUpgrades[1][4] = metSub;

		// Initialize meta progression upgrades
		Upgrade incSel(Upgrade::Target::SELECTION, "Sizes (Add)", 100, 100, 100, 100, 100, 2, 0, 340);
		metaUpgrades[0] = incSel;
		Upgrade decSel(Upgrade::Target::SELECTION, "Sizes (Sub)", 10, 10, 10, 10, 10, 1, 200, 340);
		metaUpgrades[1] = decSel;
		Upgrade incDiff(Upgrade::Target::DIFFICULTY, "Difficulty (Add)", 100, 100, 100, 100, 100, 2, 400, 340);
		metaUpgrades[2] = incDiff;
		Upgrade decDiff(Upgrade::Target::DIFFICULTY, "Difficulty (Sub)", 10, 10, 10, 10, 10, 1, 600, 340);
		metaUpgrades[3] = decDiff;

		
	}

	void UpgradeManager::OnMouseClick(int mouseX, int mouseY, Player& player)
	{
		int row = DetermineUpgradeRow(mouseY);
		if (row == 0)
		{
			// Guard Clause if no row was clicked
			return;
		}
		int column = DetermineUpgradeColumn(mouseX, row);

		Upgrade upgrade;
		if (row < 3)
		{
			upgrade = boulderUpgrades[row - 1][column - 1];
		}
		else if (row < 5) 
		{
			upgrade = chanceUpgrades[row - 3][column - 1];
		}
		else 
		{
			upgrade = metaUpgrades[column - 1];
		}
		
		if (upgrade.CanPurchase())
		{
			upgrade.Purchase(player);
			UpdateUpgradeCanPurchase(player);
		}
	}

	int UpgradeManager::DetermineUpgradeRow(int mouseY)
	{
		if (mouseY < 60 || mouseY > 400)
		{
			return 0;
		}
		else if (mouseY < 130)
		{
			return 1;
		}
		else if (mouseY < 200)
		{
			return 2;
		}
		else if (mouseY < 270)
		{
			return 3;
		}
		else if (mouseY < 340)
		{
			return 4;
		}
		else
		{
			return 5;
		}
	}

	int UpgradeManager::DetermineUpgradeColumn(int mouseX, int upgradeRow)
	{
		if (upgradeRow == 3 || upgradeRow == 4)
		{
			if (mouseX < 160)
			{
				return 1;
			}
			else if (mouseX < 320)
			{
				return 2;
			}
			else if (mouseX < 480)
			{
				return 3;
			}
			else if (mouseX < 640)
			{
				return 4;
			}
			else
			{
				return 5;
			}
		}
		else
		{
			if (mouseX < 200)
			{
				return 1;
			}
			else if (mouseX < 400)
			{
				return 2;
			}
			else if (mouseX < 600)
			{
				return 3;
			}
			else
			{
				return 4;
			}
		}
	}


	void UpgradeManager::UpdateUpgradeCanPurchase(Player& player)
	{
		// Update boulder upgrades
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				boulderUpgrades[j][i].UpdateCanPurchase(player);
			}
		}

		// Update chance upgrades
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				chanceUpgrades[j][i].UpdateCanPurchase(player);
			}
		}

		// Update meta upgrades
		for (int i = 0; i < 4; i++)
		{
			metaUpgrades[i].UpdateCanPurchase(player);
		}
	}


	void UpgradeManager::ResetTimesPurchased()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				boulderUpgrades[j][i].ResetTimesPurchased();
			}
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				chanceUpgrades[j][i].ResetTimesPurchased();
			}
		}

		for (int i = 0; i < 4; i++)
		{
			metaUpgrades[i].ResetTimesPurchased();
		}
	}


	void UpgradeManager::Draw(Surface* screen)
	{
		// Draw all upgrades by calling their draw method
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				boulderUpgrades[j][i].Draw(screen);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				chanceUpgrades[j][i].Draw(screen);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			metaUpgrades[i].Draw(screen);
		}
	}
}