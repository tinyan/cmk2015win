

#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "..\..\systemNNN\nnnLib\commonGeneral.h"
#include "..\..\systemNNN\nnnLib\gameCallBack.h"

#include "..\..\systemNNN\nnnLib\commonSystemParamName.h"
#include "..\..\systemNNN\nnnUtilLib\nnnButtonStatus.h"

#include "..\..\systemNNN\nnnUtilLib\myMouseStatus.h"
#include "..\..\systemNNN\nnnUtilLib\mymessage.h"
#include "..\..\systemNNN\nnnUtilLib\nameList.h"

#include "..\..\systemNNN\nnnUtilLib\superButtonPicture.h"
#include "..\..\systemNNN\nnnUtilLib\commonButton.h"

#include "..\..\systemNNN\nnnUtilLib\nnnButtonStatus.h"
#include "..\..\systemNNN\nnnUtilLib\commonButtonGroup.h"
#include "..\..\systemNNN\nnnUtilLib\commonUpDownButtonGroup.h"
#include "..\..\systemNNN\nnnUtilLib\commonBackButton.h"
#include "..\..\systemNNN\nnnUtilLib\commonUpDownBack.h"


#include "..\..\systemNNN\nnnUtilLib\suuji.h"



#include "mode.h"

//#include "clearStage.h"
//#include "mapData.h"
//#include "demoPlay.h"

//#include "hajike.h"

//#include "printCountDown.h"
//#include "printHaikei.h"
//#include "printPlate.h"
//#include "printScore.h"

//#include "printGameStatus.h"

//#include "resultControl.h"

//#include "highScoreData.h"

//#include "playStageCommon.h"
//#include "playStageType1.h"
//#include "playStageType1B.h"
//#include "playStageType2.h"
//#include "playStageType3.h"


#include "putCard.h"
#include "haveCard.h"
#include "deckData.h"

#include "editDeck.h"
#include "game.h"


CEditDeck::CEditDeck(CGame* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(EDITDECK_MODE);
	LoadSetupFile("editDeck",256);

	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();
	m_putCard = m_game2->GetPutCard();
	m_haveCard = m_game2->GetHaveCard();
	m_deckData = m_game2->GetDeckData();


	m_card = NULL;
	m_cardNumber = NULL;
	m_cardUsed = NULL;

	m_workMax = 0;
	ExpandWork(1024);

	m_baseCardPerPageX = 7;
	m_baseCardPerPageY = 3;
	m_baseCardPerPage = m_baseCardPerPageX * m_baseCardPerPageY;
	
	m_deckCardPrintNumberX = 7;
	m_deckCardPrintNumberY = 7;
	m_deckCardNumber = 45;


	m_deckCardPrint.x = 60;
	m_deckCardPrint.y = 80;
	m_deckCardNext.cx = 70;
	m_deckCardNext.cy = 70;
	m_deckCardSize.cx = 64;
	m_deckCardSize.cy = 64;


	m_baseCardPrint.x = 60;
	m_baseCardPrint.y = 600;
	m_baseCardNext.cx = 70;
	m_baseCardNext.cy = 70;
	m_baseCardSize.cx = 64;
	m_baseCardSize.cy = 64;



	SetRect(&m_deckArea,0,0,544,544);
	SetRect(&m_baseArea,0,544,544,416);

	m_saveButton = new CCommonButton(m_setup,"save");

	CreateUpDownButton();
	CreateBackButton();
	CreateUpDownBack();

	m_saveButton->SetPicture(CSuperButtonPicture::GetPicture(3));

	GetFadeInOutSetup();

}

CEditDeck::~CEditDeck()
{
	End();
}

void CEditDeck::End(void)
{
	DELETEARRAY(m_cardUsed);
	DELETEARRAY(m_cardNumber);
	DELETEARRAY(m_card);
}


int CEditDeck::Init(void)
{
	CreateCardList();
	m_page = 0;

	m_updownBack->SetPage(m_page);
	m_updownBack->SetPageMax(m_pageMax);
	m_updownBack->Init();

	LoadBackButtonPic();
	LoadUpDownButtonPic();
	m_back->Init();
	m_updownBack->Init();

	m_saveButton->LoadFile();
	m_saveButton->Init();

	m_captureCard = -1;

	m_commonParts->LoadDWQ("sys\\ta_editdeck_bg");
	m_bgCount = 0;

	return -1;
}



