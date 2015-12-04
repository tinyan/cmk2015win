

#if !defined __CMK2015WIN_GAMETITLE__
#define __CMK2015WIN_GAMETITLE__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;

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

private:
	CGame* m_game2;
	CMyMessage* m_message;


};






#endif
/*_*/

