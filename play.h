

#if !defined __CMK2008SUMMER_PLAY__
#define __CMK2008SUMMER_PLAY__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;

class CNameList;
class CPutPeople;

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

private:
	CGame* m_game2;
	CMyMessage* m_message;

	CPutPeople* m_putPeople;

};






#endif
/*_*/

