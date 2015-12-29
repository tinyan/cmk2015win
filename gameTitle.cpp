

#include <windows.h>
#include <Math.h>


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


#include "putChara.h"

#include "GameTitle.h"
#include "game.h"


CGameTitle::CGameTitle(CGame* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(GAMETITLE_MODE);
//	m_classNumber = TITLE_MODE;
	LoadSetupFile("gametitle",256);

	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();

	m_basicButtonKosuu = 3;
#if _DEBUG
	m_basicButtonKosuu = 4;
#endif

	m_menuButtonSetup = new CMenuButtonSetup(m_setup,m_basicButtonKosuu);

	m_menu = new CMenuButtonGroup(m_menuButtonSetup);

	for (int i=0;i<m_basicButtonKosuu;i++)
	{
		m_menu->SetPicture(i,CSuperButtonPicture::GetPicture(3+i));
	}

	m_nekoashiPic = new CPutChara("sys\\ta_nekoashi",4,4);

	GetFadeInOutSetup();

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

	m_commonParts->LoadDWQ("sys\\ta_title_bg");

	m_nekoX = 270.0f;
	m_nekoY = 800.0f;
	m_nekoHoukou = 90.0f;
	m_nekoKasoku = 0.0f;
	m_nekoCount = 0;

	m_nekoPointer = 0;
	for (int i=0;i<6;i++)
	{
		m_nekoZahyo[i*2] = -40.0f;
		m_nekoZahyo[i*2+1] = -40.0f;
		m_nekoMuki[i] = 0.0f;
	}

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
			return ReturnFadeOut(SELECTSTAGE_MODE);
		}

		if (nm == 1)
		{
			return ReturnFadeOut(EDITDECK_MODE);
		}

		if (nm == 2)
		{
			m_game2->SetSelectDeckBackMode(GAMETITLE_MODE);
			return ReturnFadeOut(LOADDECK_MODE);
		}

		if (nm == 3)
		{
			m_game2->InitData();
			m_menu->Init();
		}
	}


	return -1;
}


int CGameTitle::Print(void)
{
	CAreaControl::SetNextAllPrint();

//	CAllGraphics::FillScreen();

//	m_message->PrintMessage(10,10,"ƒ^ƒCƒgƒ‹‰æ–Ê");
	m_commonParts->Put(0,0,FALSE);
	m_nekoCount++;
	if (m_nekoCount > 6)
	{
		m_nekoCount = 0;
		int r = rand() % 100;
		if (r < 5)
		{
			m_nekoKasoku = (float)(rand() % 20) - 10.0f;
		}
		else if (r<15)
		{
			m_nekoKasoku -= 3.0f;
		}
		else if (r<25)
		{
			m_nekoKasoku += 3.0f;
		}

		if (m_nekoKasoku < -10.0f) m_nekoHoukou = -10.0f;
		if (m_nekoKasoku > 10.0f) m_nekoHoukou = 10.0f;

		m_nekoHoukou += m_nekoKasoku;
		if (m_nekoHoukou > 360.0f) m_nekoHoukou -= 360.0f;
		if (m_nekoHoukou < 0.0f) m_nekoHoukou += 360.0f;


		float th = (float)m_nekoHoukou;
		th /= 360.0f;
		th *= 3.14159f * 2.0f;
		float speed = 32.0f;
		float speedX = speed * cos(th);
		float speedY = speed * sin(th);
		m_nekoX += speedX;
		m_nekoY += speedY;
		if ((m_nekoX < -64.0f) || (m_nekoY < -64.0f) || (m_nekoX > 600.0f) || (m_nekoY > 1000.0f))
		{
			m_nekoX = (float)(rand() % 444) + 50.0f;
			m_nekoY = (float)(rand() % 860) + 50.0f;
			m_nekoHoukou = (float)(rand() % 360);
			m_nekoKasoku = (float)(rand() % 20) - 10.0f;
		}


		float haba = 20.0f;
		float th1 = th + 3.14159f / 2.0f;
		float dx = haba * cos(th1);
		float dy = haba * sin(th1);

		float s = 1.0f;
		if ((m_nekoPointer % 2) == 0) s = -1.0f;

		float x = m_nekoX + dx * s;
		float y = m_nekoY + dy * s;

		float hh = m_nekoHoukou;
		if ((rand () % 100) < 40)
		{
			hh += (float)(rand() % 64);
			hh -= 32.0f;
			if (hh > 360.0f) hh -= 360.0f;
			if (hh < 0.0f) hh += 360.0f;
		}

		m_nekoMuki[m_nekoPointer] = hh;

		m_nekoZahyo[m_nekoPointer*2+0] = x;
		m_nekoZahyo[m_nekoPointer*2+1] = y;
		m_nekoPointer++;
		m_nekoPointer %= 6;
	}

	for (int i=0;i<6;i++)
	{
		int putX = (int)m_nekoZahyo[i*2+0];
		int putY = (int)m_nekoZahyo[i*2+1];
		int h = (int)(m_nekoMuki[i] / (360.0f/16.0f));
		
//		if ((rand () % 100) < 40)
//		{
//			h += (rand() % 2)*2;
//			h -= 1;
		//}

		h += 16;
		h %= 16;

		m_nekoashiPic->Put(putX,putY,h);
	}

	m_menu->Print(TRUE);


	return -1;
}




void CGameTitle::FinalExitRoutine(void)
{
}


/*_*/



