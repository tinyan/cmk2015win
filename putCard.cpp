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

//	m_card[0] = new CPutChara("sys\\cardseat0",4,4);

	m_miniCard = new CPutChara("sys\\ta_minicardseat",16,16);

	m_cardPic = new CPicture();
	m_cardPicNumber = -1;

	CPicture* suujiPic = CSystemPicture::GetSystemPicture("ta_minicard_number");
	m_minicardSuuji = new CSuuji(suujiPic,16,16,3);

	m_cardBase[0] = new CPicture("sys\\ta_whiteCard");
	m_cardBase[1] = new CPicture("sys\\ta_greenCard");
	m_cardBase[2] = new CPicture("sys\\ta_redCard");
	m_cardBase[3] = new CPicture("sys\\ta_goldCard");

	m_rare = new CPutChara("sys\\ta_rare",8,1);
	m_rarePrintX = 226;
	m_rarePrintY = 244;

	m_namePrintX = 20;
	m_namePrintY = 14;

	m_textPrintX = 28;
	m_textPrintY = 260;
	m_textNextY = 17;

	m_plainTextPrintX = 28;
	m_plainTextPrintY = 320;
	m_plainTextNextY = 13;

	m_type = new CPutChara("sys\\ta_type",1,8);
	m_typePrintX = 84;
	m_typePrintY = 244;

	m_cardMana = new CPutChara("sys\\ta_cardMana",10,10);
	m_cardManaPrintX = 228;
	m_cardmanaPrintY = 26;
	m_cardManaNextX = -16;

	m_etcPrintX = 220;
	m_etcPrintY = 354;
	m_etcNextX = 16;

	m_etcSuuji = new CSuuji(CSystemPicture::GetSystemPicture("ta_etcsuuji"),16,16,3);

	m_flag = new CPutChara("sys\\ta_flag",1,1);
	m_flagPrintX = 20;
	m_flagPrintY = 362;
	m_flagNextX = 16;
}

CPutCard::~CPutCard()
{
	End();
}

void CPutCard::End(void)
{
	ENDDELETECLASS(m_flag);
	ENDDELETECLASS(m_etcSuuji);
	ENDDELETECLASS(m_cardMana);
	ENDDELETECLASS(m_type);
	ENDDELETECLASS(m_rare);

	for (int i=0;i<4;i++)
	{
		ENDDELETECLASS(m_cardBase[i]);
	}
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

//	SIZE size = m_cardPic->GetPicSize();
//	int sizeX = size.cx;
//	int sizeY = size.cy;
	int sizeX = 256;
	int sizeY = 384;

	int putX = x - sizeX / 2;
	int putY = y - sizeY / 2;


	int baseType = 0;
	int needMana[16];
	for (int i=0;i<16;i++)
	{
		needMana[i] = m_cardList->GetNeedMana(card,i);
	}
	int whiteMana = needMana[0];
	int greenMana = needMana[1];
	int redMana = needMana[2];

	if ((greenMana > 0) && (redMana > 0))
	{
		baseType = 3;
	}
	else
	{
		if (greenMana > 0) baseType = 1;
		if (redMana > 0) baseType = 2;
	}


	int rare = m_cardList->GetRare(card);
	int type = m_cardList->GetType(card);

	m_cardBase[baseType]->TransLucentBlt2(putX,putY,0,0,sizeX,sizeY,ps);
	m_cardPic->TransLucentBlt2(putX+20,putY+40,0,0,240,192,ps);



	m_rare->TransPut(putX+m_rarePrintX,putY+m_rarePrintY,rare,ps);

	m_type->TransPut(putX+m_typePrintX,putY+m_typePrintY,type,ps);


	//mana
	if (1)
	{
		int dx = 0;

		for (int n=2;n>=0;n--)
		{
			int need = m_cardList->GetNeedMana(card,n);
			int srcY = n;
			int srcX = 0;
			int loop = need;
			if (n == 0)
			{
				loop = 1;
				srcX = need - 1;
				if (need == 0) loop = 0;
			}

			for (int i=0;i<loop;i++)
			{
				int x = putX + m_cardManaPrintX + dx;
				int y = putY + m_cardmanaPrintY;

				m_cardMana->TransPut(x,y,srcX,srcY,ps);

				dx += m_cardManaNextX;
			}
		}
	}



	//name
	if (ps>50)
	{
		LPSTR mes = m_cardList->GetName(card);
		m_message->PrintMessage(putX+m_namePrintX,putY+m_namePrintY,mes,20,255,255,255,0,-1,0);


		for (int i=0;i<4;i++)
		{
			LPSTR mes = m_cardList->GetText(card,i);
			if ((*mes) != '@')
			{
				m_message->PrintMessage(putX+m_textPrintX,putY+m_textPrintY + m_textNextY * i,mes,16,0,0,0);
			}
		}

		for (int i=0;i<2;i++)
		{
			LPSTR mes = m_cardList->GetPlainText(card,i);
			if ((*mes) != '@')
			{
				m_message->PrintMessage(putX+m_plainTextPrintX,putY+m_plainTextPrintY + m_plainTextNextY * i,mes,12,0,0,0);
			}
		}

	}


	//etc
	if (ps > 50)
	{
		LPSTR etcMes = m_cardList->GetEtcMes(card);
		if (etcMes != NULL)
		{
			int ln = strlen(etcMes);
			for (int i=0;i<ln;i++)
			{
				char c = etcMes[i];
				int d = (int)c;
				d -= '0';
				if (c == '/') d = 11;
				if (c == '%') d = 12;
				int x = putX + m_etcPrintX - (ln-1-i) * m_etcNextX;
				int y = putY + m_etcPrintY;
				m_etcSuuji->Put(x,y,d);

			}

		}
	}

	//flag
	int numbers = m_cardList->GetNumbers(card);
	if (numbers > 1)
	{
		BOOL bad = FALSE;

		if (type == 7)
		{
			int subType = m_cardList->GetWorldType(card);
			if (subType == 5)
			{
				bad = TRUE;
			}
		}

		if (!bad)
		{
			for (int i=0;i<numbers;i++)
			{
				m_flag->TransPut(putX+m_flagPrintX+m_flagNextX*i,putY+m_flagPrintY,0,0,ps);
			}
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



