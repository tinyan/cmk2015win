#if !defined __CMK2015WIN_DAMAGESUUJI__
#define __CMK2015WIN_DAMAGESUUJI__


class CSuuji;

class CDamageSuuji
{
public:
	CDamageSuuji();
	~CDamageSuuji();
	void End(void);

	void AllClear(void);
	void AddSuuji(int x,int y,int d,int col = 0);
	void Calcu(int cnt = 1);
	void Print(void);

	typedef struct _tagSUUJIWORK
	{
		int flag;
		int x,y;
		int data;
		int count;
		int countMax;
		int color;
	}SUUJIWORK;

private:
	CSuuji* m_suuji;
	int m_dataNumber;
	int m_dataMax;
	int m_lastSet;

	SUUJIWORK* m_work;
	int SearchAki(void);

};

#endif
/*_*/
