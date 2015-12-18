#if !defined __CMK2015WIN_ATTACKOBJECTCONTROL__
#define __CMK2015WIN_ATTACKOBJECTCONTROL__


class CAttackObject;

class CAttackObjectControl
{
public:
	CAttackObjectControl();
	~CAttackObjectControl();
	void End(void);
	void Clear(void);

	int m_attackObjectNumber;

	void CutLast(void);

	CAttackObject* SearchAki(void);
	CAttackObject* GetAttackObject(int n);

private:
	int m_attackObjectMax;
	CAttackObject** m_attackObject;

	

};

#endif
/*_*/
