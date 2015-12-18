#if !defined __CMK2015WIN_PUTEQUIP__
#define __CMK2015WIN_PUTEQUIP__


class CPutChara;

class CPutEquip
{
public:
	CPutEquip();
	~CPutEquip();
	void End(void);

	void Put(int x,int y,int pl,int pic,int type,int houkou);
	static POINT m_delta[2][4];
private:
	CPutChara* m_equipPic;

};

#endif
/*_*/
