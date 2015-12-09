

#if !defined __CMK2008SUMMER_PLAY__
#define __CMK2008SUMMER_PLAY__


class CCommonGeneral;
class CGame;
class CPicture;

class CMyMessage;

class CNameList;
class CPutPeople;

class CLandTimer;

class CCommonButton;
class CDeckData;
class CPutCard;
class CCardList;
class CMana;


class CPlay : public CCommonGeneral
{
public:
	CPlay(CGame* lpGame);
	~CPlay();
	void End(void);

	int Init(void);
	int Calcu(void);
	int Print(void);


	void FinalExitRoutine(void);

private:
	CGame* m_game2;
	CMyMessage* m_message;

	CPutPeople* m_putPeople;
	CLandTimer* m_landTimer[2];

	CDeckData* m_deckData;
	CPutCard* m_putCard;
	CCardList* m_cardList;

	CCommonButton* m_useButton;
	CCommonButton* m_dropButton;
	CCommonButton* m_cancelButton;

	int m_playMode;

	int CalcuPlayMode(void);
	int CalcuUseCard(void);
	void UseCardRoutine(int pl = 0,int place = -1);
	void DropCardRoutine(int pl = 0,int place = -1);

	int m_selectedCard;
	int m_selectedPlace;

	POINT m_miniCardPoint[2];
	SIZE m_miniCardNext;
	SIZE m_miniCardSize;
	int m_placeMax;

	int* m_hand[2];
	int m_manaTypeMax;
	int m_manaMax[2][16];
	CMana* m_mana[2];


	int GetOnPlace(POINT pt);
	POINT GetHandPoint(int pl,int n);
	BOOL CheckMana(int pl,int card);

	void ClearButton(void);

};






#endif
/*_*/

