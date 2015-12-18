#if !defined __CMK2015WIN_GACHA__
#define __CMK2015WIN_GACHA__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;
class CNameList;

class CHaveCard;
class CPutCard;
class CPutChara;
class CCardList;


class CGacha : public CCommonGeneral
{
public:
	CGacha(CGame* lpGame);
	~CGacha();
	void End(void);

	int Init(void);
	int Calcu(void);
	int Print(void);


	void FinalExitRoutine(void);

private:
	CGame* m_game2;
	CMyMessage* m_message;

	CHaveCard* m_haveCard;
	CPutCard* m_putCard;
	CPutChara* m_star;
	CCardList* m_cardList;

	int m_getCard;
	int m_rareRank;
	int m_starNumber;
	int m_count;
	CPicture* m_getPic;
	int m_limit1;
	int m_limit2;
};


#endif
/*_*/
