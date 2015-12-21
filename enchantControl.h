#if !defined __CMK2015WIN_ENCHANTCONTROL__
#define __CMK2015WIN_ENCHANTCONTROL__

class CPutCard;
class CCardList;

class CEnchantControl
{
public:
	CEnchantControl(CCardList* list,CPutCard* putCard);
	~CEnchantControl();
	void End(void);

	void Clear(void);
	void AddEnchant(int pl,int card);
	void RemoveEnchant(int pl,int nm = -1);

	int GetEnchantNumber(int pl);

	void Print(void);
	int GetOnEnchant(int pl,POINT pt);
	
	int GetAttack(int pl);
	int GetDeffense(int pl);

private:
	int m_enchantMax[2];
	int m_enchantNumber[2];
	int* m_enchant[2];

	CPutCard* m_putCard;
	CCardList* m_cardList;

	POINT m_enchantPrint[2];
	SIZE m_enchantNext[2];

	POINT GetEnchantPoint(int pl,int n);
	void CalcuEffect(void);

	int m_attack[2];
	int m_deffense[2];

};

#endif
/*_*/
