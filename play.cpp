

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


#include "putPeople.h"

#include "play.h"
#include "game.h"


#define GAMEPLAY_MODE 0
#define GAMEOVER_MODE 1
#define STAGECLEAR_MODE 2
#define RETRY_OR_EXIT_MODE 3
#define NEXT_OR_EXIT_MODE 4


CPlay::CPlay(CGame* lpGame) : CCommonGeneral(lpGame)
{
	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();

	m_putPeople = m_game2->GetPutPeople();

}

CPlay::~CPlay()
{
	End();
}

void CPlay::End(void)
{
}


int CPlay::Init(void)
{

	return -1;
}



int CPlay::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();

	if (m_mouseStatus->CheckClick(1))
	{
		return ReturnFadeOut(GAMETITLE_MODE);
	}



	return -1;
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



	return -1;
}



void CPlay::FinalExitRoutine(void)
{
}





/*_*/


