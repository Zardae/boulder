#include "selection_manager.h"

namespace Boulder
{
	SelectionManager selectionManager;

	void SelectionManager::InitSelection()
	{
		mat1 = progressionManager.GenBoulderMaterial();
		mat2 = progressionManager.GenBoulderMaterial();
		mat3 = progressionManager.GenBoulderMaterial();

		size1 = progressionManager.GenBoulderSize(mat1);
		size2 = progressionManager.GenBoulderSize(mat2);
		size3 = progressionManager.GenBoulderSize(mat3);


		const int BaseCost = 10;
		cost1 = BaseCost * size1;
		cost2 = BaseCost * size2;
		cost3 = BaseCost * size3;
	}

	bool SelectionManager::Select(Player& player, int selection)
	{
		switch (selection) {
		case 1:
			if (cost1 <= player.CurrByType(mat1->GetRockType()))
			{
				player.SubCurrency(mat1->GetRockType(), cost1);
				player.InitNewBoulder(mat1, size1);
				return true;
			}
		case 2:
			if (cost2 <= player.CurrByType(mat2->GetRockType()))
			{
				player.SubCurrency(mat2->GetRockType(), cost1);
				player.InitNewBoulder(mat2, size1);
				return true;
			}
		case 3:
			if (cost3 <= player.CurrByType(mat3->GetRockType()))
			{
				player.SubCurrency(mat3->GetRockType(), cost1);
				player.InitNewBoulder(mat3, size1);
				return true;
			}
		}

		return false;
	}

	int SelectionManager::DetermineSelection(int mouseX, int mouseY)
	{
		// Reverse order to account for overlap
		
		// Check if mouse position is inside a boulder
		if (pow((mouseX - pos3X), 2) + pow((mouseY - posY), 2) <= pow((1 + size3), 2))
		{
			return 3;
		}
		else if (pow((mouseX - pos2X), 2) + pow((mouseY - posY), 2) <= pow((1 + size2), 2))
		{
			return 2;
		}
		else if (pow((mouseX - pos1X), 2) + pow((mouseY - posY), 2) <= pow((1 + size1), 2))
		{
			return 1;
		}
		return 0;
	}

	void SelectionManager::Draw(Surface* screen)
	{
		// Draw Boulder Preview
		int rad1 = 1 + size1;
		screen->Circle(pos1X - rad1, posY - rad1, rad1, mat1->GetColorCode());
		int rad2 = 1 + size2;
		screen->Circle(pos2X - rad2, posY - rad2, rad2, mat2->GetColorCode());
		int rad3 = 1 + size3;
		screen->Circle(pos3X - rad3, posY - rad3, rad3, mat3->GetColorCode());

		// Draw Boulder Info
		std::string cost1str = std::to_string(cost1);
		std::string cost2str = std::to_string(cost2);
		std::string cost3str = std::to_string(cost3);

		std::string size1str = std::to_string(size1);
		std::string size2str = std::to_string(size2);
		std::string size3str = std::to_string(size3);

		screen->Print(mat1->GetName().data(), pos1X - rad1, posY + rad1 + 5, mat1->GetColorCode());
		screen->Print(cost1str.data(), pos1X - rad1, posY + rad1 + 15, mat1->GetColorCode());
		screen->Print(size1str.data(), pos1X - rad1, posY + rad1 + 25, 0xffffff);

		screen->Print(mat2->GetName().data(), pos2X - rad2, posY + rad2 + 5, mat2->GetColorCode());
		screen->Print(cost2str.data(), pos2X - rad2, posY + rad2 + 15, mat2->GetColorCode());
		screen->Print(size2str.data(), pos2X - rad2, posY + rad2 + 25, 0xffffff);

		screen->Print(mat3->GetName().data(), pos3X - rad3, posY + rad3 + 5, mat3->GetColorCode());
		screen->Print(cost3str.data(), pos3X - rad3, posY + rad3 + 15, mat3->GetColorCode());
		screen->Print(size3str.data(), pos3X - rad3, posY + rad3 + 25, 0xffffff);
	}
}