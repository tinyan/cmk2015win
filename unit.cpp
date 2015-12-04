#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"

#include "battleStatus.h"

#include "unit.h"


int CUnit::m_serialWork = 0;


CUnit::CUnit()
{
	m_battleStatus = new CBattleStatus();
	NewSerial();

}

CUnit::~CUnit()
{
	End();
}

void CUnit::End(void)
{
	ENDDELETECLASS(m_battleStatus);
}


void CUnit::NewSerial(void)
{
	m_serial = m_serialWork;
	m_serialWork++;
}


/*_*/



