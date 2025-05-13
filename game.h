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
	State Collision();

	// Draw Game State
	void DrawStart();
	void DrawUpgrading();
	void DrawSelecting();
	void DrawRolling();
	void DrawStopping();
	void DrawBroken();

	// Boulder helper
	void DrawBoulder();

	// Obstacle helper
	void DrawObstacles();

	// Stats helper
	void DrawStats();

	// Currency helper
	void DrawCurrencies();

private:
	Surface* screen;
	State state;
	//MaterialManager materialManager;
	//ObstacleManager obstacleManager;
	Player player;

	// Member to keep track distance travelled
	// NOT the total distance, each fully travelled unit will be subtracted!
	float smallDistanceTravelled;

	// The following 3 members exist due to an error message popping up when
	// initializing and using these variables inside a switch statement
	// Pixels travelled this frame
	int distance;

	// Member to keep track of the Boulder Center (For possible movement variation)
	int centerX;
	int centerY;


	// Member to count frames passed in current state
	int frameCounter;

	// Constants for Boulder Placement
	const int BoulderX = 50;
	const int FloorY = 480;
	const int ObjectY = FloorY + 10;
};
}; // namespace Boulder