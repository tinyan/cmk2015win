#if !defined __CMK2011WIN__HEXAREA__
#define __CMK2011WIN__HEXAREA__


class CPutChara;

class CHexArea
{
public:
	CHexArea();
	~CHexArea();
	void End(void);

	POINT GetAreaBlock(float x,float y);
	int GetType(int x,int y);
	void SetType(int x,int y,int type);
	int GetPower(int x,int y);
	void SetPower(int x,int y,int pw);

	void PutHex(int x,int y);
	void PutHex(int nx,int ny,int d);
	void PutHex(int nx,int ny,int type,int playerenemy);
	POINT GetHexPoint(int nx,int ny);
	void Occupy(POINT pt,int playerenemy,int pw);
	int GetLandPower(int playerenemy);
	void AddRandomHex(int type);
	static int m_houkouTable[6*2];

	BOOL CheckInArea(int x,int y);
private:
	CPutChara* m_hexPic;
	SIZE m_size;
	POINT m_point;
	int m_powerMax;
	int m_power[64][32];
	int m_type[64][32];
};

#endif
/*_*/
