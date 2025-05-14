#pragma once
#include "surface.h"
#include "player.h"
#include "material_manager.h"
#include "upgrade.h"

namespace Boulder
{
	class UpgradeManager
	{
	public:
		void Init();

		// Method handling Mouse Click while shopping
		void OnMouseClick(int mouseX, int mouseY, Player& player);

		// Determine Upgrade position (on mouse click)
		int DetermineUpgradeRow(int mouseY);
		int DetermineUpgradeColumn(int mouseX, int upgradeRow);

		// Updates if an upgrade can be purchased for every upgrade
		void UpdateUpgradeCanPurchase(Player& player);

		// Reset times purchased
		void ResetTimesPurchased();

		void Draw(Surface* screen);
	private:
		Upgrade boulderUpgrades[2][4];
		Upgrade chanceUpgrades[2][5];
		Upgrade metaUpgrades[4];


	};

	extern UpgradeManager upgradeManager;
}