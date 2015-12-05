#if !defined __CMK2015WIN_PUTCARD__
#define __CMK2015WIN_PUTCARD__

class CPutChara;
class CCardList;

class CPutCard
{
public:
	CPutCard(CCardList* cardList);
	~CPutCard();
	void End(void);

	void PutCard(int x,int y,int card,int ps = 100);
	void PutMiniCard(int x,int y,int card,int ps = 100);
protected:
	CCardList* m_cardList;

private:
	int m_seatMax;
	CPutChara* m_card[16];
	CPutChara* m_miniCard;

};

#endif
/*_*/
