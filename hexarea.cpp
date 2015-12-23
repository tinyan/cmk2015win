#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"


#include "putChara.h"

#include "hexarea.h"


int CHexArea::m_houkouTable[]=
{
	0,-2,1,-1,1,1,0,2,-1,1,-1,-1
};

CHexArea::CHexArea()
{
	m_size.cx = 64;
	m_size.cy = 56;

	m_point.x = 0;
	m_point.y = 0;

	for (int j=0;j<64;j++)
	{
		for (int i=0;i<32;i++)
		{
			m_type[j][i] = 0;
			m_power[j][i] = 0;
		}
	}
	m_powerMax = 15000;

	m_hexPic = new CPutChara("sys\\ta_hex",4,3);
}

CHexArea::~CHexArea()
{
	End();
}

void CHexArea::End(void)
{
	ENDDELETECLASS(m_hexPic);
}

POINT CHexArea::GetAreaBlock(float fx,float fy)
{
	POINT pt;
	int x = (int)fx;
	int y = (int)fy;
	int dx = x - (m_point.x - m_size.cx / 2);
	int dy = y - (m_point.y - m_size.cy / 2);
	int nx = dx / ((m_size.cx * 3) / 2);
	int ny = dy / m_size.cy;
	int ax = dx % ((m_size.cx * 3) / 2);
	int ay = dy % m_size.cy;
	if (ax<m_size.cx)
	{
		int zx = ax - m_size.cx / 2;
		int zy = ay - m_size.cy / 2;

		if (( - (m_size.cy / (m_size.cx/2)) * zx - zy + m_size.cy) < 0)
		{
			//right up
			pt.x = nx*2+1;
			pt.y = ny*2-1;
		}
		else if (( - (m_size.cy / (m_size.cx/2)) * zx - zy - m_size.cy) > 0)
		{
			//left down
			pt.x = nx*2-1;
			pt.y = ny*2+1;
		}
		else if (( (m_size.cy / (m_size.cx/2)) * zx - zy + m_size.cy) < 0)
		{
			//left up
			pt.x = nx*2-1;
			pt.y = ny*2-1;
		}
		else if (( (m_size.cy / (m_size.cx/2)) * zx - zy - m_size.cy) > 0)
		{
			//right down
			pt.x = nx*2+1;
			pt.y = ny*2+1;
		}
		else
		{
			pt.x = nx*2;
			pt.y = ny*2;
		}
	}
	else
	{
		pt.x = nx * 2 + 1;
		if (ay < m_size.cy /2)
		{
			pt.y = ny*2 - 1;
		}
		else
		{
			pt.y = ny*2 + 1;
		}
	}

//	pt.x = 0;
//	pt.y = 0;

	return pt;
}

void CHexArea::PutHex(int x,int y)
{
	int type = 0;
	if ((x>=0) && (x<32) && (y>=0) && (y<64))
	{
		type = m_type[y][x];
	}
	int pw = 0;
	if ((x>=0) && (x<32) && (y>=0) && (y<64))
	{
		pw = m_power[y][x];
	}

	int playerenemy = -1;
	if (pw >= 10000) playerenemy = 0;
	if (pw <= -10000) playerenemy = 1;

	PutHex(x,y,type,playerenemy);

}

void CHexArea::PutHex(int nx,int ny,int type,int playerenemy)
{
	int d2 = 0;
	if (playerenemy == 0)
	{
		d2 = 1;
	}
	else if (playerenemy == 1)
	{
		d2 = 2;
	}
	else
	{
		d2 = 0;
	}

	POINT pt = GetHexPoint(nx,ny);
	if (pt.x<0) return;//error

	m_hexPic->Put(pt,type,d2);
}

void CHexArea::PutHex(int nx,int ny,int d)
{
	POINT pt = GetHexPoint(nx,ny);
	if (pt.x<0) return;//error

	m_hexPic->Put(pt,d,0);
}

POINT CHexArea::GetHexPoint(int nx,int ny)
{
	POINT pt;
	if (((nx+ny) % 2) == 1)
	{
		//error
		pt.x = - m_size.cx;
		pt.y = - m_size.cy;
	}
	else if ((ny % 2) == 0)
	{
		pt.x = (nx/2) * (m_size.cx + m_size.cx / 2);
		pt.y = (ny/2) * m_size.cy;
	}
	else
	{
		pt.x = (m_size.cx*3)/4 + ((nx-1)/2) * (m_size.cx + m_size.cx / 2);
		pt.y = m_size.cy / 2 + ((ny-1)/2) * m_size.cy;
	}


	return pt;
}

int CHexArea::GetType(int x,int y)
{
	if ((x>=0) && (x<32) && (y>=0) && (y<64))
	{
		return m_type[y][x];
	}

	return 0;
}

void CHexArea::SetType(int x,int y,int type)
{
	if ((x>=0) && (x<32) && (y>=0) && (y<64))
	{
		m_type[y][x] = type;
	}
}

int CHexArea::GetPower(int x,int y)
{
	if ((x>=0) && (x<32) && (y>=0) && (y<64))
	{
		return m_power[y][x];
	}

	return 0;
}

void CHexArea::SetPower(int x,int y,int pw)
{
	if ((x>=0) && (x<32) && (y>=0) && (y<64))
	{
		m_power[y][x] = pw;
	}
}

void CHexArea::Occupy(POINT pt,int playerenemy,int pw)
{
	int x = pt.x;
	int y = pt.y;
	int p = GetPower(x,y);
	if (playerenemy == 0)
	{
		p += pw;
		if (p>m_powerMax) p = m_powerMax;
	}
	else if (playerenemy == 1)
	{
		p -= pw;
		if (p<-m_powerMax) p = -m_powerMax;
	}
	SetPower(x,y,p);
}

int CHexArea::GetLandPower(int playerenemy)
{
	int pw = 0;
	for (int j=0;j<64;j++)
	{
		for (int i=0;i<32;i++)
		{
			int p = GetPower(i,j);
			if (((playerenemy == 0) && (p>=10000)) || ((playerenemy == 1) && (p <= -10000)))
			{
				int type = GetType(i,j);
				int t = 1;
				//
				//


				pw += t;
			}
		}
	}
	return pw;
}

void CHexArea::AddRandomHex(int type)
{
	int startX = rand() % 14;
	int startY = rand() % 30;
	startX += 1;
	startY += 1;

	if (((startX+startY) & 1) == 1)
	{
		if (startY>16)
		{
			startY--;
		}
		else
		{
			startY++;
		}
	}


	for (int i=0;i<6;i++)
	{
		int x = startX + m_houkouTable[i*2];
		int y = startX + m_houkouTable[i*2+1];
		if (CheckInArea(x,y))
		{
			m_type[y][x] = type;
		}
	}


	int k = 0;
	int xx = startX;
	int yy = startY;
	for (int i=0;i<100;i++)
	{
		int r = rand() % 6;
		int x = xx + m_houkouTable[r*2];
		int y = yy + m_houkouTable[r*2+1];
		if (CheckInArea(x,y))
		{
			xx = x;
			yy = y;
			m_type[y][x] = type;
			k++;
			if (k>=10) break;
		}
	}

}

BOOL CHexArea::CheckInArea(int x,int y)
{
	if (x<0) return FALSE;
	if (y<0) return FALSE;
	if (x>=32) return FALSE;
	if (y>=64) return FALSE;
	return TRUE;
}

/*_*/



