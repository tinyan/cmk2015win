#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nnnUtilLib\nameList.h"


#include "cardList.h"

LPSTR CCardList::m_errorName = "ƒGƒ‰[";

#define PARAM_MANA0 1
#define PARAM_CARDNAME 7
#define PARAM_CARDTYPE 8

#define PARAM_CARDTEXT 24
#define PARAM_MINICARDNUMBER 30
#define PARAM_CARDFILENAME 31

char CCardList::m_searchTable[][16][64]=
{
	{
		"",
	},
	{
		"dummy","land","people","equip","item","spell","enchant","world",""
	},

};



int CCardList::m_dataTypeTable[]=
{
	0,
	0,0,0,0,0,0,
	0,
	1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
};

CCardList::CCardList()
{
	m_cardNumberMax = 1024;

	m_list = new CNameList();
	m_paramNumber = 32;
	m_list->LoadFile("nya\\cardlist.xtx");

	m_numberToWork = new int[m_cardNumberMax];
	for (int i=0;i<m_cardNumberMax;i++)
	{
		m_numberToWork[i] = -1;
	}

	m_dataMax = m_list->GetNameKosuu() / m_paramNumber;
	m_data = new int[m_dataMax * m_paramNumber];

	for (int i=1;i<m_dataMax;i++)
	{
		int card = atoi(m_list->GetName(i*m_paramNumber+0));
		if ((card > 0) && (card <m_cardNumberMax))
		{
			m_numberToWork[card] = i;
			for (int k=0;k<m_paramNumber;k++)
			{
				int d = 0;
				int dataType = m_dataTypeTable[k];
				if (dataType == 0)
				{
					d = atoi(m_list->GetName(i*m_paramNumber+k));
				}
				else
				{
					d = SearchName(dataType,m_list->GetName(i*m_paramNumber+k));
				}

				m_data[i*m_paramNumber+k] = d;

			}
		}
	}


	//number
	//mana0,mana1,mana2,mana3,mana4,mana5
	//cardname
	//cardType
	//pad[21]
	//minicardnumber
	//filename

}

CCardList::~CCardList()
{
	End();
}

void CCardList::End(void)
{
	DELETEARRAY(m_data);
	DELETEARRAY(m_numberToWork);
	ENDDELETECLASS(m_list);
}

int CCardList::CardToNumber(int card)
{
	int n = 0;

	if (CheckCardNumber(card))
	{
		n = m_numberToWork[card];
	}

	//debugtest
	if (n == 0) n = 1;

	return n;
}

LPSTR CCardList::GetName(int card)
{
	int n = CardToNumber(card);
	return m_list->GetName(n * m_paramNumber + PARAM_CARDNAME);
}

LPSTR CCardList::GetFilename(int card)
{
	int n = CardToNumber(card);
	return m_list->GetName(n * m_paramNumber + PARAM_CARDFILENAME);
}

LPSTR CCardList::GetText(int card,int k)
{
	int n = CardToNumber(card);
	return m_list->GetName(n * m_paramNumber + PARAM_CARDTEXT + k);
}

int CCardList::GetNeedMana(int card,int manaType)
{
	int n = CardToNumber(card);
	return m_data[n*m_paramNumber + PARAM_MANA0 + manaType];
}

int CCardList::GetType(int card)
{
	int n = CardToNumber(card);
	return m_data[n*m_paramNumber + PARAM_CARDTYPE];
}

int CCardList::GetMiniCardNumber(int card)
{
	if (card == 0) return 0;
	int n = CardToNumber(card);
	return m_data[n*m_paramNumber + PARAM_MINICARDNUMBER];
}

BOOL CCardList::CheckCardNumber(int card)
{
	if ((card > 0) && (card < m_cardNumberMax))
	{
		if (m_numberToWork[card] > 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

int CCardList::SearchName(int type,LPSTR name)
{
	int found = 0;
	for (int n=1;n<16;n++)
	{
		if (m_searchTable[type][n][0] == 0) break;
		if (_stricmp(m_searchTable[type][n],name) == 0)
		{
			found = n;
			break;
		}
	}

	return found;
}

/*_*/



