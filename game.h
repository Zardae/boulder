#pragma once
#include "material_manager.h"
#include "obstacle_manager.h"
#include "player.h"

namespace Boulder {

class Surface;
class Game
{
public:
	enum State {
		START,			// Initial State when booting the game
		UPGRADING,		// Shop State
		SELECTING,		// Boulder Select
		ROLLING,		// Rolling State
		STOPPING,		// Transition State Rolling to Upgrade
		BROKEN			// Transition State Rolling to Boulder Select
	};
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	// Moving Mouse updates variables to current position
	void MouseMove(int x, int y) { mousex = x, mousey = y; }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
	int mousex, mousey;

	// Collision
	State Collision(Player player, Obstacle obstacle);

	// Draw Game State
	void DrawStart();
	void DrawUpgrading();
	void DrawSelecting();
	void DrawRolling();
	void DrawStopping();
	void DrawBroken();

private:
	Surface* screen;
	State state;
	MaterialManager *materialManager;
	Player player;

	const int BoulderX = 50;

	const int FloorY = 480;
};
}; // namespace Boulder