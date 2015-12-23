

#if !defined __CMK2015WIN_SAVEDECK__
#define __CMK2015WIN_SAVEDECK__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;
class CSelectDeck;

class CSaveDeck : public CSelectDeck
{
public:
	CSaveDeck(CGame* lpGame);
	~CSaveDeck();
	void End(void);

//	int Init(void);
//	int Calcu(void);
//	int Print(void);
//	void FinalExitRoutine(void);

	int ProcessSave(void);

private:



};






#endif
/*_*/

