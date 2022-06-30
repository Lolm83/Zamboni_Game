#pragma once

namespace Tmpl8
{
	enum ORIENTATION {
		RIGHT,
		LEFT,
		TOP,
		BOTTOM,
		TOP_RIGHT,
		TOP_LEFT,
		BOTTOM_RIGHT, 
		BOTTOM_LEFT,
	};

	class Barrier {
	public:
		Barrier(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, u32 color = 0x00ff00,
			ORIENTATION orientation = TOP);

		int m_x1;
		int m_y1;
		int m_x2;
		int m_y2;
		
		u32 m_color;
		float m_slope;
		ORIENTATION m_orientation;
		
		int GetMinX();
		int GetMaxX();
		int GetMinY();
		int GetMaxY();

		float angle; // to use eventually
	};


	Barrier::Barrier(int x1, int y1, int x2, int y2, u32 color, ORIENTATION orientation):
		m_color(color), m_orientation(orientation)
	{
		if (x1 >= 0 && x1 <= 800)
			m_x1 = x1;
		if (y1 >= 0 && y1 <= 512)
			m_y1 = y1;
		if (x2 >= 0 && x2 <= 800)
			m_x2 = x2;
		if (y2 >= 0 && y2 <= 512)
			m_y2 = y2;

		if (m_x2 != m_x1)
			m_slope = (m_y2 - m_y1) / (m_x2 - m_x1);
		else
			m_slope = 1000;
	}
	int Barrier::GetMinX() {
		if (m_x1 < m_x2)
			return m_x1;
		else
			return m_x2;
	}
	int Barrier::GetMaxX() {
		if (m_x1 > m_x2)
			return m_x1;
		else
			return m_x2;
	}
	int Barrier::GetMinY() {
		if (m_y1 < m_y2)
			return m_y1;
		else
			return m_y2;
	}
	int Barrier::GetMaxY() {
		if (m_y1 > m_y2)
			return m_y1;
		else
			return m_y2;
	}
}