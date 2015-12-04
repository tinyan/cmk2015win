

#if !defined __CMK2015WIN_GAMETITLE__
#define __CMK2015WIN_GAMETITLE__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;

class CMenuButtonSetup;
class CMenuButtonGroup;

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

	int m_basicButtonKosuu;

	CMenuButtonSetup* m_menuButtonSetup;
	CMenuButtonGroup* m_menu;

};






#endif
/*_*/

