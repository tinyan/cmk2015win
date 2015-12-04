

#if !defined __CMK2015WIN_SAVEDECK__
#define __CMK2015WIN_SAVEDECK__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;

class CSaveDeck : public CCommonGeneral
{
public:
	CSaveDeck(CGame* lpGame);
	~CSaveDeck();
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

