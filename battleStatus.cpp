#include <windows.h>

#include "cardList.h"
#include "battleStatus.h"

int CBattleStatus::m_serialCount = 0;

CBattleStatus::CBattleStatus()
{
	m_playerEnemy = -1;
	Clear();
}

CBattleStatus::~CBattleStatus()
{
	End();
}

void CBattleStatus::End(void)
{
}

void CBattleStatus::Clear(void)
{
	m_playerEnemy = -1;
	m_targetNumber = -1;
	m_targetItemNumber = -1;
	for (int i=0;i<16;i++)
	{
		m_haveItem[i] = 0;
	}

	m_attackCount = 0;
	m_targetType = 0;
	m_fromNumber = -1;
	m_fromSerial = -1;
	m_weaponSpeed = 5;
	m_highSpeed = 0;
}

void CBattleStatus::NewSerial(void)
{
	m_serial = m_serialCount;
	m_serialCount++;
}

void CBattleStatus::CalcuStatus(CCardList* list)
{
	m_attack = m_attackBase;
	m_deffense = m_deffenseBase;
	m_attackSpeed = m_attackSpeedBase;

	if (m_haveItem[0] > 0)
	{
		//weapon
		int card = m_haveItem[0];
		int attack = list->GetAttack(card);
		m_attack += attack;
	}
	if (m_haveItem[1] > 0)
	{
		//shield
		int card = m_haveItem[1];
		int deffense = list->GetDeffense(card);
		m_deffense += deffense;
	}
}


/*_*/



