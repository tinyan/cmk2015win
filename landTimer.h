#if !defined __CMK2015WIN_LANDTIMER__
#define __CMK2015WIN_LANDTIMER__


class CPicture;

class CLandTimer
{
public:
	CLandTimer();
	~CLandTimer();
	void End(void);

	void SetTimerMax(int mx);
	void SetTimer(int tm);
	BOOL AddTimer(int add = 1);
	void SetPoint(POINT pt);

	void Print(int tm = -1);
	void Print(POINT pt,int tm = -1);
private:
	int m_timerMax;
	int m_timer;
	int m_anime;

	POINT m_point;
	SIZE m_size;

	CPicture* m_onPic;
	CPicture* m_offPic;

};

#endif
/*_*/
