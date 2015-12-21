#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "..\..\systemNNN\nnnUtilLib\systempicture.h"

#include "cardList.h"
#include "putChara.h"
#include "putCard.h"
#include "enchantControl.h"

CEnchantControl::CEnchantControl(CCardList* list,CPutCard* putCard)
{
	m_cardList = list;
	m_putCard = putCard;

	for (int i=0;i<2;i++)
	{
		m_enchant[i] = new int[256];
	}

	m_enchantPrint[0].x = 500;
	m_enchantPrint[0].y = 580;
	m_enchantPrint[1].x = 500;
	m_enchantPrint[1].y = 380;

	m_enchantNext[0].cx = 0;
	m_enchantNext[0].cy = 70;
	m_enchantNext[1].cx = 0;
	m_enchantNext[1].cy = -70;




	Clear();
}

CEnchantControl::~CEnchantControl()
{
	End();
}

void CEnchantControl::End(void)
{
	for (int i=0;i<2;i++)
	{
		DELETEARRAY(m_enchant[i]);
	}
}


void CEnchantControl::Clear(void)
{
	for (int pl=0;pl<2;pl++)
	{
		m_enchantMax[pl] = 3;
		m_enchantNumber[pl] = 0;
	}
	CalcuEffect();
}

void CEnchantControl::AddEnchant(int pl,int card)
{
	if (m_enchantNumber[pl] < m_enchantMax[pl])
	{
		m_enchant[pl][m_enchantNumber[pl]] = card;
		m_enchantNumber[pl]++;
	}
	else
	{
		for (int i=0;i<m_enchantNumber[pl]-1;i++)
		{
			m_enchant[pl][i] = m_enchant[pl][i+1];
		}
		m_enchant[pl][m_enchantNumber[pl]-1] = card;
	}
	
	CalcuEffect();

}

void CEnchantControl::RemoveEnchant(int pl,int nm)
{
	if (m_enchantNumber[pl] == 0) return;
	if (nm == -1)
	{
		m_enchantNumber[pl] = 0;
		CalcuEffect();
		return;
	}

	if (nm == -2)
	{
		nm = rand() % m_enchantNumber[pl];
	}

	for (int i=nm;i<m_enchantNumber[pl]-1;i++)
	{
		m_enchant[pl][i] = m_enchant[pl][i+1];
	}
	m_enchantNumber[pl]--;
	CalcuEffect();

}

int CEnchantControl::GetOnEnchant(int pl,POINT pt)
{
	for (int i=0;i<m_enchantNumber[pl];i++)
	{
		POINT enchantPoint = GetEnchantPoint(pl,i);
		int dx = pt.x - enchantPoint.x;
		int dy = pt.y - enchantPoint.y;
		if ( (dx > -32) && (dy > -32) && (dx < 32) && (dy < 32) )
		{
			return m_enchant[pl][i];
		}

	}
	return 0;
}

POINT CEnchantControl::GetEnchantPoint(int pl,int n)
{
	POINT pt;
	int x = m_enchantPrint[pl].x;
	int y = m_enchantPrint[pl].y;
	x += m_enchantNext[pl].cx * n;
	y += m_enchantNext[pl].cy * n;

	pt.x = x;
	pt.y = y;

	return pt;
}

void CEnchantControl::Print(void)
{
	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_enchantNumber[pl];i++)
		{
			int card = m_enchant[pl][i];
			POINT pt = GetEnchantPoint(pl,i);
			m_putCard->PutMiniCard(pt,card,70);
		}
	}
}

void CEnchantControl::CalcuEffect(void)
{
	m_attack[0] = 0;
	m_attack[1] = 0;
	m_deffense[0] = 0;
	m_deffense[1] = 0;

	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_enchantNumber[pl];i++)
		{
			int card = m_enchant[pl][i];
			int enchantType = m_cardList->GetEnchantType(card);

			int targetPlayer = pl;
			if (enchantType < 0)
			{
				targetPlayer = 1 - pl;
				enchantType *= -1;
			}

			if (enchantType == 1)
			{
				//attack
				m_attack[targetPlayer] += m_cardList->GetAttack(card);
			}
			else if (enchantType == 2)
			{
				//deffense
				m_deffense[targetPlayer] += m_cardList->GetDeffense(card);
			}
		}
	}
}

int CEnchantControl::GetAttack(int pl)
{
	return m_attack[pl];
}

int CEnchantControl::GetDeffense(int pl)
{
	return m_deffense[pl];
}

int CEnchantControl::GetEnchantNumber(int pl)
{
	return m_enchantNumber[pl];
}

/*_*/



