#if !defined __CMK2015WIN_PUTCHARA__
#define __CMK2015WIN_PUTCHARA__

class CPicture;

class CPutChara
{
public:
	CPutChara(LPSTR filename,int x,int y);
	virtual ~CPutChara();
	void End(void);

	void Put(int x,int y,int n);
	void Put(int x,int y,int nx,int ny);

	void TransPut(int x,int y,int n,int ps);
	void TransPut(int x,int y,int nx,int ny,int ps);

protected:
	CPicture* m_pic;
	int m_blockX;
	int m_blockY;
	SIZE m_picSize;
	int m_sizeX;
	int m_sizeY;

private:

};

#endif
/*_*/
