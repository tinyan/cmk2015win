#include <windows.h>

#include "itemStatus.h"

int CItemStatus::m_serialCount = 0;

CItemStatus::CItemStatus()
{
	m_playerEnemy = -1;
	Clear();
}

CItemStatus::~CItemStatus()
{
	End();
}

void CItemStatus::End(void)
{
}

void CItemStatus::Clear(void)
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
}

void CItemStatus::NewSerial(void)
{
	m_serial = m_serialCount;
	m_serialCount++;
}

void CItemStatus::CalcuStatus(void)
{
	m_attack = m_attackBase;
	m_deffense = m_deffenseBase;
	m_attackSpeed = m_attackSpeedBase;

	if (m_haveItem[0] > 0)
	{
		//weapon
	}
	if (m_haveItem[1] > 0)
	{
		//shield
	}
}


/*_*/



