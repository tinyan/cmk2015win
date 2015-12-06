#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"


#include "putChara.h"


CPutChara::CPutChara(LPSTR filename,int x,int y)
{
	m_pic = new CPicture(filename);
	m_picSize  = m_pic->GetPicSize();
	m_blockX = x;
	m_blockY = y;
	m_sizeX = m_picSize.cx / m_blockX;
	m_sizeY = m_picSize.cy / m_blockY;
}

CPutChara::~CPutChara()
{
	End();
}

void CPutChara::End(void)
{
	ENDDELETECLASS(m_pic);
}

void CPutChara::Put(POINT pt,int n)
{
	Put(pt.x,pt.y,n);
}

void CPutChara::Put(int x,int y,int n)
{
	int nx = n % m_blockX;
	int ny = n / m_blockX;
	Put(x,y,nx,ny);
}

void CPutChara::Put(POINT pt,int nx,int ny)
{
	Put(pt.x,pt.y,nx,ny);
}

void CPutChara::Put(int x,int y,int nx,int ny)
{
	TransPut(x,y,nx,ny,100);
}

void CPutChara::TransPut(POINT pt,int n,int ps)
{
	TransPut(pt.x,pt.y,n,ps);
}

void CPutChara::TransPut(int x,int y,int n,int ps)
{
	int nx = n % m_blockX;
	int ny = n / m_blockX;
	TransPut(x,y,nx,ny,ps);
}

void CPutChara::TransPut(POINT pt,int nx,int ny,int ps)
{
	TransPut(pt.x,pt.y,nx,ny,ps);
}

void CPutChara::TransPut(int x,int y,int nx,int ny,int ps)
{
	if ((nx>=0) && (ny>=0) && (nx < m_blockX) && (ny<m_blockY))
	{
		int srcX = m_sizeX * nx;
		int srcY = m_sizeY * ny;
		int putX = x - m_sizeX / 2;
		int putY = y - m_sizeY / 2;

		if (ps == 100)
		{
			m_pic->Blt(putX,putY,srcX,srcY,m_sizeX,m_sizeY,TRUE);
		}
		else
		{
			m_pic->TransLucentBlt2(putX,putY,srcX,srcY,m_sizeX,m_sizeY,ps);
		}
	}
}


/*_*/



