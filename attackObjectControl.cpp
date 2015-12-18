#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "..\..\systemNNN\nnnUtilLib\systempicture.h"


#include "attackObject.h"
#include "attackObjectControl.h"


CAttackObjectControl::CAttackObjectControl()
{
	m_attackObjectMax = 256;
	m_attackObject = new CAttackObject*[m_attackObjectMax];
	for (int i=0;i<m_attackObjectMax;i++)
	{
		m_attackObject[i] = new CAttackObject();
	}
	Clear();
}

CAttackObjectControl::~CAttackObjectControl()
{
	End();
}

void CAttackObjectControl::End(void)
{
	if (m_attackObject != NULL)
	{
		for (int i=0;i<m_attackObjectMax;i++)
		{
			ENDDELETECLASS(m_attackObject[i]);
		}
		DELETEARRAY(m_attackObject);
	}
}


void CAttackObjectControl::Clear(void)
{
	
	m_attackObjectNumber = 0;
}

void CAttackObjectControl::CutLast(void)
{
	if (m_attackObjectNumber > 0)
	{
		if (!(m_attackObject[m_attackObjectNumber-1]->m_flag))
		{
			m_attackObjectNumber--;
		}
	}
}


CAttackObject* CAttackObjectControl::SearchAki(void)
{
	for (int i=0;i<m_attackObjectMax;i++)
	{
		if (!m_attackObject[i]->m_flag)
		{
			CAttackObject* obj = m_attackObject[i];
			obj->Clear();
			obj->m_flag = TRUE;
			if (i >= m_attackObjectNumber) m_attackObjectNumber = i + 1;
			return obj;
		}
	}

	return NULL;
}

CAttackObject* CAttackObjectControl::GetAttackObject(int n)
{
	if ((n>=0) && (n<m_attackObjectMax))
	{
		return m_attackObject[n];
	}
	return NULL;
}



/*_*/



