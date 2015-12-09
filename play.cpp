

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
#include "..\..\systemNNN\nnnUtilLib\commonButtonGroup.h"

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
#include "putPeople.h"
#include "landTimer.h"
#include "deckData.h"
#include "cardList.h"
#include "mana.h"

#include "play.h"
#include "game.h"


#define GAMEPLAY_MODE 0
#define GAMEOVER_MODE 1
#define STAGECLEAR_MODE 2
#define RETRY_OR_EXIT_MODE 3
#define NEXT_OR_EXIT_MODE 4

#define USECARD_MODE 5


CPlay::CPlay(CGame* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(PLAY_MODE);
	LoadSetupFile("play",256);

	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();

	m_deckData = m_game2->GetDeckData();
	m_putCard = m_game2->GetPutCard();
	m_cardList = m_game2->GetCardList();


	m_useButton = new CCommonButton(m_setup,"use");
	m_dropButton = new CCommonButton(m_setup,"drop");
	m_cancelButton = new CCommonButton(m_setup,"cancel");

	m_useButton->SetPicture(CSuperButtonPicture::GetPicture(3));
	m_dropButton->SetPicture(CSuperButtonPicture::GetPicture(4));
	m_cancelButton->SetPicture(CSuperButtonPicture::GetPicture(5));

	m_mana[0] = new CMana();
	m_mana[1] = new CMana();
	POINT pt;
	pt.x = 0;
	pt.y = 600;
	m_mana[0]->SetPoint(pt);
	pt.x = 0;
	pt.y = 200;
	m_mana[1]->SetPoint(pt);

	m_placeMax = 7;
	m_hand[0] = new int[m_placeMax];
	m_hand[1] = new int[m_placeMax];

	m_manaTypeMax = 2;

	m_miniCardPoint[0].x = 70;
	m_miniCardPoint[0].y = 800;
	m_miniCardPoint[1].x = 70;
	m_miniCardPoint[1].y = 100;
	m_miniCardNext.cx = 70;
	m_miniCardNext.cy = 70;
	m_miniCardSize.cx = 64;
	m_miniCardSize.cy = 64;


	m_putPeople = m_game2->GetPutPeople();
	m_landTimer[0] = new CLandTimer();
	m_landTimer[1] = new CLandTimer();
//	POINT pt;
	pt.x = 20;
	pt.y = 800;
	m_landTimer[0]->SetPoint(pt);
	m_landTimer[0]->SetTimerMax(100);
	pt.x = 20;
	pt.y = 100;
	m_landTimer[1]->SetPoint(pt);
	m_landTimer[1]->SetTimerMax(100);
}


CPlay::~CPlay()
{
	End();
}

void CPlay::End(void)
{
	for (int i=0;i<2;i++)
	{
		ENDDELETECLASS(m_landTimer[i]);
	}
	DELETEARRAY(m_hand[1]);
	DELETEARRAY(m_hand[0]);

	ENDDELETECLASS(m_mana[1]);
	ENDDELETECLASS(m_mana[0]);

	ENDDELETECLASS(m_cancelButton);
	ENDDELETECLASS(m_dropButton);
	ENDDELETECLASS(m_useButton);
}


int CPlay::Init(void)
{

	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_placeMax;i++)
		{
			m_hand[pl][i] = m_deckData->GetCard(i);
		}
	}

	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<=m_manaTypeMax;i++)
		{
			m_mana[pl]->SetManaMax(i,5+i);
			m_mana[pl]->SetMana(i,1+i);
		}
	}


	m_useButton->LoadFile();
	m_dropButton->LoadFile();
	m_cancelButton->LoadFile();

	ClearButton();

	m_playMode = PLAY_MODE;

	return -1;
}



int CPlay::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();

	//debug
	if (m_mouseStatus->CheckClick(1))
	{
		return ReturnFadeOut(GAMETITLE_MODE);
	}


	if (m_playMode == PLAY_MODE)
	{
		return CalcuPlayMode();
	}
	if (m_playMode == USECARD_MODE)
	{
		return CalcuUseCard();
	}





	return -1;
}

int CPlay::CalcuPlayMode(void)
{

	POINT pt = m_mouseStatus->GetZahyo();

	if (m_mouseStatus->CheckClick(0))
	{
		int place = GetOnPlace(pt);
		if (place != -1)
		{
			int card = m_hand[0][place];
			if (card > 0)
			{
				m_selectedCard = card;
				m_selectedPlace = place;
				ClearButton();

				if (CheckMana(0,card))
				{
					m_useButton->SetEnable();
				}
				else
				{
					m_useButton->SetEnable(FALSE);
				}
				m_playMode = USECARD_MODE;
				return -1;
			}
		}
	}




	for (int i=0;i<2;i++)
	{
		m_landTimer[i]->AddTimer();
	}

	return -1;
}

