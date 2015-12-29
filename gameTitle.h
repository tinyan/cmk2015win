

#if !defined __CMK2015WIN_GAMETITLE__
#define __CMK2015WIN_GAMETITLE__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;

class CMenuButtonSetup;
class CMenuButtonGroup;

class CPutChara;


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

	CPutChara* m_nekoashiPic;

	int m_nekoCount;
	float m_nekoX;
	float m_nekoY;
	float m_nekoHoukou;
	float m_nekoKasoku;

	float m_nekoZahyo[6*2];
	float m_nekoMuki[6];
	int m_nekoPointer;
};






#endif
/*_*/

