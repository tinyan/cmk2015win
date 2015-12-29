#if !defined __CMK2015WIN_SOUNDCONTROL__
#define __CMK2015WIN_SOUNDCONTROL__

class CWaveData;
class CSoundControl 
{
public:
	CSoundControl();
	~CSoundControl();
	void End(void);

	void Clear(void);
	void AddSound(int type);
	int GetSound(int type);

private:
	int m_sound[64];

};

#endif
/*_*/