int CPlay::CalcuUseCard(void)
{
	int rt1 = m_useButton->Calcu(m_inputStatus);
	int rt2 = m_dropButton->Calcu(m_inputStatus);
	int rt3 = m_cancelButton->Calcu(m_inputStatus);

	if (rt1 != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt1);
		if (nm == 0)
		{
			UseCardRoutine();
			ClearButton();
			m_playMode = PLAY_MODE;
			return -1;
		}
	}

	if (rt2 != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt2);
		if (nm == 0)
		{
			DropCardRoutine();
			ClearButton();
			m_playMode = PLAY_MODE;
			return -1;
		}
	}

	if (rt3 != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt3);
		if (nm == 0)
		{
			m_playMode = PLAY_MODE;
			return -1;
		}
	}

	return -1;
}

void CPlay::UseCardRoutine(int pl,int place)
{
	if (place == -1) place = m_selectedPlace;

	int card = m_hand[pl][place];

	//mana
	for (int i=0;i<m_manaTypeMax;i++)
	{
		int need = m_cardList->GetNeedMana(card,i);
		m_mana[pl]->UseMana(i,need);
	}
	//use



	m_hand[pl][place] = 0;
}

void CPlay::DropCardRoutine(int pl,int place)
{
	if (place == -1) place = m_selectedPlace;


	m_hand[pl][place] = 0;
}




int CPlay::Print(void)
{
	CAreaControl::SetNextAllPrint();

	CAllGraphics::FillScreen();

	m_message->PrintMessage(10,10,"ƒvƒŒƒC‰æ–Ê");



	static int a = 0;
	a++;
	a %= 8;

	for (int i=0;i<10;i++)
	{
		int x = i * 60;
		x += (rand() % 4);
		int y = 700;
		int aa = a % 4;
		y += aa;
		if (a>=4) y -= a;

	//	y += (rand() % 4);
		m_putPeople->Put(x,y,0,1,0);
	}


	for (int i=0;i<2;i++)
	{
		m_landTimer[i]->Print();
	}


	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_placeMax;i++)
		{
			POINT pt = GetHandPoint(pl,i);
			int card = m_hand[pl][i];
			if (card > 0)
			{
				//mana check
				int md = 0;

				if (CheckMana(pl,card))
				{
					md = 1;
				}

				if (md == 1)
				{
					m_putCard->PutMiniCard(pt,card);
				}
				else
				{
					m_putCard->PutMiniCard(pt,card,50);
				}
			}
		}
	}

	for (int pl=0;pl<2;pl++)
	{
		m_mana[pl]->Print();
	}

	if (m_playMode == USECARD_MODE)
	{
		m_putCard->PutCard(270,480,m_selectedCard);

		m_useButton->Print();
		m_dropButton->Print();
		m_cancelButton->Print();
	}

	return -1;
}



void CPlay::FinalExitRoutine(void)
{
}


int CPlay::GetOnPlace(POINT pt)
{
	int dx = pt.x - (m_miniCardPoint[0].x - m_miniCardSize.cx / 2);
	int dy = pt.y - (m_miniCardPoint[0].y - m_miniCardSize.cy / 2);

	if ((dx>=0) && (dy>=0))
	{
		int nx = dx / m_miniCardNext.cx;
		int ny = dy / m_miniCardNext.cy;
		if ((nx < m_placeMax) && (ny == 0))
		{
			int ax = dx % m_miniCardNext.cx;
			if (ax < m_miniCardSize.cx)
			{
				return nx;
			}
		}
	}

	return -1;
}

POINT CPlay::GetHandPoint(int pl,int n)
{
	POINT pt;
	pt.x = m_miniCardPoint[pl].x + m_miniCardNext.cx * n;
	pt.y = m_miniCardPoint[pl].y;
	return pt;
}

BOOL CPlay::CheckMana(int pl,int card)
{
	for (int i=0;i <= m_manaTypeMax;i++)
	{
		int need = m_cardList->GetNeedMana(card,i);
		if (m_mana[pl]->GetMana(i) < need) return FALSE;
	}

	return TRUE;
}

void CPlay::ClearButton(void)
{
	m_useButton->Init();
	m_dropButton->Init();
	m_cancelButton->Init();
}


/*_*/


