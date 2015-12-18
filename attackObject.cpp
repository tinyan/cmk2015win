#include <windows.h>

#include "attackObject.h"


CAttackObject::CAttackObject()
{
	Clear();
}

CAttackObject::~CAttackObject()
{
	End();
}

void CAttackObject::End(void)
{
}

void CAttackObject::SetFrom(float x,float y,int attack,int count,int type)
{
	m_fromX = x;
	m_fromY = y;
	m_attack = attack;
	m_count = 0;
	m_countMax = count;
	m_type = type;
	m_flag = TRUE;
}

void CAttackObject::SetTarget(int pl,int n,int serial)
{
	m_targetPlayer = pl;
	m_targetNumber = n;
	m_targetSerial = serial;
}

void CAttackObject::Clear(void)
{
	SetFrom(0,0,0,1);
	SetTarget(-1,-1,-1);
	m_flag = FALSE;
}

BOOL CAttackObject::Calcu(void)
{
	m_count++;
	if (m_count == m_countMax) return TRUE;
	if (m_count > m_countMax) m_flag = FALSE;
	return FALSE;
}

POINT CAttackObject::GetPoint(float toX,float toY)
{
	int count = m_count;
	if (count > m_countMax) count = m_countMax;
	int dv = m_countMax;
	if (dv<1) dv = 1;
	float x = toX - m_fromX;
	float y = toY - m_fromY;
	float ml = (float)count;

	x *= ml;
	y *= ml;
	x /= (float)dv;
	y /= (float)dv;
	x += m_fromX;
	y += m_fromY;

	POINT pt;
	pt.x = (int)x;
	pt.y = (int)y;

	return pt;
}


/*_*/



