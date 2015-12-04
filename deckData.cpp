#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nnnUtilLib\nameList.h"
#include "..\..\systemNNN\nnnUtilLib\mySaveFolder.h"
#include "..\..\systemNNN\nyanLib\INCLUDE\\myFile.h"


#include "deckData.h"


CDeckData::CDeckData(int n)
{
	m_deckNumber = n;
	m_listMax = 256;
	m_listNumber = 40;
	m_data = new int[m_listMax];
	
	ClearList();
}


CDeckData::~CDeckData()
{
	End();
}

void CDeckData::End(void)
{
	DELETEARRAY(m_data);
}

int CDeckData::GetUsedNumber(void)
{
	int n = 0;
	for (int i=0;i<m_listMax;i++)
	{
		if (i<m_listNumber)
		{
			if (m_data[i] > 0)
			{
				n++;
			}
		}
	}

	return n;
}

void CDeckData::ClearList(void)
{
	for (int i=0;i<m_listMax;i++)
	{
		m_data[i] = 0;
	}
}

void CDeckData::SetCard(int n,int card)
{
	if ((n>=0) && (n<m_listMax))
	{
		if (n<m_listNumber)
		{
			m_data[n] = card;
		}
	}
}

int CDeckData::GetCard(int n)
{
	if ((n>=0) && (n<m_listMax))
	{
		return m_data[n];
	}
	return 0;
}

BOOL CDeckData::Load(int n)
{
	if (n == -1) n = m_deckNumber;

	CNameList* list = new CNameList();
	char filenameonly[256];
	sprintf_s(filenameonly,256,"deck%d",n);
	char filename[1024];
	LPSTR folder = CMySaveFolder::GetFullFolder();
	sprintf_s(filename,1024,"%s\\%s",folder,filenameonly);
	if (CMyFile::CheckExistFile(folder,filenameonly,FALSE))
	{
		if (list->LoadFile(filename))
		{
			int dataNumber = list->GetNameKosuu();
			ClearList();
			if (dataNumber >= 4)
			{
				int param1 = atoi(list->GetName(0));
				int param2 = atoi(list->GetName(1));

				for (int i=0;i<dataNumber/2;i++)
				{
					int place = atoi(list->GetName(i*2+2));
					int card = atoi(list->GetName(i*2+1+2));
					if ((place >= 0) && (place < m_listMax))
					{
						m_data[place] = card;
					}
				}
			}
		}
		delete list;
		return TRUE;
	}

	delete list;
	return FALSE;
}

BOOL CDeckData::Save(int n)
{
	if (n == -1) n = m_deckNumber;

	char filename[1024];
	LPSTR folder = CMySaveFolder::GetFullFolder();
	sprintf_s(filename,1024,"%s\\deck%d.xtx",folder,n);
	FILE* file = CMyFile::OpenFullPath(filename,"wb");
	if (file != NULL)
	{
		char mes[256];
		sprintf_s(mes,256,"%d,%d\x00d\x00a",0,0);
		fwrite(mes,sizeof(char),strlen(mes),file);
		for (int i=0;i<m_listMax;i++)
		{
			int n = m_data[i];
			if (n>0)
			{
				sprintf_s(mes,256,"%d,%d\x00d\x00a",i,n);
				fwrite(mes,sizeof(char),strlen(mes),file);
			}
		}

		fclose(file);
		return TRUE;
	}

	return FALSE;

}


/*_*/



