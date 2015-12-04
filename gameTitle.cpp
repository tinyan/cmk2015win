

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


#include "..\..\systemNNN\nnnUtilLib\inputStatus.h"


#include "..\..\systemNNN\nnnUtilLib\menuButtonGroup.h"
#include "..\..\systemNNN\nnnUtilLib\menuButtonSetup.h"





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



#include "GameTitle.h"
#include "game.h"


CGameTitle::CGameTitle(CGame* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(GAMETITLE_MODE);
//	m_classNumber = TITLE_MODE;
	LoadSetupFile("gametitle",256);

	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();

	m_basicButtonKosuu = 2;
	m_menuButtonSetup = new CMenuButtonSetup(m_setup,m_basicButtonKosuu);

	m_menu = new CMenuButtonGroup(m_menuButtonSetup);

	for (int i=0;i<m_basicButtonKosuu;i++)
	{
		m_menu->SetPicture(i,CSuperButtonPicture::GetPicture(3+i));
	}


}

CGameTitle::~CGameTitle()
{
	End();
}

void CGameTitle::End(void)
{
	ENDDELETECLASS(m_menu);
	ENDDELETECLASS(m_menuButtonSetup);

}


int CGameTitle::Init(void)
{
	for (int i=0;i<m_basicButtonKosuu;i++)
	{
		CPicture* lpPic = m_menu->GetPicture(i);
		LPSTR name = m_menu->GetFileName(i);
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}

	m_menu->Init();

	return -1;
}



int CGameTitle::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();

	int rt = m_menu->Calcu(m_inputStatus);
	int st = CCommonButton::GetButtonStatus(rt);
	int requestSoundFlag = CCommonButton::CheckRequestSound(rt);
	int sound = 0;
	if (requestSoundFlag)
	{
		sound = CCommonButton::GetButtonSound(rt);
	}
	int existDataFlag = CCommonButton::CheckExistData(rt);
	int nm = -1;
	if (existDataFlag)
	{
		nm = CCommonButton::GetButtonData(rt);
	}

	if (requestSoundFlag)
	{
		if (sound > 0)
		{
			m_game->PlaySystemSound(sound - 1);
		}
	}



	if ((st == NNNBUTTON_NUMBER) && (existDataFlag))
	{
		if (nm == 0)
		{
			return ReturnFadeOut(PLAY_MODE);
		}

		if (nm == 1)
		{
			return ReturnFadeOut(EDITDECK_MODE);
		}
	}


	return -1;
}


int CGameTitle::Print(void)
{
	CAreaControl::SetNextAllPrint();

	CAllGraphics::FillScreen();

	m_message->PrintMessage(10,10,"ƒ^ƒCƒgƒ‹‰æ–Ê");

	m_menu->Print(TRUE);


	return -1;
}




void CGameTitle::FinalExitRoutine(void)
{
}


/*_*/



