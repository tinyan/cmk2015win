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

#include "cardList.h"

#include "putChara.h"

#include "haveCard.h"
#include "putCard.h"

#include "gacha.h"
#include "game.h"



CGacha::CGacha(CGame* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(GACHA_MODE);
	LoadSetupFile("gacha",256);

	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();
	m_haveCard = m_game2->GetHaveCard();
	m_putCard = m_game2->GetPutCard();
	m_cardList = m_game2->GetCardList();

	m_limit1 = 30;
	m_limit2 = 90;

	m_star = new CPutChara("sys\\ta_star",1,1);
	m_getPic = new CPicture("sys\\ta_gacha_get");
}


CGacha::~CGacha()
{
	End();
}

void CGacha::End(void)
{
	ENDDELETECLASS(m_getPic);
	ENDDELETECLASS(m_star);
}

int CGacha::Init(void)
{
	m_getCard = m_game2->GetGachaCard();
	int n = m_haveCard->GetCard(m_getCard);
	n += 1;
	m_haveCard->SetCard(m_getCard,n);
	m_haveCard->Save();

	m_rareRank = m_cardList->GetRare(m_getCard);
	m_starNumber = m_rareRank + 1;

	m_commonParts->LoadDWQ("sys\\ta_gacha_back");
	m_count = 0;
	return -1;
}



int CGacha::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();
	if (m_mouseStatus->CheckClick(1))
	{
//		return ReturnFadeOut(GAMETITLE_MODE);
	}

	if (m_count >= m_limit2)
	{
		if (m_mouseStatus->CheckClick())
		{
			return ReturnFadeOut(GAMETITLE_MODE);
		}
	}

	m_count++;



	return -1;
}


int CGacha::Print(void)
{
	CAreaControl::SetNextAllPrint();


	int limit1 = m_limit1;
	int limit2 = m_limit2;

	if (m_count < limit1)
	{
		int light = 0 + ( m_count  * 255) / limit1;
		int r = light;
		int g = light;
		int b = light;

		CAllGraphics::FillScreen(r,g,b);
	}
	else if (m_count < limit2)
	{
		int light = ( (limit2 - m_count)*255 ) / (limit2 - limit1);
		m_commonParts->ColorAddBlt(0,0,0,0,540,960,TRUE,light,light,light);
	}
	else
	{
		m_commonParts->Put(0,0,FALSE);
		m_getPic->Put(0,40,TRUE);
	}


	if (m_count >= limit2)
	{
		m_putCard->PutCard(270,480,m_getCard);
	}
	else if (m_count >= limit1)
	{
		int dy = -((limit2 - m_count) * 270) / (limit2 - limit1);
		int ps = 10 + ( (m_count - limit1)*90 ) / (limit2 - limit1);
		m_putCard->PutCard(270,480+dy,m_getCard,ps);
	}

	if (m_count >= limit1)
	{
		int nextX = 80;
		int startX = 270 - (nextX * (m_starNumber-1)) / 2;
		int putY = 768;
		int pic = 0;

		for (int i=0;i<m_starNumber;i++)
		{
			m_star->Put(startX + i * nextX,putY,pic);
		}
	}


	return -1;
}



void CGacha::FinalExitRoutine(void)
{
}


/*_*/



