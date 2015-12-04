

#if !defined __CMK2015WIN_EDITDECK__
#define __CMK2015WIN_EDITDECK__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;

class CEditDeck : public CCommonGeneral
{
public:
	CEditDeck(CGame* lpGame);
	~CEditDeck();
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

