

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

	int m_cardPerPage;

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

	RECT m_upperArea;
	RECT m_lowerArea;

	BOOL CheckInArea(POINT pt,RECT* lpRect);
};






#endif
/*_*/

