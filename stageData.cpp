#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nnnUtilLib\nameList.h"



#include "stageData.h"

#define PARAM_ENEMYDECK 2
#define PARAM_WORLD 3
#define PARAM_ENCHANT 4

#define PARAM_GACHA_COMMON 16
#define PARAM_GACHA_RARE 22
#define PARAM_GACHA_SUPERRARE 24

#define PARAM_ADDHEX 8

CStageData::CStageData()
{
	m_stageNumberMax = 16;
	m_stageSubNumberMax = 4;

	m_list = new CNameList();
	m_paramNumber = 32;
	m_list->LoadFile("nya\\stagelist.xtx");

	m_numberToWork = new int*[m_stageNumberMax];

	for (int i=0;i<m_stageNumberMax;i++)
	{
		m_numberToWork[i] = new int[m_stageSubNumberMax];
		for (int k=0;k<m_stageSubNumberMax;k++)
		{
			m_numberToWork[i][k] = -1;
		}
	}

	m_dataMax = m_list->GetNameKosuu() / m_paramNumber;
	m_data = new int[m_dataMax * m_paramNumber];

	for (int i=1;i<m_dataMax;i++)
	{
		int stage = atoi(m_list->GetName(i*m_paramNumber+0));
		int stageSubNumber = atoi(m_list->GetName(i*m_paramNumber+1));
		if ((stage >= 0) && (stage < m_stageNumberMax) && (stageSubNumber >= 0) && (stageSubNumber < m_stageSubNumberMax))
		{
			m_numberToWork[stage][stageSubNumber] = i;

		}

		for (int k=0;k<m_paramNumber;k++)
		{
			int d = 0;
			int dataType = 0;
			if (dataType == 0)
			{
				d = atoi(m_list->GetName(i*m_paramNumber+k));
			}
//			else
//			{
//				d = SearchName(dataType,m_list->GetName(i*m_paramNumber+k));
//			}

			m_data[i*m_paramNumber+k] = d;

		}
	}

	m_nextExistFlag = new BOOL*[m_stageNumberMax];
	for (int i=0;i<m_stageNumberMax;i++)
	{
		m_nextExistFlag[i] = new BOOL[m_stageSubNumberMax];
	}

	m_subStageNumber = new int[m_stageNumberMax];

	for (int stage=0;stage<m_stageNumberMax;stage++)
	{
		int subStageNumber = 1;

		for (int subStage=0;subStage<m_stageSubNumberMax;subStage++)
		{
			BOOL f = FALSE;

			if (CheckStageNumber(stage,subStage))
			{
				if (subStage < m_stageSubNumberMax-1)
				{
					int n = StageToNumber(stage,subStage+1);
					if (n > 1)
					{
						f = TRUE;
						subStageNumber++;
					}
				}
			}

			m_nextExistFlag[stage][subStage] = f;
		}
		m_subStageNumber[stage] = subStageNumber;
	}

}

CStageData::~CStageData()
{
	End();
}

void CStageData::End(void)
{
	DELETEARRAY(m_subStageNumber);

	if (m_nextExistFlag != NULL)
	{
		for (int i=0;i<m_stageNumberMax;i++)
		{
			DELETEARRAY(m_nextExistFlag[i]);
		}
		DELETEARRAY(m_nextExistFlag);
	}

	DELETEARRAY(m_data);

	if (m_numberToWork != NULL)
	{
		for (int i=0;i<m_stageNumberMax;i++)
		{
			DELETEARRAY(m_numberToWork[i]);
		}

		DELETEARRAY(m_numberToWork);
	}


	ENDDELETECLASS(m_list);
}

int CStageData::StageToNumber(int stage,int subStage)
{
	int n = 0;

	if (CheckStageNumber(stage,subStage))
	{
		n = m_numberToWork[stage][subStage];
	}

	//debugtest
	if (n == 0) n = 1;

	return n;
}

BOOL CStageData::CheckStageNumber(int stage,int subStage)
{
	if ((stage >= 0) && (stage < m_stageNumberMax) && (subStage >= 0) && (subStage < m_stageSubNumberMax))
	{
		return TRUE;
	}

	return FALSE;
}

int CStageData::GetEnemyDeck(int stage,int subStage)
{
	int n = StageToNumber(stage,subStage);
	return m_data[n*m_paramNumber + PARAM_ENEMYDECK];
}

int CStageData::GetWorld(int stage,int subStage)
{
	int n = StageToNumber(stage,subStage);
	return m_data[n*m_paramNumber + PARAM_WORLD];
}

int CStageData::GetEnchant(int stage,int subStage,int k)
{
	int n = StageToNumber(stage,subStage);
	return m_data[n*m_paramNumber + PARAM_ENCHANT + k];
}

BOOL CStageData::CheckExistNextSubStage(int stage,int subStage)
{
	if (CheckStageNumber(stage,subStage))
	{
		return m_nextExistFlag[stage][subStage];
	}
	return FALSE;
}

int CStageData::GetSubStageNumber(int stage)
{
	return m_subStageNumber[stage];
}

int CStageData::GetGachaCard(int stage,int subStage)
{
	int tableNumber = 0;
	int work[12*2];
	int dv = 0;


	int n = StageToNumber(stage,subStage);

	for (int i=0;i<6;i++)
	{
		int p = 100;

		int card = m_data[n*m_paramNumber + PARAM_GACHA_COMMON + i];
		if (card > 0)
		{
			dv += p;
			work[tableNumber*2] = card;
			work[tableNumber*2+1] = dv;
			tableNumber++;
		}
	}

	for (int i=0;i<2;i++)
	{
		int p = 40;
		int card = m_data[n*m_paramNumber + PARAM_GACHA_RARE + i];
		if (card > 0)
		{
			dv += p;
			work[tableNumber*2] = card;
			work[tableNumber*2+1] = dv;
			tableNumber++;
		}
	}

	for (int i=0;i<2;i++)
	{
		int p = 20;
		int card = m_data[n*m_paramNumber + PARAM_GACHA_SUPERRARE + i];
		if (card > 0)
		{
			dv += p;
			work[tableNumber*2] = card;
			work[tableNumber*2+1] = dv;
			tableNumber++;
		}
	}

	if (dv == 0) return 100;
	int r = rand() % dv;

	for (int i=0;i<tableNumber;i++)
	{
		if (r<work[i*2+1])
		{
			return work[i*2];
		}
	}

	return 100;
}

int CStageData::GetAddHex(int stage,int subStage,int type)
{
	if (CheckStageNumber(stage,subStage))
	{
		int n = StageToNumber(stage,subStage);
		return m_data[n*m_paramNumber + PARAM_ADDHEX + type];
	}
	return 0;
}

/*_*/



