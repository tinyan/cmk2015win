#if !defined __CMK2015WIN_CARDLIST__
#define __CMK2015WIN_CARDLIST__


class CNameList;

class CCardList
{
public:
	CCardList();
	~CCardList();
	void End(void);

	LPSTR GetName(int card);
	int GetNeedMana(int card,int manaType);
	int GetType(int card);
	int GetMiniCardNumber(int card);
	LPSTR GetFilename(int card);
	LPSTR GetText(int card,int n);
	LPSTR GetPlainText(int card,int n);
	int GetLandPower(int card,int manaType);

	int GetEquipType(int card);
	int GetEquipPic(int card);
	int GetItemPic(int card);

	int GetHP(int card);
	int GetAttack(int card);
	int GetDeffense(int card);
	int GetRange(int card);
	int GetAttackSpeed(int card);
	int GetOccupy(int card);
	int GetWeaponSpeed(int card);
	int GetMoveSpeed(int card);
	int GetNumbers(int card);
	int GetRare(int card);
	LPSTR GetEtcMes(int card);

	int GetWorldType(int card);
	int GetEnchantType(int card);
	int GetSpellType(int card);
	int GetItemType(int card);
	int GetHighSpeed(int card);

	int GetSound(int card);

	static LPSTR m_errorName;
private:
	int m_cardNumberMax;
	static int m_dataTypeTable[];
	static char m_searchTable[][16][64];

	CNameList* m_list;
	int m_paramNumber;
	int m_listMax;
	int* m_numberToWork;
	int* m_data;
	int m_dataMax;
	BOOL CheckCardNumber(int card);

	int SearchName(int type,LPSTR name);
	int CardToNumber(int card);

	int GetParamData(int card,int param);
	char m_etcMes[256];
};

#endif
/*_*/