int CEditDeck::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();

//	if (m_mouseStatus->CheckClick(1))
//	{
//		return ReturnFadeOut(GAMETITLE_MODE);
//	}

	GetOnArea(pt);

	if (m_largeCardPrintCount > 0)
	{
		m_largeCardPrintCount--;

		if (m_captureCard != -1)
		{
			if ((m_onAreaType != m_captureFromArea) || (m_onAreaNumber != m_captureFromPlace))
			{
				m_largeCardPrintCount = 0;
			}
		}
	}

	if (m_captureCard != -1)
	{
		m_updownBack->Calcu(NULL);
		m_saveButton->Calcu(NULL);

		if (!(m_mouseStatus->GetTrig(0)))
		{
			if (m_onAreaType == 0)
			{
				if ((m_onAreaNumber >= 0) && (m_onAreaNumber < m_deckCardNumber))
				{
					int card2 = m_deckData->GetCard(m_onAreaNumber);
					m_deckData->SetCard(m_onAreaNumber,m_captureCard);
					if (card2 > 0)
					{
						if (m_captureFromArea == 0)
						{
							m_deckData->SetCard(m_captureFromPlace,card2);
						}
						else if (m_captureFromArea == 1)
						{
							AddUsed(card2,-1);
						}
					}
					m_captureCard = -1;
					PlaySetCardSound();
				}
				else
				{
					Modosu();
					PlayModosuSound();
				}
			}
			else if (m_onAreaType == 1)
			{
				AddUsed(m_captureCard,-1);
				m_captureCard = -1;
				PlayModosuSound();
			}
			else
			{
				Modosu();
				PlayModosuSound();
			}
		}

		return -1;
	}

	if (m_mouseStatus->CheckClick())
	{
		if (m_onAreaType == 0)
		{
			if (m_onAreaNumber != -1)
			{
				int card = m_deckData->GetCard(m_onAreaNumber);
				if (card > 0)
				{
					m_captureFromArea = m_onAreaType;
					m_captureFromPlace = m_onAreaNumber;
					m_captureCard = card;
					m_deckData->SetCard(m_onAreaNumber,0);
					m_largeCardPrintCount = 300;
					PlayCaptureSound();
				}
			}
		}
		else if (m_onAreaType == 1)
		{
			if (m_onAreaNumber != -1)
			{
				int n = m_onAreaNumber + m_page * m_baseCardPerPage;
				if (n<m_listNumber)
				{
					if (m_card[n] > 0)
					{
						if (m_cardUsed[n] < m_cardNumber[n])
						{
							m_captureCard = m_card[n];
							m_captureFromArea = m_onAreaType;
							m_captureFromPlace = m_onAreaNumber;
							AddUsed(m_captureCard);
							m_largeCardPrintCount = 300;
							PlayCaptureSound();
						}
					}
				}
			}

		}
	}




//	if (m_clickingFlag)
	if (1)
	{
		if (1)
//		if (m_clickButtonNumber < -1)
		{
			int rt = NNNBUTTON_NOTHING;
//			int rt2 = NNNBUTTON_NOTHING;
			rt = m_updownBack->Calcu(m_inputStatus);

			int nm = ProcessUpDownBack(rt);
				

			if (nm == 0)
			{
				return ReturnFadeOut(GAMETITLE_MODE);
			}
			else if (nm > 0)
			{
				ChangePage(nm-1);
			}
		}
	}

	if (1)
	{
		int rt = m_saveButton->Calcu(m_inputStatus);
		int nm = ProcessCommonButton(rt);
		if (nm == 0)
		{
			m_game2->SetSelectDeckBackMode(EDITDECK_MODE);
			return ReturnFadeOut(SAVEDECK_MODE);
		}
	}

	return -1;
}

