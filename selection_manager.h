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
		void Init();

		void Select1(Player& player);
		void Select2(Player& player);
		void Select3(Player& player);

		void Draw(Surface& screen);
	private:

	};
}