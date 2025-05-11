#include "surface.h"
#include "game_object.h"
#include "game.h"

namespace Boulder
{
	GameObject::GameObject()
	{
		posx = 0;
		posy = 0;
	}

	GameObject::GameObject(int px, int py)
	{
		posx = py;
		posy = py;
	}


	GOBoulder::GOBoulder()
		: GameObject()
	{

	}
}