void CEditDeck::Modosu(void)
{
	if (m_captureFromArea == 0)
	{
		m_deckData->SetCard(m_captureFromPlace,m_captureCard);
		m_captureCard = -1;
	}
	else if (m_captureFromArea == 1)
	{
		AddUsed(m_captureCard,-1);
		m_captureCard = -1;
	}
}

int CEditDeck::Print(void)
{
	CAreaControl::SetNextAllPrint();

	m_bgCount++;
	m_bgCount %= 960;
	m_commonParts->Put(0,m_bgCount-960,FALSE);
	m_commonParts->Put(0,m_bgCount,FALSE);

//	CAllGraphics::FillScreen();

//	m_message->PrintMessage(10,10,"エディット画面");

	//char mes[256];
	//sprintf_s(mes,256,"エリア：%d　オン：%d",m_onAreaType,m_onAreaNumber);
	//m_message->PrintMessage(10,30,mes);


	for (int j=0;j<m_deckCardPrintNumberY;j++)
	{
		for (int i=0;i<m_deckCardPrintNumberX;i++)
		{
			int n = i + j * m_deckCardPrintNumberX;
			if (n<m_deckCardNumber)
			{
				POINT pt = GetDeckPoint(n);
				int card = m_deckData->GetCard(n);
				if (card > 0)
				{
					m_putCard->PutMiniCard(pt.x,pt.y,card);
				}
				else
				{
					m_putCard->PutMiniCard(pt.x,pt.y,-1);
				}
			}
		}
	}


	for (int j=0;j<m_baseCardPerPageY;j++)
	{
		for (int i=0;i<m_baseCardPerPageX;i++)
		{
			int place = i + j * m_baseCardPerPageX ;
			int n = place + m_page * m_baseCardPerPage;

			if (n<m_listNumber)
			{
				POINT pt = GetBasePoint(place);
				int card = m_card[n];
				int cardMax = m_cardNumber[n];
				int cardUsed = m_cardUsed[n];
				int k = cardMax - cardUsed;
				if (k>0)
				{
					m_putCard->PutMiniCard(pt.x,pt.y,card,100,k);
				}
				else
				{
					m_putCard->PutMiniCard(pt.x,pt.y,card,50,k);
				}
			}
		}
	}
	
	if (m_captureCard != -1)
	{
		POINT p = m_mouseStatus->GetZahyo();
		m_putCard->PutMiniCard(p,m_captureCard);

		if (m_largeCardPrintCount > 0)
		{
			int ps = m_largeCardPrintCount;
			if (ps>100) ps = 100;
			m_putCard->PutCard(544/2,480,m_captureCard,ps);
		}
	}


	
	m_updownBack->Print(TRUE);
	m_saveButton->Print(TRUE);

	return -1;
}



void CEditDeck::FinalExitRoutine(void)
{
}


void CEditDeck::GetOnArea(POINT pt)
{
	//areaType
	m_onAreaType = -1;
	if (CheckInArea(pt,&m_deckArea))
	{
		m_onAreaType = 0;
	}
	else if (CheckInArea(pt,&m_baseArea))
	{
		m_onAreaType = 1;
	}


	m_onAreaNumber = -1;

	if (m_onAreaType == 0)
	{
		m_onAreaNumber = GetOnDeck(pt);
		//upper
	}
	else if (m_onAreaType == 1)
	{
		//lower
		m_onAreaNumber = GetOnBase(pt);
	}


}

BOOL CEditDeck::CheckInArea(POINT pt,RECT* lpRect)
{
	int dx = pt.x - lpRect->left;
	int dy = pt.y - lpRect->top;
	if ((dx>=0) && (dy>=0))
	{
		if ((dx<lpRect->right) && (dy < lpRect->bottom))
		{
			return TRUE;
		}
	}

	return FALSE;
}


