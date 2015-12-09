#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "..\..\systemNNN\nnnUtilLib\suuji.h"
#include "..\..\systemNNN\nnnUtilLib\systempicture.h"
#include "..\..\systemNNN\nnnUtilLib\mymessage.h"

#include "cardList.h"
#include "putChara.h"

#include "putCard.h"


CPutCard::CPutCard(CMyMessage* message,CCardList* cardList)
{
	m_cardList = cardList;
	m_message = message;

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


	//name
	if (1)
	{
		LPSTR mes = m_cardList->GetName(card);
		m_message->PrintMessage(putX+4,putY+4,mes,20,255,255,255,0,-1,0);
	}

	//mana
	if (1)
	{
		int rgb[3][3] = 
		{
			{255,255,255},
			{0,255,0},
			{255,0,0},
		};

		int total = 0;

		for (int n=2;n>=0;n--)
		{
			int need = m_cardList->GetNeedMana(card,n);

			int r = rgb[n][0];
			int g = rgb[n][1];
			int b = rgb[n][2];

			for (int i=0;i<need;i++)
			{
				int x = putX + sizeX - (total+1) * 12;
				int y = putY +8;
				CAllGeo::BoxFill(x,y,10,10,r,g,b);

				total++;
			}
		}
	}

	//rare


	for (int i=0;i<4;i++)
	{
		LPSTR mes = m_cardList->GetText(card,i);
		if ((*mes) != 0)
		{
			m_message->PrintMessage(putX,putY+sizeY-(4-i) * 24,mes);
		}
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



