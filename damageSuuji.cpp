#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "..\..\systemNNN\nnnUtilLib\suuji.h"
#include "..\..\systemNNN\nnnUtilLib\systempicture.h"

#include "damageSuuji.h"


CDamageSuuji::CDamageSuuji()
{
	CPicture* lpPic = CSystemPicture::GetSystemPicture("ta_damageSuuji");
	m_suuji = new CSuuji(lpPic,16,16,3);
	m_dataMax = 100;
	m_work = new SUUJIWORK[m_dataMax];
	AllClear();
}

CDamageSuuji::~CDamageSuuji()
{
	End();
}

void CDamageSuuji::End(void)
{
	DELETEARRAY(m_work);
	ENDDELETECLASS(m_suuji);

}


void CDamageSuuji::AllClear(void)
{
	m_lastSet = 0;
	m_dataNumber = 0;
	for (int i=0;i<m_dataMax;i++)
	{
		m_work[i].flag = FALSE;
	}
}

void CDamageSuuji::AddSuuji(int x,int y,int d,int col)
{
	int n = SearchAki();
	if (n == -1)
	{
		m_lastSet++;
		m_lastSet %= m_dataMax;
		n = m_lastSet;
	}

	m_work[n].flag = TRUE;
	m_work[n].count = 0;
	m_work[n].countMax = 30;
	m_work[n].x = x;
	m_work[n].y = y;
	m_work[n].data = d;
	m_work[n].color = col;

	m_lastSet = n;
	if (n >= m_dataNumber) m_dataNumber = n+1;
}

void CDamageSuuji::Calcu(int cnt)
{
	for (int i=0;i<m_dataNumber;i++)
	{
		if (m_work[i].flag)
		{
			m_work[i].count++;
			if (m_work[i].count >= m_work[i].countMax)
			{
				m_work[i].flag = FALSE;
			}
		}
	}




	//
	if (m_dataNumber > 0)
	{
		if (!m_work[m_dataNumber-1].flag)
		{
			m_dataNumber--;
		}
	}
}

void CDamageSuuji::Print(void)
{
	for (int i=0;i<m_dataNumber;i++)
	{
		if (m_work[i].flag)
		{
			int putX = m_work[i].x;
			int putY = m_work[i].y;
			int c = m_work[i].count;
			int color = m_work[i].color;
			putY -= c;
			putX -= 16*2;
			m_suuji->Print(putX,putY,m_work[i].data,-1,color);

		}
	}
}

int CDamageSuuji::SearchAki(void)
{
	for (int i=0;i<m_dataMax;i++)
	{
		if (!m_work[i].flag) return i;
	}

	return -1;
}


/*_*/



