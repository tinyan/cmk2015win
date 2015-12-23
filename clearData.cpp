#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nnnUtilLib\nameList.h"
#include "..\..\systemNNN\nnnUtilLib\mySaveFolder.h"
#include "..\..\systemNNN\nyanLib\INCLUDE\\myFile.h"

#include "clearData.h"

CClearData::CClearData()
{
	m_stageMax = 16;
	m_subStageMax = 4;
	m_data = new int*[m_stageMax];
	for (int i=0;i<m_stageMax;i++)
	{
		m_data[i] = new int[m_subStageMax];
	}

	m_modifyFlag = FALSE;
	Clear();
	Load();
}

CClearData::~CClearData()
{
	End();
}

void CClearData::End(void)
{
	if (m_modifyFlag)
	{
		Save();
	}

	if (m_data != NULL)
	{
		for (int i=0;i<m_subStageMax;i++)
		{
			DELETEARRAY(m_data[i]);
		}
		DELETEARRAY(m_data);
	}
}

void CClearData::Clear(void)
{
	for (int j=0;j<m_stageMax;j++)
	{
		for (int i=0;i<m_subStageMax;i++)
		{
			m_data[j][i] = 0;
		}
	}
	m_modifyFlag = TRUE;
}

BOOL CClearData::CheckStage(int stage,int subStage)
{
	if ((stage>=0) && (stage<m_stageMax) && (subStage >=0) && (subStage<m_subStageMax))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CClearData::Load(void)
{
	CNameList* list = new CNameList();
	char filenameonly[256];
	sprintf_s(filenameonly,256,"clear.xtx");
	char filename[1024];
	LPSTR folder = CMySaveFolder::GetFullFolder();
	sprintf_s(filename,1024,"%s\\%s",folder,filenameonly);
	if (list->LoadFile(filename,FALSE,TRUE))
	{
		Clear();

		int dataNumber = list->GetNameKosuu();

		if (dataNumber >= 6)
		{
			int param1 = atoi(list->GetName(0));
			int param2 = atoi(list->GetName(1));
			int param3 = atoi(list->GetName(2));

			for (int i=1;i<dataNumber/3;i++)
			{
				int stage = atoi(list->GetName(i*3+0));
				int subStage = atoi(list->GetName(i*3+1));
				int data = atoi(list->GetName(i*3+2));
				if (CheckStage(stage,subStage))
				{
					m_data[stage][subStage] = data;
				}
			}
		}
		delete list;
		m_modifyFlag = FALSE;
		return TRUE;
	}

	delete list;
	return FALSE;


}

BOOL CClearData::Save(void)
{
	char filename[1024];
	LPSTR folder = CMySaveFolder::GetFullFolder();
	sprintf_s(filename,1024,"%s\\clear.xtx",folder);
	FILE* file = CMyFile::OpenFullPath(filename,"wb");
	if (file != NULL)
	{
		char mes[256];
		sprintf_s(mes,256,"%d,%d,%d\x00d\x00a",0,0,0);
		fwrite(mes,sizeof(char),strlen(mes),file);
		for (int j=0;j<m_stageMax;j++)
		{
			for (int i=0;i<m_subStageMax;i++)
			{
				int d = m_data[j][i];
				if (d>0)
				{
					sprintf_s(mes,256,"%d,%d,%d\x00d\x00a",j,i,d);
					fwrite(mes,sizeof(char),strlen(mes),file);
				}
			}
		}

		fclose(file);
		m_modifyFlag = FALSE;
		return TRUE;
	}

	return FALSE;

}

int CClearData::GetData(int stage,int subStage)
{
	if (CheckStage(stage,subStage))
	{
		return m_data[stage][subStage];
	}
	return 0;
}

void CClearData::SetData(int stage,int subStage,int data)
{
	if (CheckStage(stage,subStage))
	{
		if (data != m_data[stage][subStage])
		{
			m_data[stage][subStage] = data;
			m_modifyFlag = TRUE;
		}
	}
}

void CClearData::AddData(int stage,int subStage,int data)
{
	if (CheckStage(stage,subStage))
	{
		data += m_data[stage][subStage];
		SetData(stage,subStage,data);
	}
}

/*_*/



