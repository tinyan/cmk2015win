#if !defined __CMK2015WIN_PRINTDAMAGEEFFECT__
#define __CMK2015WIN_PRINTDAMAGEEFFECT__


class CPutChara;

class CPrintDamageEffect
{
public:
	CPrintDamageEffect();
	~CPrintDamageEffect();
	void End(void);

	void Clear(void);
	void Calcu(void);
	void Print(void);

	void AddDamage(int x,int y,int type = 0);

	typedef struct _tagDAMAGEEFFECT
	{
		BOOL flag;
		int x,y;
		int count;
		int countMax;
		int type;
	} DAMAGEEFFECT;

	int m_workMax;
	int m_workNumber;
	DAMAGEEFFECT* m_work;

	int SearchAki(void);
private:
	CPutChara* m_damage;
};

#endif
/*_*/
