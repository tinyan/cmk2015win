#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "cardList.h"
#include "putChara.h"

#include "putCard.h"


CPutCard::CPutCard(CCardList* cardList)
{
	m_cardList = cardList;
	m_seatMax = 16;
	for (int i=0;i<m_seatMax;i++)
	{
		m_card[i] = NULL;
	}

	m_card[0] = new CPutChara("sys\\cardseat0",4,4);

	m_miniCard = new CPutChara("sys\\ta_minicardseat",16,16);

}

CPutCard::~CPutCard()
{
	End();
}

void CPutCard::End(void)
{
	ENDDELETECLASS(m_miniCard);
	for (int i=0;i<m_seatMax;i++)
	{
		ENDDELETECLASS(m_card[i]);
	}
}

void CPutCard::PutCard(int x,int y,int card,int ps)
{
}

void CPutCard::PutMiniCard(int x,int y,int card,int ps)
{
	if (ps >= 100)
	{
		m_miniCard->Put(x,y,card);
	}
	else
	{
		m_miniCard->TransPut(x,y,card,ps);
	}
}


/*_*/



