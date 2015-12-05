//
// game.cpp
//






#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanLib\include\commonMacro.h"
#include "..\..\systemNNN\nnnUtilLib\scriptcommand.h"
#include "..\..\systemNNN\nnnUtilLib\commonGameVersion.h"
#include "..\..\systemNNN\nnnUtilLib\nameList.h"

#include "..\..\systemNNN\nyanLib\include\myFile.h"
#include "..\..\systemNNN\nnnUtilLib\mySaveFolder.h"



//#include "..\nnnUtilLib\varNumber.h"
//#include "..\nnnUtilLib\myKeyStatus.h"
//#include "..\nnnUtilLib\inputStatus.h"
//#include "..\nnnUtilLib\gameMouse.h"
//#include "..\nnnUtilLib\messageCursor.h"
//#include "..\nnnUtilLib\sceneOptionButton.h"
//#include "..\nnnUtilLib\waveMusic.h"
#include "..\..\systemNNN\nnnUtilLib\commonSystemFile.h"


#include "..\..\systemNNN\nnnLib\commonMode.h"
//#include "..\nnnLib\execScript.h"
#include "..\..\systemNNN\nnnLib\commonGeneral.h"
//#include "..\nnnLib\commonSelectPlace.h"
//#include "..\nnnLib\commonSelectHeroin.h"
//#include "..\nnnLib\commonPrintCalendar.h"
//#include "..\nnnLib\commonPrintMovie.h"
#include "..\..\systemNNN\nnnLib\gameCallBack.h"



#include "mode.h"

#include "cardList.h"
#include "hexarea.h"
#include "putPeople.h"
#include "haveCard.h"
#include "deckData.h"
#include "putCard.h"

//#include "gameTitle.h"
#include "play.h"
#include "gameTitle.h"

#include "editDeck.h"
#include "loadDeck.h"
#include "saveDeck.h"

//#include "nekopic.h"

#include "game.h"

/*
int CGame::m_daysOfMonth[13]=
{
	0,	31,29,31,30,31,30,31,31,30,31,30,31,
};
*/




CGame::CGame(HWND hwnd, HINSTANCE hinstance, CCommonSystemFile* lpSystemFile, int windowSizeX, int windowSizeY, int bpp) : CGameCallBack(hwnd, hinstance, lpSystemFile, windowSizeX, windowSizeY, bpp)
{
}

void CGame::Create(void)
{
	if (CheckDebugOk()) SetDebugFlag();

	LPSTR saveFolder = CMySaveFolder::GetFullFolder();

	m_cardList = new CCardList();
	m_hexArea = new CHexArea();
	m_putPeople = new CPutPeople();
	m_putCard = new CPutCard(m_cardList);

	m_haveCard = new CHaveCard();
	if (!(m_haveCard->Load()))
	{
		if (m_haveCard->Load(TRUE))
		{
			m_haveCard->Save();
		}
	}

	m_deckNumber = 0;
	m_deckData = new CDeckData(0);
	if (!(m_deckData->Load(0)))
	{
		if (m_deckData->Load(0,TRUE))
		{
			m_deckData->Save(0);
		}
	}



/*
	char filename[1024];
	wsprintf(filename,"%s\\stageclear.sav",saveFolder);

	FILE* file = CMyFile::Open(filename,"rb");

	for (int i=0;i<256;i++)
	{
		m_saveData[i] = 0;
	}

	if (file != NULL)
	{
		fread(m_saveData,sizeof(int),256,file);
		fclose(file);
	}
	else
	{
		m_saveData[0] = -1;
		SetSaveData(0,0);//create and save
	}

	*/

	CreateAllClass();

	SetOption(FALSE);
	StartInitialMessage();
}


CGame::~CGame()
{
	End();
}

void CGame::End(void)
{
	ENDDELETECLASS(m_deckData);
	ENDDELETECLASS(m_haveCard);
	ENDDELETECLASS(m_putCard);
	ENDDELETECLASS(m_putPeople);
	ENDDELETECLASS(m_hexArea);
	ENDDELETECLASS(m_cardList);
}






