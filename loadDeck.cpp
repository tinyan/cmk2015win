

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


#include "..\..\systemNNN\nnnUtilLib\superButtonPicture.h"
#include "..\..\systemNNN\nnnUtilLib\commonButton.h"
#include "..\..\systemNNN\nnnUtilLib\commonButtonGroup.h"
#include "..\..\systemNNN\nnnUtilLib\commonUpDownButtonGroup.h"
#include "..\..\systemNNN\nnnUtilLib\commonBackButton.h"


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

#include "deckData.h"
#include "selectDeck.h"
#include "loadDeck.h"
#include "game.h"


CLoadDeck::CLoadDeck(CGame* lpGame) : CSelectDeck(lpGame,0)
{
	SetClassNumber(LOADDECK_MODE);
	LoadSetupFile("loaddeck",256);

	CreateBackButton();
	GetFadeInOutSetup();

}

CLoadDeck::~CLoadDeck()
{
	End();
}

void CLoadDeck::End(void)
{
}

/*
int CLoadDeck::Init(void)
{
	CSelectDeck::Init();

	LoadBackButtonPic();
	m_back->Init();

	return -1;
}



int CLoadDeck::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();





	return -1;
}
*/

/*
int CLoadDeck::Print(void)
{
	CAreaControl::SetNextAllPrint();

	CAllGraphics::FillScreen();

	m_message->PrintMessage(10,10,"ƒ[ƒh‰æ–Ê");





	return -1;
}
*/

/*
void CLoadDeck::FinalExitRoutine(void)
{
}
*/


int CLoadDeck::ProcessLoad(void)
{
	m_game2->SetDeckNumber(m_onNumber);
	m_deckData->Load(m_onNumber);


	return GAMETITLE_MODE;
}


/*_*/



