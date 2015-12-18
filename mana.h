#if !defined __CMK2015WIN_MANA__
#define __CMK2015WIN_MANA__


class CMana
{
public:
	CMana();
	~CMana();
	void End(void);

	void SetManaMax(int n,int mx);
	void SetMana(int n,int mana);
	void Clear(void);
	int GetMana(int n);
	BOOL UseMana(int n,int mana);
	void AddLandPower(int n,int pw);
	void AddMana(int n,int mana);

	void AddManaPower(int pw);
	void AddAllMana(int add = 1);
	void AllHeal(int d = -1);

	void SetPoint(POINT pt);
	void Print(void);
private:
	int m_manaMax[16];
	int m_mana[16];

	int m_manaPower;
	POINT m_point;

};

#endif
/*_*/
