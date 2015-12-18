#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "..\..\systemNNN\nnnUtilLib\systempicture.h"

#include "putChara.h"
#include "printDamageEffect.h"



CPrintDamageEffect::CPrintDamageEffect()
{
	m_workMax = 256;
	m_work = new DAMAGEEFFECT[m_workMax];
	Clear();
	m_damage = new CPutChara("sys\\ta_damageeffect",4,2);
}

CPrintDamageEffect::~CPrintDamageEffect()
{
	End();
}

void CPrintDamageEffect::End(void)
{
	ENDDELETECLASS(m_damage);
	DELETEARRAY(m_work);
}

void CPrintDamageEffect::Clear(void)
{
	m_workNumber = 0;
	for (int i=0;i<m_workMax;i++)
	{
		m_work[i].flag = FALSE;
	}
}

void CPrintDamageEffect::Calcu(void)
{
	for (int i=0;i<m_workNumber;i++)
	{
		if (m_work[i].flag)
		{
			m_work[i].count++;
			if (m_work[i].count > m_work[i].countMax)
			{
				m_work[i].flag = FALSE;
			}
			else
			{

			}
		}
	}


	//cut last
	if (m_workNumber > 0)
	{
		if (!(m_work[m_workNumber-1].flag))
		{
			m_workNumber--;
		}
	}
}

void CPrintDamageEffect::Print(void)
{
	for (int i=0;i<m_workNumber;i++)
	{
		if (m_work[i].flag)
		{
			int x = m_work[i].x;
			int y = m_work[i].y;
			int anime = m_work[i].count % 4;
			int type = m_work[i].type;
			m_damage->Put(x,y,anime,type);
		}
	}
}

void CPrintDamageEffect::AddDamage(int x,int y,int type)
{
	int n = SearchAki();
	if (n != -1)
	{
		m_work[n].flag = TRUE;
		m_work[n].x = x;
		m_work[n].y = y;
		m_work[n].count = 0;
		m_work[n].countMax = 13;
		m_work[n].type = type;
	}
	
	if (n>=m_workNumber)
	{
		m_workNumber = n+1;
	}

}

int CPrintDamageEffect::SearchAki(void)
{
	for (int i=0;i<m_workMax;i++)
	{
		if (!m_work[i].flag) return i;

	}
	return -1;
}

/*_*/



