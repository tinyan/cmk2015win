

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

#include "..\..\systemNNN\nnnUtilLib\superButtonPicture.h"
#include "..\..\systemNNN\nnnUtilLib\commonButton.h"
#include "..\..\systemNNN\nnnUtilLib\commonButtonGroup.h"
#include "..\..\systemNNN\nnnUtilLib\commonUpDownButtonGroup.h"
#include "..\..\systemNNN\nnnUtilLib\commonBackButton.h"


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

#include "deckData.h"
#include "selectDeck.h"
#include "saveDeck.h"
#include "game.h"


CSaveDeck::CSaveDeck(CGame* lpGame) : CSelectDeck(lpGame,1)
{
	
	SetClassNumber(SAVEDECK_MODE);
	LoadSetupFile("savedeck",256);

	CreateBackButton();
	GetFadeInOutSetup();

}

CSaveDeck::~CSaveDeck()
{
	End();
}

void CSaveDeck::End(void)
{
}

/*
int CSaveDeck::Init(void)
{
	CSelectDeck::Init();

	LoadBackButtonPic();
	m_back->Init();

	return -1;
}



int CSaveDeck::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();

	int rt = m_back->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);
		if (nm == 0)
		{
			int backMode = m_game2->GetSelectDeckBackMode();
			return ReturnFadeOut(backMode);
		}
	}




	return -1;
}


int CSaveDeck::Print(void)
{
	CAreaControl::SetNextAllPrint();

	CAllGraphics::FillScreen();

	m_message->PrintMessage(10,10,"ƒZ[ƒu‰æ–Ê");




	return -1;
}



void CSaveDeck::FinalExitRoutine(void)
{
}
*/

int CSaveDeck::ProcessSave(void)
{
	m_game2->SetDeckNumber(m_onNumber);
	m_deckData->Save(m_onNumber);


	return GAMETITLE_MODE;
}


/*_*/



