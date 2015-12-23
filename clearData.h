#if !defined __CMK2015WIN_CLEARDATA__
#define __CMK2015WIN_CLEARDATA__


class CClearData
{
public:
	CClearData();
	~CClearData();
	void End(void);

	void Clear(void);
	BOOL Load(void);
	BOOL Save(void);
	int GetData(int stage,int subStage);
	void SetData(int stage,int subStage,int data);
	void AddData(int stage,int subStage,int data);
private:
	int** m_data;
	int m_stageMax;
	int m_subStageMax;

	BOOL CheckStage(int stage,int subStage);
	BOOL m_modifyFlag;
};

#endif
/*_*/
