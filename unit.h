#if !defined __CMK2015WIN_UNIT__
#define __CMK2015WIN_UNIT__

class CBattleStatus;

class CUnit
{
public:
	CUnit();
	~CUnit();
	void End(void);

	static int m_serialWork;

	void NewSerial(void);

private:
	int m_type;
	int m_card;
	int m_job;
	int m_serial;

	CBattleStatus* m_battleStatus;

	float m_x;
	float m_y;
	int m_targetType;
	int m_targetNumber;
	int m_targetSerial;
	float m_targetX;
	float m_targetY;

	float m_speed;


};



#endif
/*_*/
