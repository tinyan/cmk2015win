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
#include "..\..\systemNNN\nnnUtilLib\commonBackButton.h"


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

#include "clearData.h"
#include "stageData.h"

#include "selectStage.h"
#include "game.h"



CSelectStage::CSelectStage(CGame* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTSTAGE_MODE);
	LoadSetupFile("selectStage",256);

	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();
	m_clearData = m_game2->GetClearData();
	m_stageData = m_game2->GetStageData();

	m_stageMax = m_stageData->GetStageMax();
	m_existStage = 4;
	m_subStageMax = m_stageData->GetSubStageMax();

	m_enableFlag = new BOOL[m_stageMax];

	m_stagePrintX = 270;
	m_stagePrintY = 100;
	m_stageSizeX = 384;
	m_stageSizeY = 64;
	m_stageNextX = 0;
	m_stageNextY = 120;

	GetFadeInOutSetup();

	m_stagePic = new CPutChara("sys\\ta_selectStage_stage",2,4);
	m_subMark = new CPutChara("sys\\ta_selectStage_submark",2,1);
	CreateBackButton();
}


CSelectStage::~CSelectStage()
{
	End();
}

void CSelectStage::End(void)
{
	ENDDELETECLASS(m_subMark);
	ENDDELETECLASS(m_stagePic);
	DELETEARRAY(m_enableFlag);
}

int CSelectStage::Init(void)
{
	m_stage = m_game2->GetStage();
	m_subStage = m_game2->GetSubStage();

	m_enableFlag[0] = TRUE;
	for (int stage=1;stage<m_stageMax;stage++)
	{
		BOOL f = FALSE;

		int subMax = m_stageData->GetSubStageNumber(stage-1);
		if (m_clearData->GetData(stage-1,subMax-1) > 0)
		{
			f = TRUE;
		}

		m_enableFlag[stage] = f;
	}

	LoadBackButtonPic();
	m_back->Init();

	m_onNumber = -1;

	m_commonParts->LoadDWQ("sys\\ta_selectstage_scroll");
	m_scrollX = 0;
	m_scrollY = 0;

	return -1;
}



int CSelectStage::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();
	if (m_mouseStatus->CheckClick(1))
	{
//		return ReturnFadeOut(GAMETITLE_MODE);
	}

	m_onNumber = GetOnNumber(pt);

	int rt = m_back->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);
		if (nm == 0)
		{
			return ReturnFadeOut(GAMETITLE_MODE);
		}
	}


	if (m_mouseStatus->CheckClick())
	{
		if (m_onNumber != -1)
		{
			if (m_enableFlag[m_onNumber])
			{
				m_stage = m_onNumber;
				m_subStage = 0;
				m_game2->SetStage(m_stage,m_subStage);
				m_game->PlaySystemSound(0);
				return ReturnFadeOut(PLAY_MODE);
			}
		}
	}




	return -1;
}


int CSelectStage::Print(void)
{
	CAreaControl::SetNextAllPrint();


//	CAllGraphics::FillScreen(0,0,0);
//	m_message->PrintMessage(10,10,"ステージ選択");

	m_scrollX += 5;
	m_scrollX %= 200;
	m_scrollY += 2;
	m_scrollY %= 200;

	for (int j=-1;j<5;j++)
	{
		for (int i=-1;i<3;i++)
		{
			int x = i*200+m_scrollX;
			int y = j*200+m_scrollY;
			m_commonParts->Put(x,y,FALSE);
		}
	}

	for (int stage = 0;stage < m_existStage; stage++)
	{
		POINT pt = GetStagePoint(stage);
		if (m_enableFlag[stage])
		{
			int md = 0;
			if (m_onNumber == stage)
			{
				md = 1;
			}
			m_stagePic->Put(pt,md,stage);
		}
		else
		{
			m_stagePic->TransPut(pt,0,stage,50);
		}

		int subStageNumber = m_stageData->GetSubStageNumber(stage);
		for (int k=0;k<subStageNumber;k++)
		{
			int x = pt.x + 40 + 40 * k;
			int y = pt.y + 50;
			int md = 0;
			if (m_clearData->GetData(stage,k) > 0) md = 1;
			m_subMark->Put(x,y,md,0);
		}
	}

	m_back->Print();

	return -1;
}



void CSelectStage::FinalExitRoutine(void)
{
}


int CSelectStage::GetOnNumber(POINT pt)
{
	int rt = -1;

	int limitX = m_stageSizeX / 2;
	int limitY = m_stageSizeY / 2;

	for (int i=0;i<m_existStage;i++)
	{
		if (m_enableFlag[i])
		{
			POINT p = GetStagePoint(i);
			int dx = pt.x - p.x;
			int dy = pt.y - p.y;

			if ((dx > -limitX) && (dx < limitX) && (dy > -limitY) && (dy < limitY))
			{
				return i;
			}
		}
	}


	return rt;
}


POINT CSelectStage::GetStagePoint(int n)
{
	POINT pt;

	int x = m_stagePrintX + m_stageNextX * n;
	int y = m_stagePrintY + m_stageNextY * n;

	pt.x = x;
	pt.y = y;

	return pt;
}

/*_*/






/*_*/



