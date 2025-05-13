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
		obstacleManager.Init();
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
		case State::UPGRADING:
			


			DrawUpgrading();
			break;
		case State::SELECTING:


			DrawSelecting();
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
			obstacleManager.OnTick(distance);
			smallDistanceTravelled -= distance;

			// Check for collision
			// These calculations may seem a bit weird. (5 + 2 * player.GetSize()) is the radius of the boulder.
			centerX = BoulderX + 5 + 1 * player.GetSize();	
			// The Boulder is 10 pixels further down than the actual floor, to give the impression of a slight 2.5D Perspective.
			// So we need to subtract the radius again to get the centers y value.
			centerY = FloorY + 10 - (5 + 1 * player.GetSize());

			if (obstacleManager.Collided(centerX, centerY, (1 + player.GetSize())))
			{
				state = Collision();
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

	// -----------------------------------------------------------
	// Collision Method
	// -----------------------------------------------------------

	Game::State Game::Collision() {

		// Damage Calculation
		Obstacle o = obstacleManager.GetObstacles()[0];
		
		float offDiff = player.CalcAtk() - o.CalcDef();
		float defDiff = player.CalcDef() - o.CalcAtk();
		float damageTaken = std::abs(offDiff) + std::abs(defDiff);

		if (offDiff > 0 && defDiff > 0)
		{
			// Reduce damage taken if both "struggles" are won
			damageTaken /= 4;
		}
		else if (offDiff < 0 && defDiff < 0) {
			// Increasing damage taken if both "struggles" are lost
			damageTaken *= 4;
		}

		float remainingIntegrity = player.RemainingIntegrity(damageTaken);
		
		// Apply slowdown from Obstacle
		float slowdown = o.CalcSlowdown();
		player.DecreaseSpeed(slowdown);

		// Handling result
		if (remainingIntegrity == 0) {
			// Boulder was destroyed
			if (offDiff > 0) {
				// Boulder dealt enough damage to destroy Obstacle
				Obstacle removed = obstacleManager.RemoveObstacle();
				player.AddCurrency(removed.GetMaterial().GetRockType(), removed.GetReward());
			}
			return State::BROKEN;
		}
		else if (player.GetSpeed() == 0) {
			// Boulder was stopped
			if (offDiff > 0) {
				// Dealt enough damage to destroy Obstacle
				Obstacle removed = obstacleManager.RemoveObstacle();
				player.AddCurrency(removed.GetMaterial().GetRockType(), removed.GetReward());
			}
			return State::STOPPING;
		}

		Obstacle removed = obstacleManager.RemoveObstacle();
		player.AddCurrency(removed.GetMaterial().GetRockType(), removed.GetReward());
		return State::ROLLING;

	}

	// -----------------------------------------------------------
	// Draw Game State Methods
	// -----------------------------------------------------------

	void Game::DrawStart()
	{
		// Explanation Text
		std::string startupText = "Press D to start rolling";
		screen->Print(startupText.data(), 340, 254, 0xffffff);

		// Objects
		DrawBoulder();
		DrawObstacles();


	}

	void Game::DrawUpgrading()
	{


		DrawStats();
		DrawCurrencies();
	}


	void Game::DrawSelecting()
	{

		DrawStats();
		DrawCurrencies();
	}

	void Game::DrawRolling()
	{
		// Objects
		DrawBoulder();
		DrawObstacles();

		// Info
		DrawStats();
		DrawCurrencies();
	}


	void Game::DrawStopping()
	{
		// Objects
		DrawBoulder();


		// Info
		DrawStats();
		DrawCurrencies();
	}

	void Game::DrawBroken()
	{
		// Objects
		DrawObstacles();

		// Info
		DrawStats();
		DrawCurrencies();
	}


	// Draws Boulder
	void Game::DrawBoulder()
	{
		int diameter = 1 + 2 * (1 + player.GetSize());

		// Boulder
		screen->DrawBoulder(BoulderX, ObjectY, 1 + player.GetSize(), player.GetColorCode());

		// Health bar
		// Scales with diameter
		int healthBarY = ObjectY - (diameter + 40);
		// Bar
		int healthBarLength = (int)diameter * (player.GetIntegrity() / player.GetMaxIntegrity());
		screen->Bar(BoulderX - 1, healthBarY, BoulderX - 1 + healthBarLength, healthBarY + 9, 0xaa0000);
		// Outline
		screen->Box(BoulderX - 1, healthBarY - 1, BoulderX + diameter, healthBarY + 10, 0xffffff);

		// Speed bar
		// Scales with diameter
		// Bar
		int speedBarLength = (int)diameter * (player.GetSpeed() / player.GetMaxSpeed());
		screen->Bar(BoulderX - 1, healthBarY + 20, BoulderX - 1 + speedBarLength, healthBarY + 29, 0x0000aa);
		// Outline
		screen->Box(BoulderX - 1, healthBarY + 19, BoulderX + diameter, healthBarY + 30, 0xffffff);
	}


	// Draws obstacles
	void Game::DrawObstacles()
	{
		Obstacle* obstacles = obstacleManager.GetObstacles();
		int obstacleAmount = obstacleManager.GetObstacleAmount();

		for (int i = 0; i < obstacleAmount; i++)
		{
			Obstacle o = obstacles[i];
			screen->Bar(o.GetX(), o.GetY(), o.GetX() + o.GetSize(), FloorY + 10, o.GetColor());
		}
	}

	// Draws Boulder Stats in top left corner

	void Game::DrawStats()
	{
		// Draw box around stats
		screen->Box(0, 0, 399, 55, 0xffffff);

		// Left column
		std::string stats = "Boulder Stats (roughly, rounded down)";

		std::string densityStr = "Density:";
		std::string densityValStr = std::to_string(player.GetDensityInt());

		std::string brittlenessStr = "Brittleness:";
		std::string brittlenessValStr = std::to_string(player.GetBrittlenessInt());

		std::string hardnessStr = "Hardness:";
		std::string hardnessValStr = std::to_string(player.GetHardnessInt());

		std::string smoothnessStr = "Smoothness:";
		std::string smoothnessValStr = std::to_string(player.GetSmoothnessInt());

		const int labelXL = 5;
		const int valueXL = 100;

		screen->Print(stats.data(), labelXL, 5, 0xffffff);
		screen->Print(densityStr.data(), labelXL, 15, 0xffffff);
		screen->Print(densityValStr.data(), valueXL, 15, 0xffffff);
		screen->Print(brittlenessStr.data(), labelXL, 25, 0xffffff);
		screen->Print(brittlenessValStr.data(), valueXL, 25, 0xffffff);
		screen->Print(hardnessStr.data(), labelXL, 35, 0xffffff);
		screen->Print(hardnessValStr.data(), valueXL, 35, 0xffffff);
		screen->Print(smoothnessStr.data(), labelXL, 45, 0xffffff);
		screen->Print(smoothnessValStr.data(), valueXL, 45, 0xffffff);

		// Right column
		std::string sizeStr = "Size:";
		std::string sizeValStr = std::to_string(player.GetSize());

		std::string maxSpeedStr = "Max Speed:";
		std::string maxSpeedValStr = std::to_string((int)player.GetMaxSpeed());

		std::string maxIntegrityStr = "Max Integrity:";
		std::string maxIntegrityValStr = std::to_string((int)player.GetMaxIntegrity());

		const int labelXR = 205;
		const int valueXR = 300;

		screen->Print(sizeStr.data(), labelXR, 15, 0xffffff);
		screen->Print(sizeValStr.data(), valueXR, 15, 0xffffff);
		screen->Print(maxSpeedStr.data(), labelXR, 25, 0xffffff);
		screen->Print(maxSpeedValStr.data(), valueXR, 25, 0xffffff);
		screen->Print(maxIntegrityStr.data(), labelXR, 35, 0xffffff);
		screen->Print(maxIntegrityValStr.data(), valueXR, 35, 0xffffff);
	}


	// Draws currency box in the top right corner
	void Game::DrawCurrencies()
	{
		// Draw box around currencies
		screen->Box(540, 0, 799, 55, 0xffffff);

		// Draw currencies in top right corner
		// Bal stands for Balance
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



		screen->Print(igneousStr.data(), 550, 5, 0xaaaaaa);
		screen->Print(igneousBalStr.data(), 680, 5, 0xaaaaaa);
		screen->Print(sedimentaryStr.data(), 550, 15, 0xb29082);
		screen->Print(sedimentaryBalStr.data(), 680, 15, 0xb29082);
		screen->Print(metamorphicStr.data(), 550, 25, 0x808080);
		screen->Print(metamorphicBalStr.data(), 680, 25, 0x808080);
		screen->Print(extraterrestrialStr.data(), 550, 35, 0x505060);
		screen->Print(extraterrestrialBalStr.data(), 680, 35, 0x505060);
		screen->Print(metalStr.data(), 550, 45, 0x606070);
		screen->Print(metalBalStr.data(), 680, 45, 0x606070);
	}

};