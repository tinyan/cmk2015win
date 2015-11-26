#if !defined __CMK2011WIN__
#define __CMK2011WIN__


class CArea
{
public:
	CArea();
	~CArea();
	void End(void);

	void SetArea(int x,int y,int sizeX,int sizeY);
	void SetArea(POINT pt,SIZE sz);
	void SetArea(RECT rc);

	BOOL CheckInArea(int x,int y,int sizeX = 1,int sizeY = 1);
	BOOL CheckInArea(POINT pt,int sizeX = 1,int sizeY = 1);

	RECT GetRect(void);
	int CheckKabe(POINT pt,int tate);

private:
	int m_x,m_y,m_sizeX,m_sizeY;
};

#endif
/*_*/
