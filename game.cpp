#include "game.h"
#include "surface.h"
#include "material.h"
#include <cstdio> //printf
#include <iostream>

namespace Boulder
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		MaterialManager materialManager;

		player;
		this->state = START;
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		switch (state) {
		case State::START:

			DrawStart();
			break;
		}





		// clear the graphics window
		//screen->Clear(0);
		// print something in the graphics window
		/*
		screen->Circle(10, 10, 10, 0xffffff);
		screen->Print("igneous:", 550, 10, 0xffffff);
		screen->Print("1000000000", 680, 10, 0xffffff);
		screen->Print("sedimentary:", 550, 20, 0xffffff);
		screen->Print("1000000000", 680, 20, 0xffffff);
		screen->Print("metamorphic:", 550, 30, 0xffffff);
		screen->Print("1000000000", 680, 30, 0xffffff);
		screen->Print("extraterrestrial:", 550, 40, 0xffffff);
		screen->Print("1000000000", 680, 40, 0xffffff);
		screen->Print("metal:", 550, 50, 0xffffff);
		screen->Print("1000000000", 680, 50, 0xffffff);
		*/
	}



	// Draw Game State Methods

	void Game::DrawStart()
	{
		screen->Clear(0);
		screen->Print("Press D to start rolling", 340, 254, 0xffffff);
		screen->DrawBoulder(player, BoulderX, FloorY);
	}
};