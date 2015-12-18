#if !defined __CMK2015WIN_ATTACKOBJECT__
#define __CMK2015WIN_ATTACKOBJECT__


class CAttackObject
{
public:
	CAttackObject();
	~CAttackObject();
	void End(void);

	void Clear(void);
	void SetFrom(float x,float y,int attack,int count,int type = 0);
	void SetTarget(int pl,int n,int serial);
	BOOL m_flag;
	int m_attack;
	int m_type;	
	int m_targetPlayer;
	int m_targetNumber;
	int m_targetSerial;

	BOOL Calcu(void);
	POINT GetPoint(float toX,float toY);




private:
	float m_fromX,m_fromY;

	int m_count;
	int m_countMax;
};

#endif
/*_*/
