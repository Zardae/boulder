#pragma once
#include "surface.h"
#include "game.h"

namespace Boulder
{
	class GameObject
	{
	public:
		GameObject();
		GameObject(int px, int py);
		void Draw(Surface* screen);

	private:
		int posx;
		int posy;
	};

	class GOBoulder : GameObject
	{
	public:
		GOBoulder();
		Game::State Collide(GOObstacle obstacle);
		void OnDestroyed();
		void OnStopped();
		//void Draw(Surface* target)

	private:

	};

	class GOObstacle : GameObject
	{
	public:
		GOObstacle();
		GOObstacle(int psize);
	
	private:
		int size;
		int mass;
		float slowdown_factor;
		float hardness_factor;
	};
}