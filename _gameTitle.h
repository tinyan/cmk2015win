

#if !defined __CMK2008SUMMER_GAMETITLE__
#define __CMK2008SUMMER_GAMETITLE__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
//class CPrintgameStatus;
//class CClearStage;

class CGameTitle : public CCommonGeneral
{
public:
	CGameTitle(CGame* lpGame);
	~CGameTitle();
	void End(void);

	int Init(void);
	int Calcu(void);
	int Print(void);


	void FinalExitRoutine(void);

//	void SetStageMax(int stageMax){m_stageMax = stageMax;}
private:
	CGame* m_game2;
	CMyMessage* m_message;

	int m_clear[25];
	int m_selectOk[25];
	POINT m_deltaXY[25];
	SIZE m_multi[25];

	int m_waveCount;
	int m_waveMax;
	int m_waveStart;
	int m_waveSize;
	int m_waveSpeed;

	void CalcuWave(void);

	int m_buttonPrintX;
	int m_buttonPrintY;
	int m_buttonNextX;
	int m_buttonNextY;
	int m_buttonSizeX;
	int m_buttonSizeY;

	int m_nowOnButton;
	int GetOnButton(POINT pt);

};






#endif
/*_*/

