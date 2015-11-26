#if !defined __CMK2011WIN_STAGEDATA__
#define __CMK2011WIN_STAGEDATA__


class CNameList;

class CStageData
{
public:
	CStageData(int n);
	~CStageData();
	void End(void);

	RECT GetStartArea(void){return m_startArea;}
	
	int GetTargetNumber(void){return m_targetNumber;}
	RECT GetTargetRect(int n){return m_targetRect[n];}
	int GetTargetType(int n){return m_targetType[n];}

	int GetBlockNumber(void){return m_blockNumber;}
	RECT GetBlockRect(int n){return m_blockRect[n];}
	
	int GetMirrorNumber(void){return m_mirrorNumber;}
	RECT GetMirrorRect(int n){return m_mirrorRect[n];}
	int GetMirrorType(int n){return m_mirrorType[n];}

	int GetHintNumber(void){return m_hintNumber;}
	RECT GetHintRect(int n){return m_hintRect[n];}
	LPSTR GetHintMessage(int n){return m_hintMessage[n];}
	int GetFontSize(int n);
	int GetHintColor(int n){return m_hintColor[n];}

private:
	CNameList* m_list;

	RECT m_startArea;
	
	int m_targetNumber;
	RECT* m_targetRect;
	int* m_targetType;

	int m_blockNumber;
	RECT* m_blockRect;

	int m_mirrorNumber;
	RECT* m_mirrorRect;
	int* m_mirrorType;

	int m_hintNumber;
	RECT* m_hintRect;
	LPSTR* m_hintMessage;
	int* m_hintColor;

	int m_stage;


	RECT GetRectData(int n);
	int GetNumber(int n);


};


#endif
/*_*/
