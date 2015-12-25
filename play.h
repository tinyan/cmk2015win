

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
class CPutChata;
class CPutCard;
class CCardList;
class CMana;

class CHexArea;
class CBattleStatus;
class CItemStatus;
class CDamageSuuji;
class CPrintDamageEffect;
class CEnchantControl;
class CStageData;

class CAttackObjectControl;


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

	CDeckData* m_deckData[2];
	CPutCard* m_putCard;
	CCardList* m_cardList;

	CPutChara* m_tama;

	CCommonButton* m_useButton;
	CCommonButton* m_dropButton;
	CCommonButton* m_cancelButton;

	CHexArea* m_hexArea;
	CDamageSuuji* m_damageSuuji;
	CAttackObjectControl* m_attackObjectControl;
	CPrintDamageEffect* m_printDamageEffect;
	CPutChara* m_itemPic;
	CPutChara* m_hqPic;
	CEnchantControl* m_enchantControl;
	CStageData* m_stageData;


	int m_playMode;

	int m_stageNumber;
	int m_stageSubNumber;

	int CalcuPlayMode(void);
	int CalcuUseCard(void);
	int CalcuWin(void);
	int CalcuLose(void);
	int CalcuStart(void);

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
	int m_yama[2][256];
	int m_yamaMax[2];
	int m_yamaPointer[2];

	int GetOnPlace(POINT pt);
	POINT GetHandPoint(int pl,int n);
	BOOL CheckMana(int pl,int card);
	BOOL CheckMaxMana(int pl,int card);
	void UseMana(int pl,int card);

	void ClearButton(void);

	void UseLandCard(int pl,int card);
	void UsePeopleCard(int pl,int card);
	void UseEquipItemCard(int pl,int card);
	void UseItemCard(int pl,int card);
	void UseSpellCard(int pl,int card);
	void UseEnchantCard(int pl,int card);
	void UseWorldCard(int pl,int card);

	POINT m_debugPoint;
	int m_debugPower[2];

	int m_battleStatusMax;
	int m_battleStatusNumber[2];
	CBattleStatus** m_battleStatus[2];

	int m_itemStatusMax;
	int m_itemStatusNumber[2];
	CItemStatus** m_itemStatus[2];


	void DeleteLastEmpty(void);
	int SearchAkiPeople(int pl);
	int SearchAkiItem(int pl);
	void CheckTargetExist(void);

	void CalcuTargetEnemy(void);
	BOOL CheckFromExist(int pl,int n);
	BOOL CheckSameTargetAndFrom(int pl,int n);
	float CalcuDist(int pl,int n,int pl2,int n2);

	void Occupy(void);
	void MovePeople(void);
	void HealMana(int pl);
	void DrawCard(int pl);
	void GetLandPower(void);
	void Attack(void);
	void MoveAttackObject(void);
	void AttackEnemy(int pl,int n,int attack,BOOL magic = FALSE);
	void HealPeople(int pl,int n,int heal);

	BOOL CheckLegalTarget(int playerenemy,int n,int serial);
	BOOL CheckLegalItem(int playerenemy,int n,int serial);
	BOOL CheckInRange(int pl,int n,int pl2,int n2);

	void NormalAttack(int pl,int n,int pl2,int n2);
	void DeathPeople(int pl,int n);

	int GetRandomItem(int pl);

	BOOL CheckInRangeBase(int pl,int n,int pl2,int n2 = 0);
	void AttackBase(int pl,int n,int pl2,int n2 = 0);

	float m_baseX[2][1];
	float m_baseY[2][1];

	int m_hqHP[2][1];
	float m_tikeiSpeed[4];

	void DamageBase(int pl,int n,int attack);
	void GetItemRoutine(int pl,int n);

	void StartGameover(void);
	void StartClear(void);

	int m_enemyCount;
	int m_lastCount;
	void AddEnemyDropMessage(int card);
	void AddEnemyUseMessage(int card);
	void AddEnemyMessage(LPSTR mes);
	int m_enemyMessageCount;
	char m_enemyMessage[256];
	
	int m_worldCard;
	int SearchExistEnemy(int enemy);

	int GetSpellEffectByWorld(void);
	int GetAttackEffectByWorld(void);
	int GetDeffenseEffectByWorld(void);

	int m_helpCard;
	int m_helpType;
	void CheckHelpCard(POINT pt);
	
	int m_worldCardPrintX;
	int m_worldCardPrintY;

	float GetWorldSpeedEffect(void);
	int GetWorldMulti(void);

	int m_startCount;

	CSuuji* m_stageSuuji;
	CPicture* m_stagePlate;

	void PrintHelpCard(void);
	static char m_enchantTypeMessage[3][64];
};






#endif
/*_*/

