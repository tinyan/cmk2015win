

#if !defined __CMK2008SUMMER_NEKPPIC__
#define __CMK2008SUMMER_NEKPPIC__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
//class CPrintgameStatus;
//class CClearStage;
class CArea;
class CStageData;

class CNekoPic : public CCommonGeneral
{
public:
	CNekoPic(CGame* lpGame);
	~CNekoPic();
	void End(void);

	int Init(void);
	int Calcu(void);
	int Print(void);


	void FinalExitRoutine(void);

//	void SetStageMax(int stageMax){m_stageMax = stageMax;}
private:
	CGame* m_game2;
	CMyMessage* m_message;

	CStageData* m_stageData;

	BOOL m_buttonFlag;

	int m_mirrorNumber;
	CArea* m_mirror[100];
	int m_mirrorType[100];

	int m_bugSpeed[20];
	int m_bugColor[20];
	int m_bugLength[20];
	int m_bugSize[20];

	CBug* m_bug[20];
	int m_bugMax;

	int m_nowSelectBug;

	void PutMirror(RECT rc,int tate);
	void PutMirror(POINT pt,SIZE sz,int tate);
	void PutMirror(int x,int y,int sizeX,int sizeY,int tate);

	void PutRoutine(int x,int y,int sizeX,int sizeY,int srcX,int srcY,int srcSizeX,int srcSizeY,BOOL transFlag = TRUE);

	POINT m_startPoint;
	POINT m_lastPoint;
	int m_movingFlag;
	int m_drawingFlag;
	int m_waitClickOff;

	BOOL CheckInRange(POINT pt1,POINT pt2,int range);

	int m_buttonEffectCount;
	BOOL CheckOnButton(int n,POINT pt);

	BOOL m_firstClick;
};


#endif
/*_*/