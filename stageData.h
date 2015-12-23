#if !defined __CMK2015WIN_STAGEDATA__
#define __CMK2015WIN_STAGEDATA__

class CNameList;

class CStageData
{
public:
	CStageData();
	~CStageData();
	void End(void);

	int GetStageMax(void){return m_stageNumberMax;}
	int GetSubStageMax(void){return m_stageSubNumberMax;}
	int GetEnemyDeck(int stage,int subStage);
	int GetWorld(int stage,int subStage);
	int GetEnchant(int stage,int subStage,int k);
	BOOL CheckExistNextSubStage(int stage,int subStage);
	int GetSubStageNumber(int stage);
	int GetGachaCard(int stage,int subStage);
	int GetAddHex(int stage,int subStage,int type);

private:
	int m_paramNumber;
	int m_stageNumberMax;
	int m_stageSubNumberMax;
	int** m_numberToWork;
	int m_dataMax;
	int* m_data;
	BOOL** m_nextExistFlag;
	int* m_subStageNumber;

	CNameList* m_list;

	int StageToNumber(int stage,int subStage);
	BOOL CheckStageNumber(int stage,int subStage);

};

#endif
/*_*/
