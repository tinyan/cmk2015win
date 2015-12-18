#if !defined __CMK2015WIN_ITEMSTATUS__
#define __CMK2015WIN_ITEMSTATUS__


class CItemStatus
{
public:
	CItemStatus();
	~CItemStatus();
	void End(void);

	int m_serial;

	int m_playerEnemy;

	int m_targetSerial;
	int m_targetType;
	int m_targetNumber;
	int m_targetItemSerial;
	int m_targetItemNumber;
	int m_fromNumber;
	int m_fromSerial;

	int m_attackBase;
	int m_deffenseBase;
	int m_hpMax;
	int m_attackSpeed;
	int m_attackSpeedBase;
	int m_attackCount;
	int m_occupyPower;
	int m_weaponSpeed;

	int m_attack;
	int m_deffense;
	int m_hp;

	int m_haveItem[16];
	float m_x,m_y;
	float m_targetX,m_targetY;
	float m_speed;
	float m_range;

	int m_itemType;
	int m_card;

	void Clear(void);
	void NewSerial(void);
	void CalcuStatus(void);

	static int m_serialCount;

private:

};

#endif
/*_*/
