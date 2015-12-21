#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanLib\include\commonMacro.h"
#include "..\..\systemNNN\nnnUtilLib\nameList.h"


#include "stageData.h"

CStageData::CStageData(int n)
{
	m_stage = n;

	char filename[256];
	sprintf_s(filename,"stage\\stage%d.xtx",m_stage);
	m_list = new CNameList();
	m_list->LoadFile(filename);

	int p = 0;
	m_startArea = GetRectData(p);
	p += 6;

	m_targetNumber = GetNumber(p);
	p++;
	m_targetRect = new RECT[m_targetNumber+1];
	m_targetType = new int[m_targetNumber+1];
	for (int i=0;i<m_targetNumber;i++)
	{
		m_targetRect[i] = GetRectData(p);
		p += 4;
		m_targetType[i] = GetNumber(p);
		p += 2;
	}


	m_blockNumber = GetNumber(p);
	p++;
	m_blockRect = new RECT[m_blockNumber+1];
	for (int i=0;i<m_blockNumber;i++)
	{
		m_blockRect[i] = GetRectData(p);
		p += 6;
	}

	m_mirrorNumber = GetNumber(p);
	p++;
	m_mirrorRect = new RECT[m_mirrorNumber+1];
	m_mirrorType = new int[m_mirrorNumber+1];
	for (int i=0;i<m_mirrorNumber;i++)
	{
		m_mirrorRect[i] = GetRectData(p);
		p += 4;
		m_mirrorType[i] = GetNumber(p);
		p += 2;
	}

	m_hintNumber = GetNumber(p);
	p++;
	m_hintRect = new RECT[m_hintNumber+1];
	m_hintMessage = new LPSTR[m_hintNumber+1];
	m_hintColor = new int[m_hintNumber+1];

	for (int i=0;i<m_hintNumber;i++)
	{
		m_hintRect[i] = GetRectData(p);
		p += 4;
		m_hintMessage[i] = m_list->GetName(p);
		p += 1;
		m_hintColor[i] = GetNumber(p);
		p += 1;
	}
}



CStageData::~CStageData()
{
	End();
}

void CStageData::End(void)
{
	DELETEARRAY(m_targetRect);
	DELETEARRAY(m_targetType);

	DELETEARRAY(m_blockRect);

	DELETEARRAY(m_mirrorRect);
	DELETEARRAY(m_mirrorType);

	DELETEARRAY(m_hintRect);
	DELETEARRAY(m_hintMessage);
	DELETEARRAY(m_hintColor);

	ENDDELETECLASS(m_list);
}


RECT CStageData::GetRectData(int n)
{
	RECT rc;
	rc.left = atoi(m_list->GetName(n));
	rc.top = atoi(m_list->GetName(n+1));
	rc.right = atoi(m_list->GetName(n+2));
	rc.bottom = atoi(m_list->GetName(n+3));

	return rc;
}

int CStageData::GetNumber(int n)
{
	return atoi(m_list->GetName(n));
}


int CStageData::GetFontSize(int n)
{
	int fontSize = m_hintRect[n].right;
	if (fontSize == 0) fontSize = 16;

	return fontSize;
}


/*_*/

