#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <ctime>
#include "utils.cpp"
#include <stdlib.h>
#include <vector>
#include "Oiler.cpp"
#include "Barrier.cpp"

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

	

	class Barrier;
	class Oiler;
	
	Player player;
	
	// Initializing Barriers 
	
		Barrier barrier1(150, 150, 650, 150, 0x00ff00, TOP);
		Barrier barrier2(650, 150, 750, 216, 0x00ff00, TOP_RIGHT);
		Barrier barrier3(750, 216, 750, 414, 0x00ff00, RIGHT);
		Barrier barrier4(650, 480, 750, 414, 0x00ff00, BOTTOM_RIGHT);

		Barrier barrier5(150, 480, 650, 480, 0x00ff00, BOTTOM);
		Barrier barrier6(150, 480, 50, 414, 0x00ff00, BOTTOM_LEFT);
		Barrier barrier7(50, 414, 50, 216, 0x00ff00, LEFT);
		Barrier barrier8(150, 150, 50, 216, 0x00ff00, TOP_LEFT);
	
	std::vector<Barrier>::iterator barrier_iter;
	std::vector<Barrier> barriers;

	// Initializing Oilers
	
		Oiler oiler1(100, 200, 0xffffff);
		Oiler oiler2(300, 200, 0x8008a5);
		Oiler oiler3(600, 350, 0xcc4400);
	

	std::vector<Oiler>::iterator oiler_iter;
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

		// same goes for barriers
		barriers.push_back(barrier1);
		barriers.push_back(barrier2);
		barriers.push_back(barrier3);
		barriers.push_back(barrier4);
		barriers.push_back(barrier5);
		barriers.push_back(barrier6);
		barriers.push_back(barrier7);
		barriers.push_back(barrier8);
	}

	void Game::Shutdown()
	{
	}


	

	void Game::DrawOiler(Oiler* oiler)
	{
		int x = oiler->GetPosX();  int y = oiler->GetPosY(); 
		int halfwidth = oiler->GetHalfwidth(); int halflength = oiler->GetHalflength(); 
		u32 color = oiler->m_color;

		screen->Bar(x - halfwidth, y - halflength, x + halfwidth, y + halflength, color);
		screen->Bar(x - halfwidth, y - 0.25 * halflength, x + halfwidth, y + 0.1 * halflength, 0x2244dd);
	}

	void Game::DrawBarrier(Barrier* barrier)
	{
		int x1 = barrier->m_x1; int y1 = barrier->m_y1;
		int x2 = barrier->m_x2; int y2 = barrier->m_y2;
		ORIENTATION orientation = barrier->m_orientation; u32 color = barrier->m_color;

		screen->Line(x1, y1, x2, y2, color);

		switch (orientation)
		{
		case RIGHT:
			screen->Line(x1 + 1, y1, x2 + 1, y2, color);
			screen->Line(x1 + 2, y1, x2 + 2, y2, color);
		case TOP_RIGHT:
			screen->Line(x1 + 1, y1, x2 + 1, y2, color);
			screen->Line(x1 + 2, y1, x2 + 2, y2, color);
		case BOTTOM_RIGHT:
			screen->Line(x1 + 1, y1, x2 + 1, y2, color);
			screen->Line(x1 + 2, y1, x2 + 2, y2, color);
		case LEFT:
			screen->Line(x1 - 1, y1, x2 - 1, y2, color);
			screen->Line(x1 - 2, y1, x2 - 2, y2, color);
		case TOP_LEFT:
			screen->Line(x1 - 1, y1, x2 - 1, y2, color);
			screen->Line(x1 - 2, y1, x2 - 2, y2, color);
		case BOTTOM_LEFT:
			screen->Line(x1 - 1, y1, x2 - 1, y2, color);
			screen->Line(x1 - 2, y1, x2 - 2, y2, color);
		case TOP:
			screen->Line(x1, y1 - 1, x2, y2 - 1, color);
			screen->Line(x1, y1 - 2, x2, y2 - 2, color);
		case BOTTOM:
			screen->Line(x1, y1 + 1, x2, y2 + 1, color);
			screen->Line(x1, y1 + 2, x2, y2 + 2, color);
		
		default:
			break;
		}
	}

	void Game::Tick(float deltaTime)
	{
		if (!game_over)
		{
			
			
			screen->Clear(0x88aadd);
		
			// Create the Ice Rink
			

			// Oiler Random Behavoiur / Movement
			
			for (oiler_iter = oilers.begin(); oiler_iter != oilers.end(); ++oiler_iter)
			{
				oiler_iter->TickTimer(deltaTime);

				if (oiler_iter->GetTimer() > 2000)
				{
					int crazy = rand();
					oiler_iter->m_ddx = ((-5.f + (crazy % 10)) / 10000.f);
					crazy = rand();
					oiler_iter->m_ddy = ((-5.f + (crazy % 10)) / 10000.f);
					oiler_iter->SetTimer(0);
				}
			}
			
			
			// Oiler / Barrier Collisions

			for (oiler_iter = oilers.begin(); oiler_iter != oilers.end(); ++oiler_iter)
			{	
				int hy = oiler_iter->GetHalflength();
				int hx = oiler_iter->GetHalfwidth();
				int x_right = oiler_iter->GetPosX() + hx;
				int x_left = oiler_iter->GetPosX() - hx;
				int y_top = oiler_iter->GetPosY() - hy;
				int y_bottom = oiler_iter->GetPosY() + hy;
				
				
				for (barrier_iter = barriers.begin(); barrier_iter != barriers.end(); ++barrier_iter)
				{


					switch (barrier_iter->m_orientation)
					{
					case RIGHT:
						if (x_right >= barrier_iter->m_x1 && y_top >= barrier_iter->GetMinY()
							&& y_bottom <= barrier_iter->GetMaxY())
						{
							oiler_iter->SetPosX(barrier_iter->GetMaxX() - hx);
							oiler_iter->m_collisionX = true;
						}
						break;
					case LEFT:
						if (x_left <= barrier_iter->m_x1 && y_top >= barrier_iter->GetMinY()
							&& y_bottom <= barrier_iter->GetMaxY())
						{
							oiler_iter->SetPosX(barrier_iter->GetMaxX() + hx);
							oiler_iter->m_collisionX = true;
						}
						break;
					case TOP:
						if (y_top <= barrier_iter->m_y1 && x_left >= barrier_iter->GetMinX()
							&& x_right <= barrier_iter->GetMaxX())
						{
							oiler_iter->SetPosY(barrier_iter->GetMaxY() + hy);
							oiler_iter->m_collisionY = true;
						}
						break;
					case BOTTOM:
						if (y_bottom >= barrier_iter->m_y1 && x_left >= barrier_iter->GetMinX()
							&& x_right <= barrier_iter->GetMaxX())
						{
							oiler_iter->SetPosY(barrier_iter->GetMinY() - hy);
							oiler_iter->m_collisionY = true;
						}
						break;
					}
				}
				
				oiler_iter->Accelerate(oiler_iter->m_ddx, oiler_iter->m_ddy, deltaTime);
			}
			


			//Draw EVERYTHING
			
			for (barrier_iter = barriers.begin(); barrier_iter != barriers.end(); ++barrier_iter)
				DrawBarrier(&(*barrier_iter));
			

			for (oiler_iter = oilers.begin(); oiler_iter != oilers.end(); ++oiler_iter)
				DrawOiler(&(*oiler_iter)); //Ugly, but i know no other way... 
		}
	}
};