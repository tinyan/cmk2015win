

#if !defined __CMK2015WIN_EDITDECK__
#define __CMK2015WIN_EDITDECK__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;
class CPutCard;
class CHaveCard;
class CDeckData;

class CCommonButton;

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

	CPutCard* m_putCard;
	CHaveCard* m_haveCard;
	CDeckData* m_deckData;

	void CreateCardList(void);
	void ExpandWork(int n);
	void AddUsed(int card,int add = 1);

	int m_listNumber;

	int m_baseCardPerPage;
	int m_baseCardPerPageX;
	int m_baseCardPerPageY;

	int m_deckCardPrintNumberX;
	int m_deckCardPrintNumberY;
	int m_deckCardNumber;

	POINT m_deckCardPrint;
	SIZE m_deckCardNext;
	SIZE m_deckCardSize;


	POINT m_baseCardPrint;
	SIZE m_baseCardNext;
	SIZE m_baseCardSize;



	int m_workMax;
	int* m_card;
	int* m_cardNumber;
	int* m_cardUsed;

	int m_captureCard;
	int m_captureFromArea;
	int m_captureFromPlace;
	int m_captureFromPage;

	void GetOnArea(POINT pt);
	int m_onAreaType;
	int m_onAreaNumber;

	RECT m_deckArea;
	RECT m_baseArea;

	BOOL CheckInArea(POINT pt,RECT* lpRect);

	int m_page;
	int m_pageMax;

	CCommonButton* m_saveButton;

	void ChangePage(int updown);

	POINT GetDeckPoint(int n);
	POINT GetBasePoint(int place);

	int GetOnDeck(POINT pt);
	int GetOnBase(POINT pt);

	void Modosu(void);

	int m_largeCardPrintCount;
};






#endif
/*_*/