void CEditDeck::CreateCardList(void)
{
	int n = m_haveCard->CalcuCardList();
	ExpandWork(n);

	//filter
	m_listNumber = 0;
	for (int i=0;i<n;i++)
	{
		m_card[m_listNumber] = m_haveCard->GetCardListCard(i);
		m_cardNumber[m_listNumber] = m_haveCard->GetCardListNumber(i);
		m_cardUsed[m_listNumber] = 0;
		m_listNumber++;
	}


	//check deck
	int k = m_deckData->GetListNumber();
	for (int i=0;i<k;i++)
	{
		int card = m_deckData->GetCard(i);
		if (card > 0)
		{
			AddUsed(card);
		}
	}


	//page
	m_pageMax = (m_listNumber + m_baseCardPerPage - 1) / m_baseCardPerPage;
	if (m_pageMax <= 0) m_pageMax = 1;



}

void CEditDeck::AddUsed(int card,int add)
{
	int found = -1;
	for (int i=0;i<m_listNumber;i++)
	{
		int check = m_card[i];
		if (check == card)
		{
			found = i;
			break;
		}
	}

	if (found != -1)
	{
		m_cardUsed[found] += add;
	}
}


void CEditDeck::ExpandWork(int n)
{
	if (n<=m_workMax) return;

	DELETEARRAY(m_cardUsed);
	DELETEARRAY(m_cardNumber);
	DELETEARRAY(m_card);

	m_workMax = n;

	m_card = new int[n];
	m_cardNumber = new int[n];
	m_cardUsed = new int[n];
}

void CEditDeck::ChangePage(int page)
{
	m_page = page;
	m_updown->SetPage(m_page);
	m_updown->Init();
}


POINT CEditDeck::GetDeckPoint(int n)
{
	int nx = n % m_deckCardPrintNumberX;
	int ny = n / m_deckCardPrintNumberX;
	int x = m_deckCardPrint.x + m_deckCardNext.cx * nx;
	int y = m_deckCardPrint.y + m_deckCardNext.cy * ny;
	POINT pt;
	pt.x = x;
	pt.y = y;
	return pt;

}

POINT CEditDeck::GetBasePoint(int place)
{
	int nx = place % m_baseCardPerPageX;
	int ny = place / m_baseCardPerPageX;
	int x = m_baseCardPrint.x + m_baseCardNext.cx * nx;
	int y = m_baseCardPrint.y + m_baseCardNext.cy * ny;
	POINT pt;
	pt.x = x;
	pt.y = y;
	return pt;
}

int CEditDeck::GetOnDeck(POINT pt)
{
	int dx = pt.x - (m_deckCardPrint.x - m_deckCardSize.cx / 2);
	int dy = pt.y - (m_deckCardPrint.y - m_deckCardSize.cy / 2);
	if ((dx<0) || (dy<0)) return -1;

	int ax = dx % m_deckCardNext.cx;
	int ay = dy % m_deckCardNext.cy;
	if ((ax>=m_deckCardSize.cx) || (ay>=m_deckCardSize.cy)) return -1;
	
	int nx = dx / m_deckCardNext.cx;
	int ny = dy / m_deckCardNext.cy;

	if (nx >= m_deckCardPrintNumberX) return -1;
	if (ny >= m_deckCardPrintNumberY) return -1;

	int n = nx + ny * m_deckCardPrintNumberX;

	return n;
}


int CEditDeck::GetOnBase(POINT pt)
{
	int dx = pt.x - (m_baseCardPrint.x - m_baseCardSize.cx / 2);
	int dy = pt.y - (m_baseCardPrint.y - m_baseCardSize.cy / 2);
	if ((dx<0) || (dy<0)) return -1;

	int ax = dx % m_baseCardNext.cx;
	int ay = dy % m_baseCardNext.cy;
	if ((ax>=m_baseCardSize.cx) || (ay>=m_baseCardSize.cy)) return -1;
	
	int nx = dx / m_baseCardNext.cx;
	int ny = dy / m_baseCardNext.cy;

	if (nx >= m_baseCardPerPageX) return -1;
	if (ny >= m_baseCardPerPageY) return -1;

	int n = nx + ny * m_baseCardPerPageX;

	return n;
}

void CEditDeck::PlaySetCardSound(void)
{
	m_game->PlaySystemSound(5-1);
}

void CEditDeck::PlayModosuSound(void)
{
	m_game->PlaySystemSound(2-1);
}

void CEditDeck::PlayCaptureSound(void)
{
	m_game->PlaySystemSound(1-1);
}

/*_*/



