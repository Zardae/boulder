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
					state = State::STOPPING;
				}
			}
			
			// Calculate distance travelled
			smallDistanceTravelled += player.GetSpeed() * deltaTime / 1000;
			distance = (int)smallDistanceTravelled;
			obstacleManager.OnTick(distance, materialManager);
			smallDistanceTravelled -= distance;

			// Check for collision
			// These calculations may seem a bit weird. (5 + 2 * player.GetSize()) is the radius of the boulder.
			centerX = BoulderX + 5 + 2 * player.GetSize();	
			// The Boulder is 10 pixels further down than the actual floor, to give the impression of a slight 2.5D Perspective.
			// So we need to subtract the radius again to get the centers y value.
			centerY = FloorY + 10 - (5 + 2 * player.GetSize());

			if (obstacleManager.Collided(centerX, centerY, (5 + 2 * player.GetSize())))
			{
				Collision();
			}

			DrawRolling();
			break;
		case State::STOPPING:


			DrawStopping();

			frameCounter++;
			if (frameCounter > 150)
			{
				state = State::UPGRADING;
				frameCounter = 0;
			}
			break;
		case State::BROKEN:

			DrawBroken();

			frameCounter++;
			if (frameCounter > 150)
			{
				state = State::SELECTING;
				frameCounter = 0;
			}

			break;
		}

	}

	// Collision Method
	Game::State Game::Collision() {
		return State::ROLLING;
	}


	// Draw Game State Methods

	void Game::DrawStart()
	{
		// Explanation Text
		std::string startupText = "Press D to start rolling";
		screen->Print(startupText.data(), 340, 254, 0xffffff);

		// Objects
		screen->DrawBoulder(BoulderX, FloorY + 10, 5 + 2 * player.GetSize(), player.GetColorCode());


	}

	void Game::DrawRolling()
	{
		// Objects
		screen->DrawBoulder(BoulderX, FloorY + 10, 5 + 2 * player.GetSize(), player.GetColorCode());


		// Balance
		DrawCurrencies();
	}


	void Game::DrawStopping()
	{
		// Objects
		screen->DrawBoulder(BoulderX, FloorY + 10, 5 + 2 * player.GetSize(), player.GetColorCode());


		// Balance
		DrawCurrencies();
	}

	void Game::DrawBroken()
	{
		// Objects


		// Balance
		DrawCurrencies();
	}

	// Draws obstacles
	void Game::DrawObstacles()
	{

	}


	// Draws currency box in the top right corner
	void Game::DrawCurrencies()
	{
		// Draw box around currencies
		screen->Box(540, 0, 799, 60, 0xffffff);

		//Draw currencies in top right corner
		std::string igneousStr = "Igneous";
		std::string igneousBalStr = std::to_string(player.GetIgneous());

		std::string sedimentaryStr = "Sedimentary";
		std::string sedimentaryBalStr = std::to_string(player.GetSedimentary());

		std::string metamorphicStr = "Metamorphic";
		std::string metamorphicBalStr = std::to_string(player.GetMetamorphic());

		std::string extraterrestrialStr = "Extraterrestrial";
		std::string extraterrestrialBalStr = std::to_string(player.GetExtraterrestrial());

		std::string metalStr = "Metal";
		std::string metalBalStr = std::to_string(player.GetMetal());



		screen->Print(igneousStr.data(), 550, 10, 0xaaaaaa);
		screen->Print(igneousBalStr.data(), 680, 10, 0xaaaaaa);
		screen->Print(sedimentaryStr.data(), 550, 20, 0xb29082);
		screen->Print(sedimentaryBalStr.data(), 680, 20, 0xb29082);
		screen->Print(metamorphicStr.data(), 550, 30, 0x808080);
		screen->Print(metamorphicBalStr.data(), 680, 30, 0x808080);
		screen->Print(extraterrestrialStr.data(), 550, 40, 0x505060);
		screen->Print(extraterrestrialBalStr.data(), 680, 40, 0x505060);
		screen->Print(metalStr.data(), 550, 50, 0x606070);
		screen->Print(metalBalStr.data(), 680, 50, 0x606070);
	}

};