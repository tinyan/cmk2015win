#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "mana.h"


CMana::CMana()
{
	Clear();
	m_point.x = 0;
	m_point.y = 0;
}

CMana::~CMana()
{
	End();
}

void CMana::End(void)
{
}

void CMana::Clear(void)
{
	for (int i=0;i<16;i++)
	{
		m_mana[i] = 0;
		m_manaMax[i] = 0;
	}
	m_manaPower = 0;
}

void CMana::SetManaMax(int n,int mx)
{
	m_manaMax[n] = mx;
}

void CMana::SetMana(int n,int mana)
{
	if (mana>m_manaMax[n]) mana = m_manaMax[n];
	m_mana[n] = mana;
}

int CMana::GetMana(int n)
{
	return m_mana[n];
}

void CMana::AddLandPower(int n,int pw)
{
	int d = m_manaMax[n];
	d += pw;
	SetManaMax(n,d);
}

void CMana::AddMana(int n,int mana)
{
	int d = GetMana(n);
	d += mana;
	SetMana(n,d);
}

void CMana::AllHeal(int d)
{
	for (int i=0;i<16;i++)
	{
		if (d == -1)
		{
			m_mana[i] = m_manaMax[i];
		}
		else
		{
			AddMana(i,d);
		}
	}
}

BOOL CMana::UseMana(int n,int mana)
{
	if (mana > m_mana[n]) return FALSE;

	m_mana[n] -= mana;
	return TRUE;
}

void CMana::SetPoint(POINT pt)
{
	m_point = pt;
}

void CMana::AddManaPower(int pw)
{
	m_manaPower += pw;
	if (m_manaPower >= 10000)
	{
		m_manaPower -= 10000;
		AddAllMana();
	}
}

void CMana::AddAllMana(int add)
{
	for (int i=0;i<16;i++)
	{
		int mana = m_mana[i];
		mana += add;
		if (mana > m_manaMax[i]) mana = m_manaMax[i];
		m_mana[i] = mana;
	}
}

void CMana::Print(void)
{
	int rgb[3][3] = 
	{
		{255,255,255},
		{0,255,0},
		{255,0,0},
	};

	for (int n=0;n<=2;n++)
	{
		int mx = m_manaMax[n];
		int mana = m_mana[n];

		int r = rgb[n][0];
		int g = rgb[n][1];
		int b = rgb[n][2];

		for (int i=0;i<mx;i++)
		{
			int x = m_point.x + 12 * i;
			int y = m_point.y + 12 * n;
			if (i<mana)
			{
				CAllGeo::BoxFill(x,y,10,10,r,g,b);
			}
			else
			{
				CAllGeo::BoxFill(x+2,y+2,6,6,r,g,b);
			}
		}
	}
}


/*_*/



