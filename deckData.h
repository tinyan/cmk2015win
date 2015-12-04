#if !defined __CMK2015WIN_DECKDATA__
#define __CMK2015WIN_DECKDATA__


class CDeckData
{
public:
	CDeckData(int n);
	~CDeckData();
	void End(void);

	int GetUsedNumber(void);
	void ClearList(void);
	void SetCard(int n,int card);
	int GetCard(int n);

	BOOL Load(int n = -1);
	BOOL Save(int n = -1);

private:
	int m_deckNumber;
	int m_listMax;
	int m_listNumber;
	int* m_data;

};

#endif
/*_*/
