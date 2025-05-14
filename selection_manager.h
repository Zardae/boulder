#pragma once
#include "material.h"
#include "player.h"
#include "surface.h"
#include "progression_manager.h"

namespace Boulder
{
	class SelectionManager
	{
	public:
		// Initialize a selection of 3 Boudlers
		void InitSelection();

		// Select one of the given Boulders
		// Returns true if successfully selected
		bool Select(Player& player, int selection);
		
		// Returns the number of the selected Boulder
		// Returns 0 if no Boulder selected
		int DetermineSelection(int mouseX, int mouseY);

		// Draws the boulders and information on the game window
		void Draw(Surface* screen);

		
	private:
		// Selection materials
		Material* mat1;
		Material* mat2;
		Material* mat3;

		// Selection sizes
		int size1 = 0;
		int size2 = 0;
		int size3 = 0;

		// Selection costs
		int cost1 = 0;
		int cost2 = 0;
		int cost3 = 0;

		// Drawing and selection related constants
		const int pos1X = 199;
		const int pos2X = 399;
		const int pos3X = 599;

		const int posY = 255;
	};

	extern SelectionManager selectionManager;
}