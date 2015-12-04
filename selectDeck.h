

#if !defined __CMK2015WIN_SELECTDECK__
#define __CMK2015WIN_SELECTDECK__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;

class CSelectDeck : public CCommonGeneral
{
public:
	CSelectDeck(CGame* lpGame);
	~CSelectDeck();
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

