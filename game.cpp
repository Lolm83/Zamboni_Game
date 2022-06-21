#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <ctime>
#include "utils.cpp"
#include <stdlib.h>
#include <vector>
#include "Oiler.cpp"

			// Zamboni Game
/*
			- THE PLAN -
	Player drives a zamboni around a hockey rink clearing the ice, needs to get 80% of it clear.
	Ice physics apply, player can accelerate, decelerate, and change the direction of the zamboni.
	Hockey players mill about the rink, if you hit them with the front of your zamboni, they die.
	If you hit them from the side or they hit you, they fall over, stay down for a bit, then get up.
	
	        - WHAT I NEED TO PROGRAM -
	- Collisions and drawing the Hockey Rink []
	- Ice Physics []
	- Player Controlled zamboni rotation + Acceleration/Deceleration []
	- Clear Ice Tracker + Zamboni ice clearing ability []
	- Hockey Players behaviour and simulation []
	- Main Menu + Difficulty settings []

			- NOTES -
	+ Screen size is fixed at 800 x 512
	+ 

*/
namespace Tmpl8
{
	bool game_over;

	class Player {
	public:
		int x;
		int y;
		int halflength;
		int halfwidth;
	};

	class Oiler;
	
	
	Player player;
	
	Oiler oiler1(100, 200, 0xffffff);
	Oiler oiler2(300, 200, 0x8008a5);
	Oiler oiler3(600, 50, 0xcc4400);
	
	std::vector<Oiler>::iterator iter;
	// And if you're wondering, yes, I bought the Michael Dawson book. 
	std::vector<Oiler> oilers;

	void Game::Init()
	{	
		game_over = false; 
		srand(time(NULL)); 

		//Storing my Hockey Players in a Vector because its much better than an array.
		
		oilers.push_back(oiler1);
		oilers.push_back(oiler2);
		oilers.push_back(oiler3);
		

	}

	void Game::Shutdown()
	{
	}

	void Game::Draw(Oiler* oiler)
	{
		int x = oiler->GetPosX();  int y = oiler->GetPosY(); 
		int halfwidth = oiler->GetHalfwidth(); int halflength = oiler->GetHalflength(); 
		u32 color = oiler->m_color;

		screen->Bar(x - halfwidth, y - halflength, x + halfwidth, y + halflength, color);
		screen->Bar(x - halfwidth, y - 0.25 * halflength, x + halfwidth, y + 0.1 * halflength, 0x2244dd);
	}

	Player Zamboni;


	void Game::Tick(float deltaTime)
	{
		if (!game_over)
		{
			
			screen->Clear(0x88aadd);
		
			// Oiler Behavoiur / Movement
			for (iter = oilers.begin(); iter != oilers.end(); ++iter)
			{
				iter->TickTimer(deltaTime);

				if (iter->GetTimer() > 2000)
				{
					int crazy = rand();
					iter->m_ddx = ((-25.f + (crazy % 50)) / 10000.f);
					crazy = rand();
					iter->m_ddy = ((-25.f + (crazy % 50)) / 10000.f);
					iter->SetTimer(0);
				}

				iter->Accelerate(iter->m_ddx, iter->m_ddy, deltaTime);
			}
			

			//Draw EVERYTHING
			for (iter = oilers.begin(); iter != oilers.end(); ++iter)
				Draw(&(*iter)); //Ugly, but i know no other way... 
		}
	}
};