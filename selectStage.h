#if !defined __CMK2015WIN_SELECTSTAGE__
#define __CMK2015WIN_SELECTSTAGE__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;

class CHaveCard;
class CPutCard;
class CPutChara;
class CCardList;
class CClearData;
class CStageData;

class CSelectStage : public CCommonGeneral
{
public:
	CSelectStage(CGame* lpGame);
	~CSelectStage();
	void End(void);

	int Init(void);
	int Calcu(void);
	int Print(void);


	void FinalExitRoutine(void);

private:
	CGame* m_game2;
	CMyMessage* m_message;

	int m_stage;
	int m_subStage;
	BOOL* m_enableFlag;

	CStageData* m_stageData;
	CClearData* m_clearData;
	int m_stageMax;
	int m_subStageMax;

	int m_onNumber;
	int GetOnNumber(POINT pt);

	POINT GetStagePoint(int n);

	int m_stagePrintX;
	int m_stagePrintY;
	int m_stageSizeX;
	int m_stageSizeY;
	int m_stageNextX;
	int m_stageNextY;

	CPutChara* m_stagePic;
	CPutChara* m_subMark;
	int m_existStage;
	int m_scrollX;
	int m_scrollY;
};


#endif
/*_*/
