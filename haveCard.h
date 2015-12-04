#if !defined __CMK2015WIN_HAVECARD__
#define __CMK2015WIN_HAVECARD__


class CHaveCard
{
public:
	CHaveCard();
	~CHaveCard();
	void End(void);

	BOOL Load(void);
	BOOL Save(void);

	void ClearList(void);
	void SetCard(int card,int n=1);
	int GetCard(int card);

private:
	int m_listMax;
	int* m_data;

};

#endif
/*_*/
