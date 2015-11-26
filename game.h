//
//
//

#if !defined __NNNEXE_GAME__
#define __NNNEXE_GAME__


//#include "..\nnnLib\gameCallBack.h"

class CCommonSystemFile;
class CNameList;

//class CMakeParty;
//class CPartyStatusList;
//class CSelectMagicMenu;
//class CUtil;

//class CCharaStart;
//class CHouseLevel;

//class CCharaNumber;
//class CGameMouse;

//class CModePlate;

//class CKatakana;

//class CAreaHaveHouse;

//class COkimonoList;
//class CMoveMaskTable;

//class CHouseToSerial;

//class CEventList;

//class CDungeonAreaList;

//class CGameItem;
//class CHaveItem;

//class CCharaStatus;
//class CCastleLevel;

class CGameCallBack;

class CGame : public CGameCallBack
{
public:
	CGame(HWND hwnd, HINSTANCE hinstance, CCommonSystemFile* lpSystemFile, int windowSizeX, int windowSizeY, int bpp);
	~CGame();
	void End(void);


//
	void ReceiveUserCommand(int cmd, int paraKosuu, int* paraPtr);
	void ReceiveUserFunction(int cmd, int paraKosuu, int* paraPtr);
	void UserCommandCallBack(void);

	/////////////////////////////////////////////Ç±ÇÃÇ÷ÇÒÇ…ïKóvÇ»ä÷êîÇí«â¡

	//åpè≥
	void GetExtDataForSave(LPVOID ptr,int extNumber = 0);
	void SetExtDataByLoad(LPVOID ptr,int extNumber = 0);

	void Create(void);

	int GetSaveData(int n);
	void SetSaveData(int n,int d);

	int GetSelectedStage(void){return m_selectedStage;}
	void SetSelectedStage(int stage){m_selectedStage = stage;}

private:
	void CreateAllClass(void);
//	void AfterInitNewGame(int uraMode = 0, BOOL demoFlag = FALSE);

	BOOL CheckDebugOk(void);

	int m_selectedStage;

	int m_saveData[256];
};





#endif
/*_*/

