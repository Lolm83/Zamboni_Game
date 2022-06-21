#pragma once

namespace Tmpl8
{

	class Oiler {
	public:
		Oiler(int x = 0, int y = 0, u32 color = 0x00ff00, int halfwidth = 5,
			  int halflength = 10, float syncopation = (rand() % 2000));

		void Accelerate(float ddx, float ddy, float dt);
		void TickTimer(float dt);

		static int GetTotal();
		int GetPosX() const;
		int GetPosY() const;
		int GetHalfwidth() const;
		int GetHalflength() const; 
		float GetTimer() const;
		float GetXAcceleration() const;
		float GetYAcceleration() const;
		
		void SetTimer(float time);
		void SetXAcceleration(float acceleration);
		void SetYAcceleration(float acceleration);
		
		u32 m_color;
		float m_ddx;
		float m_ddy;

	private:
		int m_x;
		int m_y;
		int m_halfwidth;
		int m_halflength;
		float m_dx;
		float m_dy;
		

		float m_timer;
		bool m_collisionX;
		bool m_collisionY;

		static int s_total;
	};

	int Oiler::s_total = 0;

	//Constructor 
	Oiler::Oiler(int x, int y, u32 color, int halfwidth, int halflength, float syncopation):
		m_halfwidth(halfwidth),
		m_halflength(halflength),
		m_color(color),
		m_collisionX(false),
		m_collisionY(false),
		m_timer(syncopation),
		m_ddx(0),
		m_ddy(0)
	{
		if (x - halfwidth >= 0 || x + halfwidth <= 800)
			m_x = x;
		else m_x = 400;
		if (y - halflength >= 0 || y + halflength <= 512)
			m_y = y;
		else m_y = 256;
		++s_total;
		m_dx = 0, m_dy = 0;
	}

	// "Get" Member Functions (Pretty Barebones)
	int Oiler::GetPosX() const
	{
		return m_x;
	}
	int Oiler::GetPosY() const
	{
		return m_y;
	}
	int Oiler::GetHalfwidth() const
	{
		return m_halfwidth;
	}
	int Oiler::GetHalflength() const
	{
		return m_halflength;
	}
	float Oiler::GetTimer() const 
	{
		return m_timer;
	}
	float Oiler::GetXAcceleration() const
	{
		return m_ddx;
	}
	float Oiler::GetYAcceleration() const
	{
		return m_ddy;
	}

	//Static "Get" Member Functions (Also Pretty Barebones)
	int Oiler::GetTotal()
	{
		return s_total;
	}

	// "Set" Member Functions (Also Simple)
	void Oiler::SetTimer(float time)
	{
		if (time >= 0)
		{
			m_timer = time;
		}
	}
	void Oiler::SetXAcceleration(float acceleration)
	{
		if (acceleration < 0.001 && acceleration > -0.001)
			m_ddx = acceleration;
	}
	void Oiler::SetYAcceleration(float acceleration)
	{
		if (acceleration < 0.001 && acceleration > -0.001)
			m_ddx = acceleration;
	}

	// Functions to modify data members
	void Oiler::Accelerate(float ddx, float ddy, float dt)
	{
		m_dx += ddx * dt; m_dy += ddy * dt;


		// collisions are in here TEMPORARILY!!! Make an AABB collision function somewhere else!
		{
			if (m_x + m_halfwidth + m_dx * dt <= 800 && m_x - m_halfwidth + m_dx * dt >= 0)
				m_x += m_dx * dt;
			else if (m_x + m_halfwidth + m_dx * dt > 800) {
				m_x = 800 - m_halfwidth;
				m_dx = -m_dx;
				m_collisionX = true;
			}
			else {
				m_x = 0 + m_halfwidth;
				m_dx = -m_dx;
				m_collisionX = true;
			}

			if (m_y + m_halflength + m_dy * dt <= 512 && m_y - m_halflength + m_dy * dt >= 0)
				m_y += m_dy * dt;
			else if (m_y + m_halflength + m_dy * dt > 512) {
				m_y = 512 - m_halflength;
				m_dy = -m_dy;
				m_collisionY = true;
			}
			else {
				m_y = 0 + m_halflength;
				m_dy = -m_dy;
				m_collisionY = true;
			}

			if (m_collisionX)
			{
				m_ddx = -m_ddx * 0.3f;
				m_collisionX = false;
			}
			if (m_collisionY)
			{
				m_ddy = -m_ddy * 0.3f;
				m_collisionY = false;
			}	
		}

		m_dx *= 0.9;
		m_dy *= 0.9;
	}
	void Oiler::TickTimer(float dt)
	{
		m_timer += dt;
	}
}
