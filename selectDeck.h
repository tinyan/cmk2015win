

#if !defined __CMK2015WIN_SELECTDECK__
#define __CMK2015WIN_SELECTDECK__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;

class CDeckData;

class CSelectDeck : public CCommonGeneral
{
public:
	CSelectDeck(CGame* lpGame,int loadsave);
	virtual ~CSelectDeck();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual int ProcessLoad(void){return -1;}
	virtual int ProcessSave(void){return -1;}


	virtual void FinalExitRoutine(void);

protected:
	CGame* m_game2;
	CMyMessage* m_message;
	int m_loadsave;

	int m_deckMax;
	BOOL* m_dataExistFlag;
	BOOL* m_enableFlag;

	int m_onNumber;

	int m_deckPrintX;
	int m_deckPrintY;
	int m_deckNextX;
	int m_deckNextY;
	int m_deckSizeX;
	int m_deckSizeY;
	POINT GetDeckPoint(int n);
	int GetOnDeck(POINT pt);
	BOOL CheckOnDeck(int n,POINT pt);

	CDeckData* m_deckData;


};






#endif
/*_*/

