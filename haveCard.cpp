#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nnnUtilLib\nameList.h"
#include "..\..\systemNNN\nnnUtilLib\mySaveFolder.h"
#include "..\..\systemNNN\nyanLib\INCLUDE\\myFile.h"


#include "haveCard.h"


CHaveCard::CHaveCard()
{
	m_listMax = 256;
	m_data = new int[m_listMax];
	ClearList();
}


CHaveCard::~CHaveCard()
{
	End();
}

void CHaveCard::End(void)
{
}

void CHaveCard::ClearList(void)
{
	for (int i=0;i<m_listMax;i++)
	{
		m_data[i] = 0;
	}
}

void CHaveCard::SetCard(int card,int n)
{
	if ((card >=0) && (card <m_listMax))
	{
		m_data[card] = n;
	}
}

int CHaveCard::GetCard(int card)
{
	if ((card >=0) && (card <m_listMax))
	{
		return m_data[card];
	}

	return 0;
}


BOOL CHaveCard::Load(void)
{
	CNameList* list = new CNameList();
	LPCSTR filenameonly = "havecard.xtx";
	char filename[256];
	LPSTR folder = CMySaveFolder::GetFullFolder();
	sprintf_s(filename,256,"%s\\%s",folder,filenameonly);
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
					int card = atoi(list->GetName(i*2+2));
					int n = atoi(list->GetName(i*2+1+2));
					if ((card >= 0) && (card < m_listMax))
					{
						m_data[card] = n;
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

BOOL CHaveCard::Save(void)
{
	char filename[256];
	LPSTR folder = CMySaveFolder::GetFullFolder();
	sprintf_s(filename,256,"%s\\havecard.xtx",folder);
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



