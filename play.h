

#if !defined __CMK2008SUMMER_PLAY__
#define __CMK2008SUMMER_PLAY__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CBug;

class CArea;
class CStageData;

//class CClearStage;
//class CMapData;
//class CDemoPlay;

//class CHajike;


//class CPrintCountDown;
//class CPrintHaikei;
//class CPrintPlate;
//class CPrintScore;
//class CPrintGameStatus;


//class CHighScoreData;
//class CResultControl;

//class CPlayStageType1;
//class CPlayStageCommon;

class CNameList;

class CPlay : public CCommonGeneral
{
public:
	CPlay(CGame* lpGame);
	~CPlay();
	void End(void);

	int Init(void);
	int Calcu(void);
	int Print(void);


	void FinalExitRoutine(void);

//	void SetDemoMode(BOOL md = TRUE);

//	void SetStage(int stage);
private:
	CGame* m_game2;
	CMyMessage* m_message;

	CPicture* m_pic;

	CBug* m_bug[20];

	int m_playMode;
	int m_waitClickOff;
	int m_drawingFlag;
	BOOL m_movingFlag;

	POINT m_startPoint;
	POINT m_lastPoint;

	BOOL CheckInRange(POINT pt1,POINT pt2,int range);


	int m_bugMax;


	int m_effectCount[100];
	int m_effectFlag[100];
	RECT m_effectRect[100];


	CArea* m_startArea;
	CArea* m_block[100];
	CArea* m_mirror[100];
	int m_mirrorType[100];
	CArea* m_target[100];
	int m_targetFlag[100];
	int m_targetType[100];

	CStageData* m_stageData[24];

	CArea* m_button[3];

	int SearchAkiBug(void);

	void PutStartArea(RECT rc);
	void PutStartArea(POINT pt,SIZE sz);
	void PutStartArea(int x,int y,int sizeX,int sizeY);

	void PutMirror(RECT rc,int tate);
	void PutMirror(POINT pt,SIZE sz,int tate);
	void PutMirror(int x,int y,int sizeX,int sizeY,int tate);

	void PutBlock(RECT rc);
	void PutBlock(POINT pt,SIZE sz);
	void PutBlock(int x,int y,int sizeX,int sizeY);

	void PutTarget(RECT rc,int type);
	void PutTarget(POINT pt,SIZE sz,int type);
	void PutTarget(int x,int y,int sizeX,int sizeY,int type);

	void PutRoutine(int x,int y,int sizeX,int sizeY,int srcX,int srcY,int srcSizeX,int srcSizeY,BOOL transFlag = TRUE);

	void PutRetryButton(void);
	void PutNextButton(void);
	void PutExitButton(void);

	void AddGetEffect(RECT rc);
	void PrintEffect(void);

	void InitNewStage(void);

//	int m_demoFlag;
//	int m_demoCount;
/*
	int m_life;
	int m_stage;
	int m_score;
	int m_highScore;
	int m_maxStage;
	int m_time;

	int m_stageKosuu;

	int m_bonusScore;
	int m_bonusTime;
	int m_bonusLife;
*/

	/*
	POINT m_start;
	POINT m_start0;

	CPicture* m_pic;
	CPicture* m_bg;

	int* m_panel;
	int* m_panelCount;
	int* m_panelCheck;

	int m_mapSizeX;
	int m_mapSizeY;

	void ClearPanel(void);
	void ClearPanelCount(void);
	void ClearPanelCheck(void);


	BOOL CheckClear(void);
	BOOL CheckGameOver(void);

	POINT GetPanelZahyo(int x,int y);
	int m_panelPrintX;
	int m_panelPrintY;
	int m_panelSizeX;
	int m_panelSizeY;

	int GetPanel(int x,int y);
	int GetPanelCount(int x,int y);
	int GetPanelCheck(int x,int y);

	void SetPanel(int x,int y,int d);
	void SetPanelCount(int x,int y,int c);
	void SetPanelCheck(int x,int y,int chk=1);

	void PutPanel(int x,int y,int panel,int check,int count);

	CClearStage* m_clearStage;
	CMapData* m_mapData[10];

	int m_nokori;

	void CalcuPanel(void);

	int m_panelCountMax;
	void SetPanelEffect(int x,int y,int panelNum);

	int m_panelSpeed[10];

	POINT GetOnBlock(POINT pt);

	int m_demoNumber;
	int m_demoLimit;

	CHajike* m_hajike;

	int m_autoDemoCount;
	int m_autoDemoTime;

	BOOL CheckNoCalcu(void);
	BOOL m_changedFlag;

	CDemoPlay* m_demoPlay[5][3];
*/

	/*
	CPrintCountDown* m_printCountDown;
	CPrintHaikei* m_printHaikei;
	CPrintPlate* m_printPlate;
	CPrintScore* m_printScore;

	CPrintGameStatus* m_printGameStatus;

	CResultControl* m_resultControl;


	CPlayStageCommon* m_playStageClass[10];

	int m_startZeroCount;

	void SetStageData(void);
	void CalcuBonusUp(int& bonus,int& target,int limit,BOOL allFlag = FALSE);

	CHighScoreData* m_highScoreData;

	CNameList* m_stageData;
	int m_playClassNumber;
	int m_bgNumber;

	int m_gameClearCount;

	void PlayCountDownSound(int n);
	void PlayWarningSound(int n);
	void PlayGameOverSound(void);
	void PlayGameClearSound(void);

	int m_cannotClickCount;
	*/

	int m_stageNumber;

	int m_targetNumber;
	int m_mirrorNumber;
	int m_blockNumber;

	int m_targetNokori;

	int m_mirrorSound;
	int m_getSound;

	void StartClearStage(void);
	int m_stageClearCount;
	int m_gameOverCount;

	void StartGameOverMode(void);
	void StartRetryOrExitMode(void);
	void StartNextOrExitMode(void);

	BOOL CheckOnRetryButton(POINT pt);
	BOOL CheckOnNextButton(POINT pt);
	BOOL CheckOnExitButton(POINT pt);

	int m_stageClearSound;
	int m_gameOverSound;
};






#endif
/*_*/

