//
//
//

#if !defined __NNNEXE_GAME__
#define __NNNEXE_GAME__


//#include "..\nnnLib\gameCallBack.h"

class CCommonSystemFile;
class CNameList;
class CPutPeople;
class CHaveCard;
class CCardList;
class CDeckData;
class CPutCard;
class CStageData;
class CClearData;

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
class CHexArea;

class CGame : public CGameCallBack
{
public:
	CGame(HWND hwnd, HINSTANCE hinstance, CCommonSystemFile* lpSystemFile, int windowSizeX, int windowSizeY, int bpp);
	virtual ~CGame();
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

//	int GetSelectedStage(void){return m_selectedStage;}
//	void SetSelectedStage(int stage){m_selectedStage = stage;}
	CHexArea* GetHexArea(void){return m_hexArea;}
	CPutPeople* GetPutPeople(void){return m_putPeople;}
	CHaveCard* GetHaveCard(void){return m_haveCard;}
	CCardList* GetCardList(void){return m_cardList;}
	CDeckData* GetDeckData(void){return m_deckData;}
	CDeckData* GetEnemyDeckData(void){return m_enemyDeckData;}
	CPutCard* GetPutCard(void){return m_putCard;}
	CStageData* GetStageData(void){return m_stageData;}
	CClearData* GetClearData(void){return m_clearData;}

	void InitData(void);
	void SetGachaCard(int card){m_gachaCard = card;}
	int GetGachaCard(void){return m_gachaCard;}
	int GetStage(void){return m_stage;}
	int GetSubStage(void){return m_subStage;}
	void SetStage(int stage,int subStage);
	void SetSelectDeckBackMode(int mode);
	int GetSelectDeckBackMode(void){return m_selectDeckBackMode;}
	int GetDeckNumber(void){return m_deckNumber;}
	void SetDeckNumber(int n);
	void ClearStage(int stage,int subStage);

private:
	void CreateAllClass(void);
//	void AfterInitNewGame(int uraMode = 0, BOOL demoFlag = FALSE);

	BOOL CheckDebugOk(void);

	CCardList* m_cardList;
	CHexArea* m_hexArea;
	CPutPeople* m_putPeople;

	CHaveCard* m_haveCard;
	CDeckData* m_deckData;
	CDeckData* m_enemyDeckData;
	CPutCard* m_putCard;
	CStageData* m_stageData;
	CClearData* m_clearData;
//	int m_selectedStage;
	int m_deckNumber;
	int m_gachaCard;

	int m_stage;
	int m_subStage;
	int m_selectDeckBackMode;


	int m_saveData[256];
};





#endif
/*_*/

