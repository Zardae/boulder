#include "game.h"
#include "surface.h"
#include "material.h"
#include <cstdio> //printf
#include <iostream>
#include <windows.h>

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
		screen->Clear(0);
		
		// Draw "Floor"
		screen->Bar(0, FloorY, 800, 512, 0x734222);

		switch (state) {
		case State::START:
			DrawStart();

			if (GetAsyncKeyState('D'))
			{
				player.Accelerate(deltaTime);
				state = State::ROLLING;
			}

			break;
		case State::ROLLING:

			if (GetAsyncKeyState('D'))
			{
				player.Accelerate(deltaTime);
			}
			else if (GetAsyncKeyState('A'))
			{
				player.Decelerate(deltaTime);
				if (player.GetSpeed() == 0)
				{
					state = State::START;
				}
			}


			DrawRolling();
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

	// Collision Method
	Game::State Game::Collision(Player player, Obstacle obstacle) {
		return State::ROLLING;
	}


	// Draw Game State Methods

	void Game::DrawStart()
	{
		// Explanation Text
		screen->Print("Press D to start rolling", 340, 254, 0xffffff);

		// Objects
		screen->DrawBoulder(BoulderX, FloorY + 10, 5 + 2 * player.GetSize(), player.GetColorCode());


	}

	void Game::DrawRolling()
	{
		// Objects
		screen->DrawBoulder(BoulderX, FloorY + 10, 5 + 2 * player.GetSize(), player.GetColorCode());

		//Draw currencies in top right corner
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
	}
};