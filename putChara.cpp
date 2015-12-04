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

void CPutChara::Put(int x,int y,int n)
{
	int nx = n % m_blockX;
	int ny = n / m_blockX;
	Put(x,y,nx,ny);
}

void CPutChara::Put(int x,int y,int nx,int ny)
{
	if ((nx>=0) && (ny>=0) && (nx < m_blockX) && (ny<m_blockY))
	{
		int srcY = m_sizeX * nx;
		int srcX = m_sizeY * ny;
		m_pic->Blt(x-m_sizeX/2,y-m_sizeY/2,srcX,srcY,m_sizeX,m_sizeY,TRUE);
	}
}

void CPutChara::TransPut(int x,int y,int n,int ps)
{
	int nx = n % m_blockX;
	int ny = n / m_blockX;
	TransPut(x,y,nx,ny,ps);
}

void CPutChara::TransPut(int x,int y,int nx,int ny,int ps)
{
	if ((nx>=0) && (ny>=0) && (nx < m_blockX) && (ny<m_blockY))
	{
		int srcY = m_sizeX * nx;
		int srcX = m_sizeY * ny;
		m_pic->TransLucentBlt2(x-m_sizeX/2,y-m_sizeY/2,srcX,srcY,m_sizeX,m_sizeY,ps);
	}
}


/*_*/



