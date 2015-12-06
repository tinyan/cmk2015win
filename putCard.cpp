#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "..\..\systemNNN\nnnUtilLib\suuji.h"
#include "..\..\systemNNN\nnnUtilLib\systempicture.h"

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

	m_cardPic = new CPicture();
	m_cardPicNumber = -1;

	CPicture* suujiPic = CSystemPicture::GetSystemPicture("ta_minicard_number");
	m_minicardSuuji = new CSuuji(suujiPic,16,16,3);


}

CPutCard::~CPutCard()
{
	End();
}

void CPutCard::End(void)
{
	ENDDELETECLASS(m_minicardSuuji);
	ENDDELETECLASS(m_cardPic);
	ENDDELETECLASS(m_miniCard);
	for (int i=0;i<m_seatMax;i++)
	{
		ENDDELETECLASS(m_card[i]);
	}
}

void CPutCard::PutCard(int x,int y,int card,int ps)
{
	if (m_cardPicNumber != card)
	{
		LPSTR filenameonly = m_cardList->GetFilename(card);
		char filename[256];
		sprintf_s(filename,256,"sys\\%s",filenameonly);
		m_cardPic->LoadDWQ(filename);

		m_cardPicNumber = card;
	}

	SIZE size = m_cardPic->GetPicSize();
	int sizeX = size.cx;
	int sizeY = size.cy;

	int putX = x - sizeX / 2;
	int putY = y - sizeY / 2;

	if (ps >= 100)
	{
		m_cardPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
	}
	else
	{
		m_cardPic->TransLucentBlt2(putX,putY,0,0,sizeX,sizeY,ps);
	}

}

void CPutCard::PutMiniCard(POINT pt,int card,int ps,int number)
{
	PutMiniCard(pt.x,pt.y,card,ps,number);
}

void CPutCard::PutMiniCard(int x,int y,int card,int ps,int number)
{
	int miniCard;
	if (card <= 0)
	{
		miniCard = -card;
	}
	else
	{
		miniCard = m_cardList->GetMiniCardNumber(card);
	}

	if (ps >= 100)
	{
		m_miniCard->Put(x,y,miniCard);
	}
	else
	{
		m_miniCard->TransPut(x,y,miniCard,ps);
	}
	
	if (number >= 0)
	{
		m_minicardSuuji->Print(x-16,y+16,number);
	}
}


/*_*/



