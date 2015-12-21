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

	CClearData* m_clearData;
};


#endif
/*_*/
