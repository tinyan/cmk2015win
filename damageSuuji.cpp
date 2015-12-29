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
	m_suuji = new CSuuji(lpPic,32,32,3,24);
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

void CDamageSuuji::AddSuuji(int x,int y,int d,int col,BOOL magic)
{
	int n = SearchAki();
	if (n == -1)
	{
		m_lastSet++;
		m_lastSet %= m_dataMax;
		n = m_lastSet;
	}

	int countMax = 2000;
	int countSpeed = 100;

	if (d >= 10)
	{
		countMax = 2500;
		countSpeed = 100 + (d-10)*5;
	}
	else if (d >= 20)
	{
		int dd = d;
		if (dd>30) dd = 30;

		countMax = 3000;
		countSpeed = 150 + (dd-20)*5;
		if (countSpeed > 200) countSpeed = 200;

	}

	if (col == 2)
	{
		countMax = 3000;
		countSpeed = 50;
	}

	if (magic)
	{
		countMax = 3000;
		countSpeed = 50;
	}

	m_work[n].flag = TRUE;
	m_work[n].count = 0;
	m_work[n].countMax = countMax;
	m_work[n].x = x;
	m_work[n].y = y;
	m_work[n].data = d;
	m_work[n].color = col;
	m_work[n].countSpeed = countSpeed;

	m_lastSet = n;
	if (n >= m_dataNumber) m_dataNumber = n+1;
}

void CDamageSuuji::Calcu(int cnt)
{
	for (int i=0;i<m_dataNumber;i++)
	{
		if (m_work[i].flag)
		{
			m_work[i].count += m_work[i].countSpeed;
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
			putY -= c / 100;
			putX -= 32*2;
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



