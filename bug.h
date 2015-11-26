#if !defined __CMK2011WIN_BUG__
#define __CMK2011WIN_BUG__


class CBug
{
public:
	CBug();
	~CBug();
	void End(void);

	void Clear(void);

	BOOL AddPoint(float x, float y);
	BOOL AddPoint(POINT pt);
	int GetPointNumber(void){return m_pointNumber;}
	int GetPointPointer(void){return m_pointPointer;}
	float GetTotalLength(void){return m_lengthTotal;}

	float GetUsedLength(void){return m_usedLength;}

	int GetRealPointNumber(void){return m_realPointNumber;}
	int GetRealPointPointer(void){return m_realPointPointer;}
	float GetRealAngle(void){return m_realAngle;}

	void SetRealAngle(float angle){m_realAngle = angle;}

	BOOL Start(int life = -1);
	BOOL CalcuNext(BOOL limitFlag = FALSE);
	float GetCalcuedX(void){return m_calcuedX;}
	float GetCalcuedY(void){return m_calcuedY;}
	float GetCalcuedAngle(void){return m_calcuedAngle;}
	void Calcu(int count = 10);

	void AllCopy(CBug* from);


	float* GetPoint(void){return m_point;}
	float* GetAngle(void){return m_angle;}
	float* GetLength(void){return m_length;}
	float* GetRealPoint(void){return m_realPoint;}
	int* GetRealPointInt(void){return m_realPointInt;}
	
	POINT GetTailPoint(void);

	int GetPrintPointLength(void);
	POINT GetPrintPoint(int k);

	float GetNowLength(void);
	float GetNowAngle(void);
	float GetNowDeltaAngle(void);

	float AdjustAngle(float angle);

	int GetRealTailPointer(void);

	BOOL GetStartFlag(void){return m_startFlag;}
	BOOL GetDeathFlag(void){return m_deathFlag;}
	BOOL GetFlag(void){return m_flag;}
	int GetLife(void){return m_life;}

	POINT GetHeadPoint(void);
	void SetDeath(void);
	void Reflect(int tate);
	void Turn(int angle);

	void SetRealPrintLength(int ln){m_realPointPrintLength = ln;}
private:
	int m_pointMax;
	float* m_point;
	float* m_angle;
	float* m_length;
	float* m_realPoint;
	int* m_realPointInt;

	float m_lengthTotal;
	int m_pointNumber;
	int m_pointPointer;
	float m_usedLength;

	int m_realPointMax;
	int m_realPointPointer;
	int m_realPointNumber;

	int m_realPointPrintLength;

	float m_realAngle;

	float m_calcuedX;
	float m_calcuedY;
	float m_calcuedAngle;

	BOOL m_startFlag;
	BOOL m_deathFlag;
	BOOL m_flag;
	int m_life;
};

#endif
/*_*/
