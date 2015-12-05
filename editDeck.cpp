

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

	m_cardPerPage = 5;

	SetRect(&m_upperArea,0,0,544,544);
	SetRect(&m_lowerArea,0,544,544,300);

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

//	m_page = 0;
//	m_pageMax = 1;

	m_captureCard = -1;

	return -1;
}



int CEditDeck::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();

	if (m_mouseStatus->CheckClick(1))
	{
		return ReturnFadeOut(GAMETITLE_MODE);
	}

	GetOnArea(pt);


	if (m_captureCard != -1)
	{
		if (!(m_mouseStatus->GetTrig(0)))
		{




		}
	}






	return -1;
}


int CEditDeck::Print(void)
{
	CAreaControl::SetNextAllPrint();

	CAllGraphics::FillScreen();

	m_message->PrintMessage(10,10,"エディット画面");

	char mes[256];
	sprintf_s(mes,256,"エリア：%d　オン：%d",m_onAreaType,m_onAreaNumber);
	m_message->PrintMessage(10,30,mes);


	for (int j=0;j<7;j++)
	{
		for (int i=0;i<7;i++)
		{
			int x = i * 70 + 40;
			int y = j * 70 + 150;
			m_putCard->PutMiniCard(x,y,1);
		}
	}


	return -1;
}



void CEditDeck::FinalExitRoutine(void)
{
}


void CEditDeck::GetOnArea(POINT pt)
{
	//areaType
	m_onAreaType = -1;
	if (CheckInArea(pt,&m_upperArea))
	{
		m_onAreaType = 0;
	}
	else if (CheckInArea(pt,&m_lowerArea))
	{
		m_onAreaType = 1;
	}


	m_onAreaNumber = -1;

	if (m_onAreaType == 0)
	{
		//upper
	}
	else if (m_onAreaType == 1)
	{
		//lower
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

/*_*/



