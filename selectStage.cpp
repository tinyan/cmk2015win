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

#include "clearData.h"
#include "selectStage.h"
#include "game.h"



CSelectStage::CSelectStage(CGame* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTSTAGE_MODE);
	LoadSetupFile("selectStage",256);

	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();
	m_clearData = m_game2->GetClearData();
}


CSelectStage::~CSelectStage()
{
	End();
}

void CSelectStage::End(void)
{
}

int CSelectStage::Init(void)
{
	m_stage = m_game2->GetStage();
	m_subStage = m_game2->GetSubStage();

	return -1;
}



int CSelectStage::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();
	if (m_mouseStatus->CheckClick(1))
	{
//		return ReturnFadeOut(GAMETITLE_MODE);
	}

	if (m_mouseStatus->CheckClick())
	{
		m_game2->SetStage(m_stage,m_subStage);
		return ReturnFadeOut(PLAY_MODE);
	}




	return -1;
}


int CSelectStage::Print(void)
{
	CAreaControl::SetNextAllPrint();


	CAllGraphics::FillScreen(0,0,0);
	m_message->PrintMessage(10,10,"ステージ選択");




	return -1;
}



void CSelectStage::FinalExitRoutine(void)
{
}


/*_*/






/*_*/



