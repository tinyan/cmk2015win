#include <windows.h>

#include "area.h"


CArea::CArea()
{
	SetArea(0,0,1,1);
}

CArea::~CArea()
{
	End();
}

void CArea::End(void)
{
}

void CArea::SetArea(int x,int y,int sizeX,int sizeY)
{
	m_x = x;
	m_y = y;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
}

void CArea::SetArea(POINT pt,SIZE sz)
{
	SetArea(pt.x,pt.y,sz.cx,sz.cy);
}

void CArea::SetArea(RECT rc)
{
	SetArea(rc.left,rc.top,rc.right,rc.bottom);
}

BOOL CArea::CheckInArea(int x,int y,int sizeX ,int sizeY)
{
	//simple
	if ((x<m_x) || (x>=m_x+m_sizeX) || (y<m_y) || (y>=m_y+m_sizeY)) return FALSE;

	return TRUE;
}

BOOL CArea::CheckInArea(POINT pt,int sizeX,int sizeY )
{
	return CheckInArea(pt.x,pt.y,sizeX,sizeY);
}

RECT CArea::GetRect(void)
{
	RECT rc;
	rc.left = m_x;
	rc.top = m_y;
	rc.right = m_sizeX;
	rc.bottom = m_sizeY;

	return rc;
}

int CArea::CheckKabe(POINT pt,int tate)
{
	if (tate)
	{
		if ((pt.y == m_y) || (pt.y == m_y+m_sizeY-1)) return 1;
		if ((pt.x > m_x) && (pt.x < m_x+m_sizeX-1))
		{
			if ((pt.y == m_y+1) || (pt.y == m_y+m_sizeY-2)) return 1;
		}
	}
	else
	{
		if ((pt.x == m_x) || (pt.x == m_x+m_sizeX-1)) return 1;
		if ((pt.y > m_y) && (pt.y < m_y+m_sizeY-1))
		{
			if ((pt.x == m_x+1) || (pt.x == m_x+m_sizeX-2)) return 1;
		}
	}

	return 0;

}


/*_*/



