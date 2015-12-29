

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
#include "..\..\systemNNN\nnnUtilLib\commonBackButton.h"

#include "..\..\systemNNN\nnnUtilLib\suuji.h"
#include "..\..\systemNNN\nnnUtilLib\mySaveFolder.h"
#include "..\..\systemNNN\nyanLib\INCLUDE\\myFile.h"

#include "..\..\systemNNN\nnnUtilLib\systempicture.h"

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



#include "SelectDeck.h"
#include "game.h"


CSelectDeck::CSelectDeck(CGame* lpGame,int loadsave) : CCommonGeneral(lpGame)
{
	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();
	m_loadsave = loadsave;

	m_deckData = m_game2->GetDeckData();

	m_deckMax = 8;
	m_dataExistFlag = new BOOL[m_deckMax];
	m_enableFlag = new BOOL[m_deckMax];

	m_deckPrintX = 64;
	m_deckPrintY = 64;
	m_deckNextX = 0;
	m_deckNextY = 70;
	m_deckSizeX = 400;
	m_deckSizeY = 64;

	m_suuji = new CSuuji(CSystemPicture::GetSystemPicture("ta_selectdeck_number"),64,64,1);

}

CSelectDeck::~CSelectDeck()
{
	End();
}

void CSelectDeck::End(void)
{
	ENDDELETECLASS(m_suuji);
	DELETEARRAY(m_enableFlag);
	DELETEARRAY(m_dataExistFlag);
}


int CSelectDeck::Init(void)
{
	for (int i=0;i<m_deckMax;i++)
	{
		m_dataExistFlag[i] = FALSE;

		char filename[1024];
		LPSTR folder = CMySaveFolder::GetFullFolder();
		sprintf_s(filename,1024,"%s\\deck%d.xtx",folder,i);
		FILE* file = NULL;
		fopen_s(&file,filename,"rb");
		if (file != NULL)
		{
			m_dataExistFlag[i] = TRUE;
			fclose(file);
		}
	}

	for (int i=0;i<m_deckMax;i++)
	{
		m_enableFlag[i] = TRUE;
		if (m_loadsave == 0)
		{
			if (!m_dataExistFlag[i])
			{
				m_enableFlag[i] = FALSE;
			}
		}
	}

	m_onNumber = -1;

	LoadBackButtonPic();
	m_back->Init();

	if (m_classNumber == SAVEDECK_MODE)
	{
		m_commonBG->LoadDWQ("sys\\ta_selectdeck_save_bg");
	}
	else
	{
		m_commonBG->LoadDWQ("sys\\ta_selectdeck_load_bg");
	}
	
	m_commonParts->LoadDWQ("sys\\ta_selectdeck_plate");

	return -1;
}



int CSelectDeck::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();
	m_onNumber = GetOnDeck(pt);

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

	if (m_mouseStatus->CheckClick())
	{
		if (m_onNumber != -1)
		{
			if (m_enableFlag[m_onNumber])
			{
				m_game->PlaySystemSound(0);

				if (m_loadsave == 0)
				{
					return ReturnFadeOut(ProcessLoad());
				}
				else
				{
					return ReturnFadeOut(ProcessSave());
				}
			}
		}
	}



	return -1;
}


int CSelectDeck::Print(void)
{
	CAreaControl::SetNextAllPrint();

//	CAllGraphics::FillScreen();
	m_commonBG->Put(0,0,FALSE);

//	m_message->PrintMessage(10,10,"デッキ選択画面");

	for (int i=0;i<m_deckMax;i++)
	{
		POINT pt = GetDeckPoint(i);

		//通常 on ??? nodata

		int md = 0;
		if (m_dataExistFlag[i])
		{
			md = 1;
		}

		if (m_onNumber == i)
		{
			if (m_enableFlag[i])
			{
				md = 2;
			}
		}

		int sizeX = m_deckSizeX;
		int sizeY = m_deckSizeY;
		int srcX = 0;
		int srcY = sizeY * md;

		m_commonParts->Blt(pt.x,pt.y,srcX,srcY,sizeX,sizeY,TRUE);
		if (md != 0)
		{
			m_suuji->Print(pt.x+256,pt.y,i+1);
		}
//		CAllGeo::BoxFill(pt.x,pt.y,m_deckSizeX,m_deckSizeY,r,g,b);
	}

	m_back->Print();
	return -1;
}




void CSelectDeck::FinalExitRoutine(void)
{
}


POINT CSelectDeck::GetDeckPoint(int n)
{
	POINT pt;
	pt.x = m_deckPrintX + m_deckNextX * n;
	pt.y = m_deckPrintY + m_deckNextY * n;

	return pt;
}

int CSelectDeck::GetOnDeck(POINT pt)
{
	for (int i=0;i<m_deckMax;i++)
	{
		if (CheckOnDeck(i,pt))
		{
			return i;
		}
	}

	return -1;
}

BOOL CSelectDeck::CheckOnDeck(int n,POINT pt)
{
	POINT p = GetDeckPoint(n);
	int dx = pt.x - p.x;
	int dy = pt.y - p.y;
	if ((dx>=0) && (dy>=0) && (dx<m_deckSizeX) && (dy<m_deckSizeY))
	{
		return TRUE;
	}

	return FALSE;
}


/*_*/



