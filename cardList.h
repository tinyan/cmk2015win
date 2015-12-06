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
};

#endif
/*_*/
