

#if !defined __CMK2015WIN_LOADDECK__
#define __CMK2015WIN_LOADDECK__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;
class CSelectDeck;

class CLoadDeck : public CSelectDeck
{
public:
	CLoadDeck(CGame* lpGame);
	~CLoadDeck();
	void End(void);

//	int Init(void);
//	int Calcu(void);
//	int Print(void);
//	void FinalExitRoutine(void);
	int ProcessLoad(void);

private:
	


};






#endif
/*_*/

