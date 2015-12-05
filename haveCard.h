#if !defined __CMK2015WIN_HAVECARD__
#define __CMK2015WIN_HAVECARD__


class CHaveCard
{
public:
	CHaveCard();
	~CHaveCard();
	void End(void);

	BOOL Load(BOOL defaultFlag = FALSE);
	BOOL Save(void);

	void ClearList(void);
	void SetCard(int card,int n=1);
	int GetCard(int card);

	int CalcuCardList(void);
	int GetCardListCard(int n);
	int GetCardListNumber(int n);


private:
	int m_listMax;
	int* m_data;
	int* m_cardList;
	int m_cardListNumber;

};

#endif
/*_*/
