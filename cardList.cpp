#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nnnUtilLib\nameList.h"


#include "cardList.h"

LPSTR CCardList::m_errorName = "ƒGƒ‰[";

#define PARAM_MANA0 1
#define PARAM_CARDNAME 7
#define PARAM_CARDTYPE 8

//‹¤’Ê
//people
#define PARAM_HP 10
#define PARAM_ATTACK 11
#define PARAM_DEFFENSE 12
#define PARAM_RANGE 13
#define PARAM_ATTACKSPEED 14
#define PARAM_OCCUPY 15
#define PARAM_WEAPONSPEED 16
#define PARAM_MOVESPEED 17
#define PARAM_HIGHSPEED 18
#define PARAM_CARDSOUND 19
#define PARAM_NUMBERS 20

//land
#define PARAM_LANDPOWER0 9
//equip
#define PARAM_EQUIPTYPE 9

//item
#define PARAM_ITEMTYPE 9

//spell
#define PARAM_SPELLTYPE 9

//world
#define PARAM_WORLDTYPE 9
//1:attack

//enchant
#define PARAM_ENCHANTTYPE 9
//0:attack 1:deffense 

#define PARAM_RARE 21
#define PARAM_EQUIPPIC 22
#define PARAM_ITEMPIC 23

#define PARAM_CARDTEXT 24
#define PARAM_CARDPLANETEXT 28
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

	m_etcMes[0] = 0;

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

LPSTR CCardList::GetPlainText(int card,int k)
{
	int n = CardToNumber(card);
	return m_list->GetName(n * m_paramNumber + PARAM_CARDPLANETEXT + k);
}

int CCardList::GetNeedMana(int card,int manaType)
{
	int n = CardToNumber(card);
	return m_data[n*m_paramNumber + PARAM_MANA0 + manaType];
}

int CCardList::GetLandPower(int card,int manaType)
{
	int n = CardToNumber(card);
	return m_data[n*m_paramNumber + PARAM_LANDPOWER0 + manaType];
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

int CCardList::GetEquipType(int card)
{
	if (card == 0) return 0;
	int n = CardToNumber(card);
	return m_data[n*m_paramNumber + PARAM_EQUIPTYPE];
}

int CCardList::GetEquipPic(int card)
{
	if (card == 0) return 0;
	int n = CardToNumber(card);
	return m_data[n*m_paramNumber + PARAM_EQUIPPIC];
}

int CCardList::GetItemPic(int card)
{
	if (card == 0) return 0;
	int n = CardToNumber(card);
	return m_data[n*m_paramNumber + PARAM_ITEMPIC];
}

int CCardList::GetHP(int card)
{
	return GetParamData(card,PARAM_HP);
}

int CCardList::GetAttack(int card)
{
	return GetParamData(card,PARAM_ATTACK);
}

int CCardList::GetDeffense(int card)
{
	return GetParamData(card,PARAM_DEFFENSE);
}

int CCardList::GetRange(int card)
{
	return GetParamData(card,PARAM_RANGE);
}

int CCardList::GetAttackSpeed(int card)
{
	return GetParamData(card,PARAM_ATTACKSPEED);
}

int CCardList::GetOccupy(int card)
{
	return GetParamData(card,PARAM_OCCUPY);
}

int CCardList::GetWeaponSpeed(int card)
{
	return GetParamData(card,PARAM_WEAPONSPEED);
}

int CCardList::GetMoveSpeed(int card)
{
	return GetParamData(card,PARAM_MOVESPEED);
}

int CCardList::GetHighSpeed(int card)
{
	return GetParamData(card,PARAM_HIGHSPEED);
}

int CCardList::GetRare(int card)
{
	return GetParamData(card,PARAM_RARE);
}

int CCardList::GetNumbers(int card)
{
	return GetParamData(card,PARAM_NUMBERS);
}

int CCardList::GetWorldType(int card)
{
	return GetParamData(card,PARAM_WORLDTYPE);
}

int CCardList::GetEnchantType(int card)
{
	return GetParamData(card,PARAM_ENCHANTTYPE);
}

int CCardList::GetSpellType(int card)
{
	return GetParamData(card,PARAM_SPELLTYPE);
}

int CCardList::GetItemType(int card)
{
	return GetParamData(card,PARAM_ITEMTYPE);
}

int CCardList::GetSound(int card)
{
	return GetParamData(card,PARAM_CARDSOUND);
}

LPSTR CCardList::GetEtcMes(int card)
{
	int type = GetType(card);
	if (type == 1)
	{
		int getMana = 0;
		for (int i=0;i<8;i++)
		{
			getMana += GetLandPower(card,i);
		}
		sprintf_s(m_etcMes,256,"%d",getMana);
		return m_etcMes;
	}
	else if (type == 2)
	{
		int attack = GetAttack(card);
		int deffense = GetDeffense(card);
		int hp = GetHP(card);
		sprintf_s(m_etcMes,256,"%d/%d/%d",attack,deffense,hp);
		return m_etcMes;
	}
	else if (type == 3)
	{
		//equip
		int equipType = GetEquipType(card);
		int param = 0;
		if (equipType == 0)
		{
			param = GetAttack(card);
		}
		else if (equipType == 1)
		{
			param = GetDeffense(card);
		}
		
		if (param != 0)
		{
			if (param < 0) param *= -1;
			sprintf_s(m_etcMes,256,"%d",param);
			return m_etcMes;
		}
	}
	else if (type == 4)
	{
		int itemType = GetItemType(card);
		if (itemType == 0)
		{
			int param = GetHP(card);
			sprintf_s(m_etcMes,256,"%d",param);
			return m_etcMes;
		}
	}
	else if (type == 5)
	{
		int spellType = GetSpellType(card);
		if (spellType == 0)
		{
			int param = GetAttack(card);
			sprintf_s(m_etcMes,256,"%d",param);
			return m_etcMes;
		}
	}
	else if (type == 6)
	{
		int enchantType = GetEnchantType(card);
		int param = 0;
		if ((enchantType == 1) || (enchantType == -1))
		{
			param = GetAttack(card);
		}
		else if ((enchantType == 2) || (enchantType == -2))
		{
			param = GetDeffense(card);
		}

		if (param != 0)
		{
			if (param < 0) param *= -1;
			sprintf_s(m_etcMes,256,"%d",param);
			return m_etcMes;
		}

	}
	else if (type == 7)
	{
		int worldType = GetWorldType(card);
		int param = 0;
		if (worldType == 1)
		{
			param = GetAttack(card);
		}
		else if (worldType == 2)
		{
			param = GetDeffense(card);
		}
		else if (worldType == 3)
		{
			param = GetAttack(card);
		}
		else if (worldType == 4)
		{
			param = GetMoveSpeed(card);
		}
		else if (worldType == 5)
		{
			param = GetNumbers(card);
		}
		if (param != 0)
		{
			if (param < 0) param *= -1;
			if (worldType == 4)
			{
				sprintf_s(m_etcMes,256,"%d%%",param);
			}
			else
			{
				sprintf_s(m_etcMes,256,"%d",param);
			}
			return m_etcMes;
		}

	}

	return NULL;
}


int CCardList::GetParamData(int card,int param)
{
	if (card == 0) return 0;
	int n = CardToNumber(card);
	return m_data[n*m_paramNumber + param];
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



