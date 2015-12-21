#if !defined __CMK2015WIN_STAGEDATA__
#define __CMK2015WIN_STAGEDATA__

class CNameList;

class CStageData
{
public:
	CStageData();
	~CStageData();
	void End(void);

	int GetEnemyDeck(int stage,int subStage);
	int GetWorld(int stage,int subStage);
	int GetEnchant(int stage,int subStage,int k);

private:
	int m_paramNumber;
	int m_stageNumberMax;
	int m_stageSubNumberMax;
	int** m_numberToWork;
	int m_dataMax;
	int* m_data;

	CNameList* m_list;

	int StageToNumber(int stage,int subStage);
	BOOL CheckStageNumber(int stage,int subStage);
};

#endif
/*_*/
