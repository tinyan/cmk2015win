#if !defined __CMK2015WIN_PUTPEOPLE__
#define __CMK2015WIN_PUTPEOPLE__

class CPutChara;

class CPutPeople
{
public:
	CPutPeople();
	~CPutPeople();
	void End(void);

	void CalcuAnime(void);

	void Put(int x,int y,int type,int pic,int houkou = 0);
	void PutItem(int x,int y,int type,int item,int houkou = 0);
	void PutLife(int x,int y,int type,int life,int lifeMax = 100);

private:
	CPutChara* m_people[2];
	int m_peopleAnime;
	int m_itemAnime;

};

#endif
/*_*/
