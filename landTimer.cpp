#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "landTimer.h"



CLandTimer::CLandTimer()
{
	m_onPic = new CPicture("sys\\ta_landtimer_on");
	m_offPic = new CPicture("sys\\ta_landtimer_off");
	m_size = m_onPic->GetPicSize();

	m_timerMax = 100;
	m_timer = 0;
	m_point.x = 0;
	m_point.y = 0;
	m_anime = 0;
}

CLandTimer::~CLandTimer()
{
	End();
}

void CLandTimer::End(void)
{
	ENDDELETECLASS(m_offPic);
	ENDDELETECLASS(m_onPic);

}


void CLandTimer::SetTimerMax(int mx)
{
	m_timerMax = mx;
}

void CLandTimer::AddTimer(int add)
{
	m_timer += add;
	if (m_timer > m_timerMax) m_timer = m_timerMax;
}

void CLandTimer::SetTimer(int tm)
{
	m_timer = tm;
}

void CLandTimer::SetPoint(POINT pt)
{
	m_point = pt;
}

void CLandTimer::Print(int tm)
{
	Print(m_point,tm);
}

void CLandTimer::Print(POINT pt,int tm)
{
	if (tm == -1) tm = m_timer;


	if (tm >= m_timerMax)
	{
		//anime?
		m_anime++;
		m_anime %= 20;
		int add = m_anime;
		if (add >= 10) add = 20-add;

		int ps = add * 10;
		int r = add*4;
		int g = add*4;
		int b = add*4;

		m_onPic->ColorAddBlt(pt.x,pt.y,0,0,m_size.cx,m_size.cy,TRUE,r,g,b);

		return;
	}


	int onGaze = (m_size.cx * tm) / m_timerMax;
	int offGaze = m_size.cx - onGaze;

	int putX = pt.x;
	int putY = pt.y;
	int sizeX = onGaze;
	int sizeY = m_size.cy;
	int srcX = 0;
	int srcY = 0;

	m_onPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);

	srcX += sizeX;
	putX += sizeX;
	sizeX = offGaze;
	m_offPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
}


/*_*/