///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CGame::CreateAllClass(void)
{
	CreateCommonClass(NOTHING_MODE);
	CreateCommonClass(LOGO_MODE);
//	CreateCommonClass(TITLE_MODE);
//	CreateCommonClass(OPENING_MODE);
//	CreateCommonClass(CONFIG_MODE);
//	CreateCommonClass(PRINTMESSAGE_MODE);
//	CreateCommonClass(SELECTPLACE_MODE);
//	CreateCommonClass(BACKLOG_MODE);
//	CreateCommonClass(PRINTOVERRAP_MODE);
//	CreateCommonClass(SELECTMESSAGE_MODE);
//	CreateCommonClass(SYSTEMMENU_MODE);
//
//	CreateCommonClass(CODECERROR_MODE);
//	CreateCommonClass(PRINTMOVIE_MODE);

//	CreateCommonClass(SELECTHEROIN_MODE);
//	CreateCommonClass(PRINTCALENDAR_MODE);

//	CreateCommonClass(PRINTMOVIE_MODE);
//	CreateCommonClass(NAMEINPUT_MODE);
//	CreateCommonClass(MYPRINTRESULT_MODE);
//	CreateCommonClass(SELECTCHART_MODE);

	if (CCommonGameVersion::CheckTaikenOrNetVersion() == FALSE)
	{
//		CreateCommonClass(OMAKE_MODE);
//		CreateCommonClass(SELECTCGCHARA_MODE);
//		CreateCommonClass(SELECTCG_MODE);
//		CreateCommonClass(SELECTSCENECHARA_MODE);
//		CreateCommonClass(SELECTSCENE_MODE);
//		CreateCommonClass(LISTENBGM_MODE);
//		CreateCommonClass(PRINTCG_MODE);
//		CreateCommonClass(LOAD_MODE);
//		CreateCommonClass(SAVE_MODE);
	}


//	m_general[GAMETITLE_MODE] = new CGameTitle(this);
	m_general[PLAY_MODE] = new CPlay(this);
	m_general[GAMETITLE_MODE] = new CGameTitle(this);
	m_general[EDITDECK_MODE] = new CEditDeck(this);
	m_general[LOADDECK_MODE] = new CLoadDeck(this);
	m_general[SAVEDECK_MODE] = new CSaveDeck(this);


//	m_general[NEKOPIC_MODE] = new CNekoPic(this);




//	CreateCommonClass(LOAD_MODE);
//	CreateCommonClass(SAVE_MODE);

//	CreateCommonClass(MINIGAME_MODE);


}




void CGame::ReceiveUserCommand(int cmd, int paraKosuu, int* paraPtr)
{
	m_skipNextCommandFlag = FALSE;
	m_userCommand = cmd;
	GetUserPara(paraKosuu, paraPtr);

//	if (m_userCommand == m_selectHeroinCommandNumber)
//	{
//		CSelectHeroin* selectHeroin = (CSelectHeroin*)m_general[SELECTHEROIN_MODE];
//		selectHeroin->StartSelectHeroin();
//		SetReturnCode(SELECTHEROIN_MODE);
//	}


}



void CGame::ReceiveUserFunction(int cmd, int paraKosuu, int* paraPtr)
{
	m_userFunction = cmd;
	GetUserPara(paraKosuu, paraPtr);

	if (m_userFunction == m_adjustDateFunction)
	{
		if (m_dayMonthVar != -1)
		{
			int d = GetVarData(m_dayMonthVar);
////			d = AdjustDate(d);
			SetVarData(m_dayMonthVar,d);
		}
	}



}






/*
int CGame::AdjustDate(int daymonth)
{
	int month = daymonth / 100;
	int day = daymonth % 100;

	if (day > m_daysOfMonth[month])
	{
		day -= m_daysOfMonth[month];
		month++;
	}

	return month * 100 + day;
}
*/







void CGame::UserCommandCallBack(void)
{
//	if (m_userCommand == m_selectPlaceCommandNumber)
//	{
//		CCommonSelectPlace* selectPlace = (CCommonSelectPlace*)(m_general[SELECTPLACE_MODE]);
//
//		SetReturnCode(SELECTPLACE_MODE);
//	}

}




int CGame::GetSaveData(int n)
{
	return m_saveData[n];
	return 0;
}

void CGame::SetSaveData(int n,int d)
{
	if (d != m_saveData[n])
	{
		m_saveData[n] = d;

		LPSTR saveFolder = CMySaveFolder::GetFullFolder();

		char filename[1024];
		wsprintf(filename,"%s\\stageclear.sav",saveFolder);

		FILE* file = CMyFile::Open(filename,"wb");

		if (file != NULL)
		{
			fwrite(m_saveData,sizeof(int),256,file);
			fclose(file);
		}
	}
}




BOOL CGame::CheckDebugOk(void)
{
	FILE* file00 = NULL;

	fopen_s(&file00,"debug666.txt","rb");
	if (file00 != NULL)
	{
		fclose(file00);
		return TRUE;
	}
	return FALSE;
}


void CGame::GetExtDataForSave(LPVOID ptr,int extNumber)
{
}

void CGame::SetExtDataByLoad(LPVOID ptr,int extNumber)
{
}



/*_*/



