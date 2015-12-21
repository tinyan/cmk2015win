

#include <windows.h>
#include <math.h>


#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "..\..\systemNNN\nnnLib\commonGeneral.h"
#include "..\..\systemNNN\nnnLib\gameCallBack.h"

#include "..\..\systemNNN\nnnLib\commonSystemParamName.h"
#include "..\..\systemNNN\nnnUtilLib\nnnButtonStatus.h"

#include "..\..\systemNNN\nnnUtilLib\myMouseStatus.h"
#include "..\..\systemNNN\nnnUtilLib\mymessage.h"
#include "..\..\systemNNN\nnnUtilLib\nameList.h"

#include "..\..\systemNNN\nnnUtilLib\superButtonPicture.h"
#include "..\..\systemNNN\nnnUtilLib\commonButton.h"
#include "..\..\systemNNN\nnnUtilLib\commonButtonGroup.h"

#include "..\..\systemNNN\nnnUtilLib\suuji.h"


#include "mode.h"

//#include "clearStage.h"
//#include "mapData.h"
//#include "demoPlay.h"

//#include "hajike.h"

//#include "printCountDown.h"
//#include "printHaikei.h"
//#include "printPlate.h"
//#include "printScore.h"

//#include "printGameStatus.h"

//#include "resultControl.h"

//#include "highScoreData.h"

//#include "playStageCommon.h"
//#include "playStageType1.h"
//#include "playStageType1B.h"
//#include "playStageType2.h"
//#include "playStageType3.h"

#include "putChara.h"
#include "putCard.h"
#include "putPeople.h"
#include "landTimer.h"
#include "deckData.h"
#include "cardList.h"
#include "mana.h"
#include "stageData.h"

#include "hexarea.h"
#include "battleStatus.h"
#include "itemStatus.h"
#include "damageSuuji.h"
#include "printDamageEffect.h"

#include "attackObject.h"
#include "attackObjectControl.h"
#include "enchantControl.h"


#include "play.h"
#include "game.h"


#define GAMEPLAY_MODE 0
#define GAMEOVER_MODE 1
#define STAGECLEAR_MODE 2
#define RETRY_OR_EXIT_MODE 3
#define NEXT_OR_EXIT_MODE 4

#define USECARD_MODE 5

char CPlay::m_enchantTypeMessage[3][64]=
{
	"自軍エンチャント","敵エンチャント","ワールド効果"
};

CPlay::CPlay(CGame* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(PLAY_MODE);
	LoadSetupFile("play",256);

	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();

	m_deckData[0] = m_game2->GetDeckData();
	m_deckData[1] = m_game2->GetEnemyDeckData();
	m_putCard = m_game2->GetPutCard();
	m_cardList = m_game2->GetCardList();
	m_stageData = m_game2->GetStageData();

	
	m_hexArea = new CHexArea();
	m_damageSuuji = new CDamageSuuji();
	m_printDamageEffect = new CPrintDamageEffect();
	m_attackObjectControl = new CAttackObjectControl();
	m_enchantControl = new CEnchantControl(m_cardList,m_putCard);


	m_useButton = new CCommonButton(m_setup,"use");
	m_dropButton = new CCommonButton(m_setup,"drop");
	m_cancelButton = new CCommonButton(m_setup,"cancel");

	m_useButton->SetPicture(CSuperButtonPicture::GetPicture(3));
	m_dropButton->SetPicture(CSuperButtonPicture::GetPicture(4));
	m_cancelButton->SetPicture(CSuperButtonPicture::GetPicture(5));

	m_mana[0] = new CMana(0);
	m_mana[1] = new CMana(1);
	POINT pt;
	pt.x = 20;
	pt.y = 850;
	m_mana[0]->SetPoint(pt);
	pt.x = 20;
	pt.y = 110;
	m_mana[1]->SetPoint(pt);

	m_placeMax = 7;
	m_hand[0] = new int[m_placeMax];
	m_hand[1] = new int[m_placeMax];


	m_battleStatusMax = 256;
	for (int n=0;n<2;n++)
	{
		m_battleStatus[n] = new CBattleStatus*[m_battleStatusMax];
		for (int i=0;i<m_battleStatusMax;i++)
		{
			m_battleStatus[n][i] = new CBattleStatus();
		}
		m_battleStatusNumber[n] = 0;
	}

	m_itemStatusMax = 256;
	for (int n=0;n<2;n++)
	{
		m_itemStatus[n] = new CItemStatus*[m_itemStatusMax];
		for (int i=0;i<m_itemStatusMax;i++)
		{
			m_itemStatus[n][i] = new CItemStatus();
		}
		m_itemStatusNumber[n] = 0;
	}



	m_manaTypeMax = 2;

	m_miniCardNext.cx = 70;
	m_miniCardNext.cy = 70;
	m_miniCardSize.cx = 64;
	m_miniCardSize.cy = 64;
	m_miniCardPoint[0].x = 270-3*m_miniCardNext.cx;
	m_miniCardPoint[0].y = 920;
	m_miniCardPoint[1].x = 270-3*m_miniCardNext.cx;
	m_miniCardPoint[1].y = 40;


	m_putPeople = m_game2->GetPutPeople();
	m_landTimer[0] = new CLandTimer();
	m_landTimer[1] = new CLandTimer();
//	POINT pt;
	pt.x = 20;
	pt.y = 870;
	m_landTimer[0]->SetPoint(pt);
	m_landTimer[0]->SetTimerMax(30000);
	pt.x = 20;
	pt.y = 90;
	m_landTimer[1]->SetPoint(pt);
	m_landTimer[1]->SetTimerMax(30000);

	m_baseX[0][0] = 370;
	m_baseX[1][0] = 170;
	m_baseY[0][0] = 820;
	m_baseY[1][0] = 140;

	m_itemPic = new CPutChara("sys\\ta_item",4,1);

	m_hqPic = new CPutChara("sys\\ta_hq",4,2);

	m_tikeiSpeed[0] = 1.0f;
	m_tikeiSpeed[1] = 0.8f;
	m_tikeiSpeed[2] = 0.6f;
	m_tikeiSpeed[3] = 0.4f;

	m_worldCardPrintX = 70;
	m_worldCardPrintY = 480;
}


CPlay::~CPlay()
{
	End();
}

void CPlay::End(void)
{
	ENDDELETECLASS(m_itemPic);

	for (int i=0;i<2;i++)
	{
		ENDDELETECLASS(m_landTimer[i]);
	}

	for (int n=0;n<2;n++)
	{
		if (m_itemStatus[n] != NULL)
		{
			for (int i=0;i<m_itemStatusMax;i++)
			{
				ENDDELETECLASS(m_itemStatus[n][i]);
			}
			DELETEARRAY(m_itemStatus[n]);
		}
	}

	for (int n=0;n<2;n++)
	{
		if (m_battleStatus[n] != NULL)
		{
			for (int i=0;i<m_battleStatusMax;i++)
			{
				ENDDELETECLASS(m_battleStatus[n][i]);
			}
			DELETEARRAY(m_battleStatus[n]);
		}
	}



	DELETEARRAY(m_hand[1]);
	DELETEARRAY(m_hand[0]);

	ENDDELETECLASS(m_mana[1]);
	ENDDELETECLASS(m_mana[0]);

	ENDDELETECLASS(m_cancelButton);
	ENDDELETECLASS(m_dropButton);
	ENDDELETECLASS(m_useButton);

	ENDDELETECLASS(m_enchantControl);
	ENDDELETECLASS(m_attackObjectControl);
	ENDDELETECLASS(m_printDamageEffect);
	ENDDELETECLASS(m_damageSuuji);
	ENDDELETECLASS(m_hexArea);
}


int CPlay::Init(void)
{
	m_yamaMax[0] = 0;
	m_yamaMax[1] = 0;
	m_yamaPointer[0] = 0;
	m_yamaPointer[1] = 0;
	m_battleStatusNumber[0] = 0;
	m_battleStatusNumber[1] = 0;
	m_itemStatusNumber[0] = 0;
	m_itemStatusNumber[1] = 0;

	m_stageNumber = 0;
	m_stageSubNumber = 0;

	for (int i=0;i<1;i++)
	{
		m_hqHP[0][i] = 1000;
		m_hqHP[1][i] = 1000;
	}

	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_battleStatusMax;i++)
		{
			m_battleStatus[pl][i]->Clear();
		}
	}

	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_itemStatusMax;i++)
		{
			m_itemStatus[pl][i]->Clear();
		}
	}

	int enemyDeckNumber = m_stageData->GetEnemyDeck(m_stageNumber,m_stageSubNumber);
	m_deckData[1]->Load(enemyDeckNumber,TRUE);

	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_deckData[pl]->GetListNumber();i++)
		{
			int card = m_deckData[pl]->GetCard(i);
			if (card > 0)
			{
				m_yama[pl][m_yamaMax[pl]] = card;
				m_yamaMax[pl]++;
			}
		}
	}

	//shuffle
	for (int pl=0;pl<2;pl++)
	{
		int mx = m_yamaMax[pl];
		if (mx > 1)
		{
			for (int i=0;i<mx;i++)
			{
				int r = rand() % mx;
				int card = m_yama[pl][i];
				m_yama[pl][i] = m_yama[pl][r];
				m_yama[pl][r] = card;
			}
		}
	}


	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_placeMax;i++)
		{
			m_hand[pl][i] = 0;
			if (m_yamaPointer[pl] < m_yamaMax[pl])
			{
				int card = m_yama[pl][m_yamaPointer[pl]];
				if (card > 0)
				{
					m_hand[pl][i] = card;
				}

				m_yamaPointer[pl]++;
			}
		}
	}

	for (int pl=0;pl<2;pl++)
	{
		m_mana[pl]->SetManaMax(0,1);
		m_mana[pl]->SetMana(0,1);

		for (int i=1;i<=m_manaTypeMax;i++)
		{
			int m = 0;
//			if (i<3) m = 3;
			m_mana[pl]->SetManaMax(i,m);
			m_mana[pl]->SetMana(i,m);
		}
	}


	for (int j=3;j<32;j++)
	{
		for (int i=0;i<14;i++)
		{
			int type = 0;
			if (j == 15) type = 1;
			m_hexArea->SetType(i,j,type);
			int pw = 0;
			if (j<8) pw = -10000;
			if (j>=27) pw = 10000;
			m_hexArea->SetPower(i,j,pw);
		}
	}

	m_damageSuuji->AllClear();
	m_printDamageEffect->Clear();
	m_attackObjectControl->Clear();
	m_enchantControl->Clear();

	m_useButton->LoadFile();
	m_dropButton->LoadFile();
	m_cancelButton->LoadFile();

	ClearButton();

	m_enemyCount = 0;
	m_enemyMessageCount = 0;
	m_playMode = PLAY_MODE;
	
	
	m_worldCard = m_stageData->GetWorld(m_stageNumber,m_stageSubNumber);
	for (int i=0;i<3;i++)
	{
		int enemyEnchant = m_stageData->GetEnchant(m_stageNumber,m_stageSubNumber,i);
		if (enemyEnchant > 0)
		{
			m_enchantControl->AddEnchant(1,enemyEnchant);
		}
	}

	return -1;
}



int CPlay::Calcu(void)
{

	m_helpCard = 0;

	POINT pt = m_mouseStatus->GetZahyo();

	m_debugPoint = m_hexArea->GetAreaBlock((float)pt.x,(float)pt.y);
	//debug
	if (m_mouseStatus->CheckClick(1))
	{
		return ReturnFadeOut(GAMETITLE_MODE);
	}

	if (m_mouseStatus->CheckClick(2))
	{
//		int card = 100 + (rand() % 3);
//		m_game2->SetGachaCard(card);
//		return ReturnFadeOut(GACHA_MODE);
	}

	m_damageSuuji->Calcu();
	m_printDamageEffect->Calcu();
	m_attackObjectControl->CutLast();


	if (m_playMode == PLAY_MODE)
	{
		CheckHelpCard(pt);
		return CalcuPlayMode();
	}
	if (m_playMode == USECARD_MODE)
	{
		return CalcuUseCard();
	}
	if (m_playMode == GAMEOVER_MODE)
	{
		MoveAttackObject();
		return CalcuLose();
	}
	if (m_playMode == STAGECLEAR_MODE)
	{
		MoveAttackObject();
		return CalcuWin();
	}



	return -1;
}

int CPlay::CalcuPlayMode(void)
{

	POINT pt = m_mouseStatus->GetZahyo();

	if (m_mouseStatus->CheckClick(0))
	{
		int place = GetOnPlace(pt);
		if (place != -1)
		{
			int card = m_hand[0][place];
			if (card > 0)
			{
				m_selectedCard = card;
				m_selectedPlace = place;

				if (CheckMana(0,card))
				{
					m_useButton->SetEnable();
				}
				else
				{
					m_useButton->SetEnable(FALSE);
				}
				ClearButton();

				m_playMode = USECARD_MODE;
				return -1;
			}
		}
	}

	//dummy enemy card
	m_enemyCount++;
	if (m_enemyCount >= 20)
	{
		if ((rand() % 100) < 5)
		{
			int r = rand() % 7;
			int card = m_hand[1][r];
			if (card > 0)
			{
				if (CheckMana(1,card))
				{
					BOOL f = TRUE;
					int cardType = m_cardList->GetType(card);
					if (cardType == 5)
					{
						int spellType = m_cardList->GetSpellType(card);
						if (spellType == 0)
						{
							if (m_battleStatusNumber[0] == 0) f = FALSE;
						}
						else if ((spellType == 1) || (spellType == 2))
						{
							if (m_enchantControl->GetEnchantNumber(0) == 0) f = FALSE;
						}
					}

					if (cardType == 4)
					{
						int itemType = m_cardList->GetItemType(card);
						if (itemType == 0)
						{
							f = FALSE;
							for (int i=0;i<m_battleStatusNumber[1];i++)
							{
								if (m_battleStatus[1][i]->m_playerEnemy != -1)
								{
									if (m_battleStatus[1][i]->m_hp < m_battleStatus[1][i]->m_hpMax)
									{
										f = TRUE;
										break;
									}
								}
							}
						}
					}

					if (f)
					{
						UseCardRoutine(1,r);
						m_enemyCount = 0;
						AddEnemyUseMessage(card);
					}
	//				OutputDebugString("ENEMY USE CARD");
				}
			}
		}
	}

	//enemy discard
	if (m_enemyCount >= 20)
	{
		int found = -1;
		for (int i=0;i<m_placeMax;i++)
		{
			if (m_hand[1][i] == 0)
			{
				found = i;
				break;
			}
		}

		if (found == -1)
		{
			//将来使えるカードがあるか

			for (int i=0;i<m_placeMax;i++)
			{
				int card = m_hand[1][i];
				if (CheckMaxMana(1,card))
				{
					found = i;
					break;
				}
			}

			if (found == -1)
			{
				//dropcard
				int r = rand() % 7;
				int card = m_hand[1][r];
				DropCardRoutine(1,r);
				AddEnemyDropMessage(card);
			}
		}
	}



	CheckTargetExist();
	//search item

	//new target enemy
	CalcuTargetEnemy();


	//占領
	Occupy();
	//move
	MovePeople();

	Attack();

	MoveAttackObject();

	//getitem
	//battle

	GetLandPower();



	DeleteLastEmpty();

	return -1;
}


void CPlay::HealMana(int pl)
{
	m_mana[pl]->AllHeal(1);
}

void CPlay::DrawCard(int pl)
{
	for (int i=0;i<m_placeMax;i++)
	{
		if (m_hand[pl][i] == 0)
		{
			if (m_yamaPointer[pl] < m_yamaMax[pl])
			{
				int card = m_yama[pl][m_yamaPointer[pl]];
				m_hand[pl][i] = card;
				m_yamaPointer[pl]++;
				return;
			}
		}
	}

}

//こうげきされていて、もくひょうがとおいならきりかえる
//敵がいるときは基地攻撃をやめる

void CPlay::CalcuTargetEnemy(void)
{
	for (int pl=0;pl<2;pl++)
	{
		BOOL f = FALSE;

		for (int i=0;i<m_battleStatusNumber[1-pl];i++)
		{
			if (m_battleStatus[1-pl][i]->m_playerEnemy != -1)
			{
				f = TRUE;
				break;
			}
		}

		if (f)
		{
			for (int i=0;i<m_battleStatusNumber[pl];i++)
			{
				if (m_battleStatus[pl][i]->m_targetType == 0)
				{
					m_battleStatus[pl][i]->m_targetNumber = -1;
					m_battleStatus[pl][i]->m_targetItemNumber = -1;
					m_battleStatus[pl][i]->m_targetType = -1;
				}
			}
		}
	}

	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_battleStatusNumber[pl];i++)
		{
			CBattleStatus* people = m_battleStatus[pl][i];
			if (people->m_playerEnemy != -1)
			{
				if (people->m_targetItemNumber == -1)
				{
					if (CheckFromExist(pl,i))
					{
						if (!CheckSameTargetAndFrom(pl,i))
						{
							BOOL f = FALSE;
							if (people->m_targetNumber == -1)
							{
								f = TRUE;
							}
							else
							{
								float dist = CalcuDist(pl,i,1-pl,people->m_targetNumber);
								float fromDist = CalcuDist(pl,i,1-pl,people->m_fromNumber);
								if (fromDist < dist)
								{
									f = TRUE;
								}
							}
							//near or nothing
							if (f)
							{
								people->m_targetNumber = people->m_fromNumber;
								people->m_targetSerial = people->m_fromSerial;
								people->m_targetType = 1;
							}
						}
					}
					else
					{
						//item?
//						if (people->m_targetNumber == -1)
						if (people->m_targetItemNumber == -1)
						{
							int itemNumber = GetRandomItem(pl);
							if (itemNumber != -1)
							{
								//have?
								int itemType = m_itemStatus[pl][itemNumber]->m_itemType;
								if (people->m_haveItem[itemType] == 0)
								{
									CItemStatus* item = m_itemStatus[pl][itemNumber];
									people->m_targetItemNumber = itemNumber;
									people->m_targetItemSerial = item->m_serial;
									item->m_fromNumber = i;
									item->m_fromSerial = people->m_serial;
									people->m_targetType = 2;
								}
							}
						}

						//enemy?
						if ((people->m_targetNumber == -1) && (people->m_targetItemNumber == -1))
						{
							int enemyNumber = m_battleStatusNumber[1-pl];
							int r = 0;
							if (enemyNumber > 2)
							{
								r = rand() % enemyNumber;
							}

							for (int k=0;k<enemyNumber;k++)
							{
								if (m_battleStatus[1-pl][r]->m_playerEnemy != -1)
								{
									people->m_targetNumber = r;
									people->m_targetSerial = m_battleStatus[1-pl][r]->m_serial;
									people->m_targetType = 1;

//									char mes[256];
//									sprintf_s(mes,256,"目標:%d\x00d\x00a",r);
//									OutputDebugString(mes);
									break;
								}

								r++;
								r %= enemyNumber;
							}
						}


						//base?
						if ((people->m_targetNumber == -1) && (people->m_targetItemNumber == -1))
						{
							people->m_targetType = 0;
						}

					}
				}
			}
		}
	}
}

int CPlay::GetRandomItem(int pl)
{
	int mx = m_itemStatusNumber[pl];
	if (mx <= 0) return -1;
	int n = 0;
	if (mx > 1)
	{
		n = rand() % mx;
	}
	if (m_itemStatus[pl][n]->m_playerEnemy == -1) return -1;
	if (m_itemStatus[pl][n]->m_fromNumber != -1) return -1;
	return n;
}

float CPlay::CalcuDist(int pl,int n,int pl2,int n2)
{
	float x = m_battleStatus[pl][n]->m_x;
	float y = m_battleStatus[pl][n]->m_y;
	float x2 = m_battleStatus[pl2][n2]->m_x;
	float y2 = m_battleStatus[pl2][n2]->m_y;

	float dx = x - x2;
	float dy = y - y2;
	float dist = sqrt(dx*dx+dy*dy);
	return dist;
}

BOOL CPlay::CheckFromExist(int pl,int n)
{
	CBattleStatus* people = m_battleStatus[pl][n];
	int fromNumber = people->m_fromNumber;
	int fromSerial = people->m_fromSerial;
	if (fromNumber == -1) return FALSE;
	if (fromNumber >= m_battleStatusNumber[1-pl]) return FALSE;
	if (m_battleStatus[1-pl][fromNumber]->m_serial != fromSerial) return FALSE;

	return TRUE;
}

BOOL CPlay::CheckSameTargetAndFrom(int pl,int n)
{
	CBattleStatus* people = m_battleStatus[pl][n];
	int fromNumber = people->m_fromNumber;
	int fromSerial = people->m_fromSerial;
	int targetNumber = people->m_targetNumber;
	int targetSerial = people->m_targetSerial;
	if ((fromNumber == targetNumber) && (fromSerial == targetSerial))
	{
		return TRUE;
	}
	return FALSE;
}

void CPlay::GetLandPower(void)
{
	for (int i=0;i<2;i++)
	{
		int pw = m_hexArea->GetLandPower(i);
		pw += 100;

		m_debugPower[i] = pw;

		if (m_landTimer[i]->AddTimer(pw))
		{
			m_landTimer[i]->SetTimer(0);
			HealMana(i);
			DrawCard(i);
		}
	}
}

void CPlay::Occupy(void)
{
	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_battleStatusNumber[pl];i++)
		{
			CBattleStatus* people = m_battleStatus[pl][i];
			if (people->m_playerEnemy != -1)
			{
				float x = m_battleStatus[pl][i]->m_x;
				float y = m_battleStatus[pl][i]->m_y;

				POINT hexBlock = m_hexArea->GetAreaBlock(x,y);
//				int type = m_hexArea->GetType(hexBlock.x,hexBlock.y);
//				int pw = m_hexArea->GetPower(hexBlock.x,hexBlock.y);
				int occupy = people->m_occupyPower;
				m_hexArea->Occupy(hexBlock,pl,occupy);
			}
		}
	}
}

void CPlay::MovePeople(void)
{
	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_battleStatusNumber[pl];i++)
		{
			CBattleStatus* people = m_battleStatus[pl][i];
			if (people->m_playerEnemy != -1)
			{
				int targetType = people->m_targetType;
				float targetX = 0.0f;
				float targetY = 0.0f;
				BOOL f = FALSE;

				if (targetType == 0)
				{
					targetX = m_baseX[1-pl][0];
					targetY = m_baseY[1-pl][0];

					f = TRUE;
				}
				else if (targetType == 1)
				{
					int targetNumber = people->m_targetNumber;
					int targetSerial = people->m_targetSerial;
					if (targetNumber != -1)
					{
						if (m_battleStatus[1-pl][targetNumber]->m_playerEnemy != -1)
						{
							if (m_battleStatus[1-pl][targetNumber]->m_serial == targetSerial)
							{
								targetX = m_battleStatus[1-pl][targetNumber]->m_x;
								targetY = m_battleStatus[1-pl][targetNumber]->m_y;
								f = TRUE;
							}
						}
					}
				}
				else if (targetType == 2)
				{
					int itemNumber = people->m_targetItemNumber;
					int itemSerial = people->m_targetItemSerial;
					if (CheckLegalItem(pl,itemNumber,itemSerial))
					{
						targetX = m_itemStatus[pl][itemNumber]->m_x;
						targetY = m_itemStatus[pl][itemNumber]->m_y;
						f = TRUE;
					}
				}

				if (f)
				{
					float x = m_battleStatus[pl][i]->m_x;
					float y = m_battleStatus[pl][i]->m_y;
					float dx = targetX - x;
					float dy = targetY - y;
					float dist = sqrt(dx*dx+dy*dy);
					float speed = m_battleStatus[pl][i]->m_speed;

					speed *= GetWorldSpeedEffect();

					POINT hexBlock = m_hexArea->GetAreaBlock(x,y);
					int type = m_hexArea->GetType(hexBlock.x,hexBlock.y);

					if ((type > 0) && (type < 4))
					{
						speed *= m_tikeiSpeed[type];
					}
					int pw = m_hexArea->GetPower(hexBlock.x,hexBlock.y);
					if (pl == 0)
					{
						if (pw<10000)
						{
							speed = 0.3f;
						}
						else if (pw <= -10000)
						{
							speed = 0.05f;
						}
					}
					else if (pl == 1)
					{
						if (pw>=-10000)
						{
							speed = 0.3f;
						}
						else if (pw >= 10000)
						{
							speed = 0.05f;
						}
					}



					if (speed > dist) speed = dist;
					float range = m_battleStatus[pl][i]->m_range * 0.8f;
				
					if (targetType != 2)
					{
						if (dist < range) speed = 0.0f;
					}
					else
					{
						if (dist < 10.0f) speed = 0.0f;
					}

					float mulX = 1.0f;

					if (pl == 0)
					{
						if (dy< -200.0f) mulX = 0.0f;
					}
					else if (pl == 1)
					{
						if (dy> 200.0f) mulX = 0.0f;
					}


					float nx = 0.0f;
					float ny = 1.0f;
					if (dist > 0.0)
					{
						nx = dx / dist;
						ny = dy / dist;
					}
					x += nx * speed * mulX;
					y += ny * speed;

					m_battleStatus[pl][i]->m_x = x;
					m_battleStatus[pl][i]->m_y = y;
				}

				//check get item
				if (people->m_targetItemNumber != -1)
				{
					int targetItemNumber = people->m_targetItemNumber;
					int targetSerial = people->m_targetItemSerial;
					if (CheckLegalItem(pl,targetItemNumber,targetSerial))
					{
						//near?
						float itemX = m_itemStatus[pl][targetItemNumber]->m_x;
						float itemY = m_itemStatus[pl][targetItemNumber]->m_y;
						float x = people->m_x;
						float y = people->m_y;
						float dx = itemX - x;
						float dy = itemY - y;
						float dist = sqrt(dx*dx+dy*dy);
						float range = m_battleStatus[pl][i]->m_range;
//						if (dist < range)
						if (dist < 20.0f)
						{
							GetItemRoutine(pl,i);
						}
					}
				}
			}
		}
	}
}

void CPlay::GetItemRoutine(int pl,int n)
{
	OutputDebugString("\x00d\x00a *** GET ITEM ***");
	CBattleStatus* people = m_battleStatus[pl][n];
	int targetItemNumber = people->m_targetItemNumber;
	int targetSerial = people->m_targetItemSerial;
	if (CheckLegalItem(pl,targetItemNumber,targetSerial))
	{
		int card = m_itemStatus[pl][targetItemNumber]->m_card;
		if (card > 0)
		{
			int itemType = m_cardList->GetEquipType(card);
			if (itemType >= 0)
			{
				people->m_haveItem[itemType] = card;
				people->CalcuStatus(m_cardList);
			}


			m_itemStatus[pl][targetItemNumber]->m_playerEnemy = -1;
			people->m_targetType = -1;
			people->m_targetItemNumber = -1;
			people->m_targetNumber = -1;
		}
	}
}


void CPlay::Attack(void)
{
	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_battleStatusNumber[pl];i++)
		{
			CBattleStatus* people = m_battleStatus[pl][i];
			if (people->m_playerEnemy != -1)
			{
				people->m_attackCount += people->m_attackSpeed;
				int count = people->m_attackCount;
				if (count >= 10000)
				{
					count -= 10000;
					people->m_attackCount = count;

					int targetType = people->m_targetType;
					int targetNumber = people->m_targetNumber;
					int targetSerial = people->m_targetSerial;

					if (targetType == 0)
					{
						if (CheckInRangeBase(pl,i,1-pl,0))
						{
							AttackBase(pl,i,1-pl,0);
						}
					}
					else if (targetType == 1)
					{
						if (CheckLegalTarget(1-pl,targetNumber,targetSerial))
						{
							if (CheckInRange(pl,i,1-pl,targetNumber))
							{
								//
								NormalAttack(pl,i,1-pl,targetNumber);
							}
						}

					}
				}
			}
		}
	}
}


void CPlay::AttackBase(int pl,int n,int pl2,int n2)
{
	CBattleStatus* people = m_battleStatus[pl][n];
	int attack = people->m_attack;

	CAttackObject* obj = m_attackObjectControl->SearchAki();
	if (obj != NULL)
	{
		int count = people->m_weaponSpeed;
		int type = 0;
		float fromX = people->m_x;
		float fromY = people->m_y;
		obj->SetFrom(fromX,fromY,attack,count,type);

//		int serial = enemy->m_serial;
		obj->SetTarget(pl2,n2,0);
	}
}


void CPlay::NormalAttack(int pl,int n,int pl2,int n2)
{
	CBattleStatus* people = m_battleStatus[pl][n];
	CBattleStatus* enemy = m_battleStatus[pl2][n2];
	enemy->m_fromSerial = enemy->m_serial;
	enemy->m_fromNumber = n;

	int attack = people->m_attack;
	CAttackObject* obj = m_attackObjectControl->SearchAki();
	if (obj != NULL)
	{
		int count = people->m_weaponSpeed;
		int type = 1;
		float fromX = people->m_x;
		float fromY = people->m_y;
		obj->SetFrom(fromX,fromY,attack,count,type);

		int serial = enemy->m_serial;
		obj->SetTarget(pl2,n2,serial);
	}
}


void CPlay::AttackEnemy(int pl,int n,int attack,BOOL magic)
{
	if (!magic)
	{
		int worldAttack = GetAttackEffectByWorld();
		attack += worldAttack;
		if (attack < 1) attack = 1;
	}

	CBattleStatus* enemy = m_battleStatus[pl][n];
	int deffense = enemy->m_deffense;

	if (!magic)
	{
		attack += m_enchantControl->GetAttack(1-pl);
		deffense += m_enchantControl->GetDeffense(pl);
	}




	attack *= ((rand() % 100) + 50);
	attack /= 100;

	int damage = attack;
	if (!magic)
	{
		damage -= deffense;
	}
	if (damage <= 0) damage = 1;

	int hp = enemy->m_hp;
	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
	}
	enemy->m_hp = hp;
	if (hp <= 0)
	{
		DeathPeople(pl,n);
	}

	int putX = (int)(enemy->m_x);
	int putY = (int)(enemy->m_y);
	m_printDamageEffect->AddDamage(putX,putY,pl);

	putY -= 32;
	m_damageSuuji->AddSuuji(putX,putY,damage,pl);
}

void CPlay::MoveAttackObject(void)
{
	int n = m_attackObjectControl->m_attackObjectNumber;
	for (int i=0;i<n;i++)
	{
		CAttackObject* obj = m_attackObjectControl->GetAttackObject(i);
		if (obj->m_flag)
		{
			if (obj->m_type == 0)
			{
				//base
				int pl = obj->m_targetPlayer;

				BOOL f = obj->Calcu();
				if (f)
				{
					int attack = obj->m_attack;
					DamageBase(pl,0,attack);
				}
			}
			else if (obj->m_type == 1)
			{
				int pl = obj->m_targetPlayer;
				int targetNumber = obj->m_targetNumber;
				int serial = obj->m_targetSerial;

				if (CheckLegalTarget(pl,targetNumber,serial))
				{
					BOOL f = obj->Calcu();
					if (f)
					{
						int attack = obj->m_attack;
						AttackEnemy(pl,targetNumber,attack);
					}
				}
				else
				{
					obj->m_flag = FALSE;
				}
			}
		}
	}
}

void CPlay::DamageBase(int pl,int n,int attack)
{
	m_hqHP[pl][n] -= attack;


	int putX = (int)m_baseX[pl][n];
	int putY = (int)m_baseY[pl][n];
	m_printDamageEffect->AddDamage(putX,putY,pl);

	putY -= 32;
	m_damageSuuji->AddSuuji(putX,putY,attack,pl);



	if (m_hqHP[pl][n] <= 0)
	{
		if (pl == 0)
		{
			StartGameover();
		}
		else
		{
			StartClear();
		}
	}



}


void CPlay::DeathPeople(int pl,int n)
{
	CBattleStatus* people = m_battleStatus[pl][n];

	people->m_playerEnemy = -1;
}


BOOL CPlay::CheckInRange(int pl,int n,int pl2,int n2)
{
	float dist = CalcuDist(pl,n,pl2,n2);
	CBattleStatus* people = m_battleStatus[pl][n];
	float range = people->m_range;
	if (range >= dist) return TRUE;
	return FALSE;
}

BOOL CPlay::CheckInRangeBase(int pl,int n,int pl2,int n2)
{
	float x = m_battleStatus[pl][n]->m_x;
	float y = m_battleStatus[pl][n]->m_y;
	float x2 = m_baseX[pl2][n2];
	float y2 = m_baseY[pl2][n2];
	float dx = x2 - x;
	float dy = y2 - y;
	float dist = sqrt(dx*dx+dy*dy);

	CBattleStatus* people = m_battleStatus[pl][n];
	float range = people->m_range;
	if (range >= dist) return TRUE;
	return FALSE;
}



BOOL CPlay::CheckLegalTarget(int playerenemy,int n,int serial)
{
	if (n == -1) return FALSE;
	if (n < m_battleStatusNumber[playerenemy])
	{
		CBattleStatus* enemy = m_battleStatus[playerenemy][n];
		if (enemy->m_playerEnemy != -1)
		{
			if (enemy->m_serial == serial)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CPlay::CheckLegalItem(int playerenemy,int n,int serial)
{
	if (n == -1) return FALSE;
	if (n < m_itemStatusNumber[playerenemy])
	{
		CItemStatus* item = m_itemStatus[playerenemy][n];
		if (item->m_playerEnemy != -1)
		{
			if (item->m_serial == serial)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}


int CPlay::CalcuUseCard(void)
{
	int rt1 = m_useButton->Calcu(m_inputStatus);
	int rt2 = m_dropButton->Calcu(m_inputStatus);
	int rt3 = m_cancelButton->Calcu(m_inputStatus);

	if (rt1 != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt1);
		if (nm == 0)
		{
			UseCardRoutine();
			ClearButton();
			m_playMode = PLAY_MODE;
			return -1;
		}
	}

	if (rt2 != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt2);
		if (nm == 0)
		{
			DropCardRoutine();
			ClearButton();
			m_playMode = PLAY_MODE;
			return -1;
		}
	}

	if (rt3 != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt3);
		if (nm == 0)
		{
			m_playMode = PLAY_MODE;
			return -1;
		}
	}

	return -1;
}



void CPlay::UseCardRoutine(int pl,int place)
{
	if (place == -1) place = m_selectedPlace;

	int card = m_hand[pl][place];

	//mana
	UseMana(pl,card);


	//use
	int type = m_cardList->GetType(card);
	switch (type)
	{
	case 1:
		UseLandCard(pl,card);
		break;
	case 2:
		UsePeopleCard(pl,card);
		break;
	case 3:
		UseEquipItemCard(pl,card);
		break;
	case 4:
		UseItemCard(pl,card);
		break;
	case 5:
		UseSpellCard(pl,card);
		break;
	case 6:
		UseEnchantCard(pl,card);
		break;
	case 7:
		UseWorldCard(pl,card);
		break;
	default:
		break;
	}


	m_hand[pl][place] = 0;
}

void CPlay::DropCardRoutine(int pl,int place)
{
	if (place == -1) place = m_selectedPlace;


	m_hand[pl][place] = 0;
}

void CPlay::UseLandCard(int pl,int card)
{
	for (int i=0;i<=m_manaTypeMax;i++)
	{
		int pw = m_cardList->GetLandPower(card,i);
		m_mana[pl]->AddLandPower(i,pw);
	//	m_mana[pl]->AddMana(i,pw);
	}

}


void CPlay::UsePeopleCard(int pl,int card)
{
	int ppl = m_cardList->GetNumbers(card);
	ppl *= GetWorldMulti();

	for (int i=0;i<ppl;i++)
	{
		int n = SearchAkiPeople(pl);
		if (n == -1)
		{
			//no people
			return;
		}

		if (n>=m_battleStatusNumber[pl])
		{
			m_battleStatusNumber[pl] = n+1;
		}

		CBattleStatus* people = m_battleStatus[pl][n];
		people->Clear();
		people->NewSerial();
		people->m_playerEnemy = pl;

		float x = (float)(rand() % 500) + 20.0f;
		float y = (float)( (1-pl) * 600 ) + 180.0f;
		
		
		
		
		int hp = m_cardList->GetHP(card);
		
		int rangeOrg = m_cardList->GetRange(card);
		rangeOrg *= ((rand() % 50) + 75);
		rangeOrg /= 100;
		if (rangeOrg < 1) rangeOrg = 1;
		float range = (float)rangeOrg;

		float speed = (float)(m_cardList->GetMoveSpeed(card));
		speed *= 0.01f;
		speed *= (float)((rand() % 50) + 75);
		speed *= 0.01f;

		int attack = m_cardList->GetAttack(card);
		int attackSpeed = m_cardList->GetAttackSpeed(card);
		int deffense = m_cardList->GetDeffense(card);
		int occupy = m_cardList->GetOccupy(card);
		int weaponSpeed = m_cardList->GetWeaponSpeed(card);

		attackSpeed *= (80 + rand() % 40);
		attackSpeed /= 100;
		if (attackSpeed < 1) attackSpeed = 1;


		people->m_x = x;
		people->m_y = y;

		people->m_hpMax = hp;
		people->m_hp = hp;
		people->m_attackBase = attack;
		people->m_deffenseBase = deffense;
		people->m_speed = speed;
		people->m_hpMax = people->m_hpMax;
		people->m_range = range;
		people->m_attackSpeedBase = attackSpeed;
		people->m_attackSpeed = attackSpeed;
		people->m_attackCount = 0;
		people->m_occupyPower = occupy;
		people->m_weaponSpeed = weaponSpeed;
		people->CalcuStatus(m_cardList);
	}
}


int CPlay::SearchAkiPeople(int pl)
{
	for (int i=0;i<m_battleStatusMax;i++)
	{
		if (m_battleStatus[pl][i]->m_playerEnemy == -1)
		{
			return i;
		}
	}

	return -1;
}

int CPlay::SearchAkiItem(int pl)
{
	for (int i=0;i<m_itemStatusMax;i++)
	{
		if (m_itemStatus[pl][i]->m_playerEnemy == -1)
		{
			return i;
		}
	}

	return -1;
}

void CPlay::UseEquipItemCard(int pl,int card)
{
	int it = m_cardList->GetNumbers(card);
	it *= GetWorldMulti();
	for (int i=0;i<it;i++)
	{
		int n = SearchAkiItem(pl);
		if (n == -1)
		{
			//no item
			return;
		}

		if (n>=m_itemStatusNumber[pl])
		{
			m_itemStatusNumber[pl] = n+1;
		}

		CItemStatus* item = m_itemStatus[pl][n];
		item->Clear();
		item->NewSerial();
		item->m_playerEnemy = pl;

		float x = (float)(rand() % 500) + 20.0f;
		float y = (float)( (1-pl) * 600 ) + 180.0f;
		int itemType = m_cardList->GetEquipType(card);

		item->m_x = x;
		item->m_y = y;

		item->m_itemType = itemType;
		item->m_card = card;
	}
}

void CPlay::UseItemCard(int pl,int card)
{
	int nm = m_cardList->GetNumbers(card);
	int lp = nm;

	int itemType = m_cardList->GetItemType(card);


	if (itemType == 0)
	{
		int playerNumber = m_battleStatusNumber[pl];
		if (playerNumber<1) return;
		
		int heal = m_cardList->GetHP(card);

		//check world
//		int spellEffect = GetSpellEffectByWorld();
//		attack += spellEffect;

		if (nm == 0)
		{
			lp = playerNumber;
		}

		int n = rand() % playerNumber;

		for (int i=0;i<lp;i++)
		{
			if (m_battleStatus[pl][n]->m_playerEnemy == -1)
			{
				for (int k=0;k<playerNumber;k++)
				{
					n++;
					n %= playerNumber;
					if (m_battleStatus[pl][n]->m_playerEnemy != -1)
					{
						break;
					}
				}
			}

			if (m_battleStatus[pl][n]->m_playerEnemy != -1)
			{
				HealPeople(pl,n,heal);
			}

			n++;
			n %= playerNumber;
		}
	}
	else if (itemType == 1)
	{
	}

}

void CPlay::HealPeople(int pl,int n,int heal)
{
	int hp = m_battleStatus[pl][n]->m_hp;
	int hpMax = m_battleStatus[pl][n]->m_hpMax;
	int newHP = hp + heal;
	if (newHP > hpMax) newHP = hpMax;

	int realHeal = newHP - hp;
	if (realHeal > 0)
	{
		m_battleStatus[pl][n]->m_hp = newHP;
		int x = (int)m_battleStatus[pl][n]->m_x;
		int y = (int)m_battleStatus[pl][n]->m_y;
		y -= 32;

		m_damageSuuji->AddSuuji(x,y,realHeal,2);
	}

}

void CPlay::UseSpellCard(int pl,int card)
{
	int nm = m_cardList->GetNumbers(card);
	int lp = nm;

	int spellType = m_cardList->GetSpellType(card);


	if (spellType == 0)
	{
		int enemyNumber = m_battleStatusNumber[1-pl];
		if (enemyNumber<1) return;
		
		int attack = m_cardList->GetAttack(card);

		//check world
		int spellEffect = GetSpellEffectByWorld();
		attack += spellEffect;

		if (nm == 0)
		{
			lp = enemyNumber;
		}

		int n = rand() % enemyNumber;

		for (int i=0;i<lp;i++)
		{
			if (m_battleStatus[1-pl][n]->m_playerEnemy == -1)
			{
				for (int k=0;k<enemyNumber;k++)
				{
					n++;
					n %= enemyNumber;
					if (m_battleStatus[1-pl][n]->m_playerEnemy != -1)
					{
						break;
					}
				}
			}

			if (m_battleStatus[1-pl][n]->m_playerEnemy != -1)
			{
				AttackEnemy(1-pl,n,attack,TRUE);
			}

			n++;
			n %= enemyNumber;
		}
	}
	else if (spellType == 1)
	{
		//disenchant
		for (int i=0;i<lp;i++)
		{
			m_enchantControl->RemoveEnchant(1-pl,-2);
		}
	}
	else if (spellType == 2)
	{
		m_enchantControl->Clear();
		//trankillty
	}
}


int CPlay::SearchExistEnemy(int enemy)
{
	int enemyNumber = m_battleStatusNumber[enemy];
	if (enemyNumber<1) return -1;
	int n = rand() % enemyNumber;
	for (int i=0;i<enemyNumber;i++)
	{
		if (m_battleStatus[enemy][n]->m_playerEnemy == enemy) return n;
		n++;
		n %= enemyNumber;
	}
	return -1;
}

void CPlay::UseEnchantCard(int pl,int card)
{
	m_enchantControl->AddEnchant(pl,card);
}

void CPlay::UseWorldCard(int pl,int card)
{
	m_worldCard = card;
}


int CPlay::CalcuWin(void)
{
	m_lastCount++;
	if (m_lastCount >= 100)
	{
		m_lastCount = 100;
		if (m_mouseStatus->CheckClick())
		{
			int card = 100 + (rand() % 3);
			m_game2->SetGachaCard(card);
			return GACHA_MODE;
		}
	}

	return -1;
}

int CPlay::CalcuLose(void)
{
	m_lastCount++;
	if (m_lastCount >= 100)
	{
		m_lastCount = 100;
		if (m_mouseStatus->CheckClick())
		{
			return GAMETITLE_MODE;
		}
	}

	return -1;
}

int CPlay::Print(void)
{
	
	CAreaControl::SetNextAllPrint();

	CAllGraphics::FillScreen();

//	m_message->PrintMessage(10,10,"プレイ画面");

	for (int j=3;j<32;j++)
	{
		for (int i=0;i<14;i++)
		{
			if (((i+j) % 2) == 0)
			{
				m_hexArea->PutHex(i,j);
			}
		}
	}

	if (1)
	{
		char mes[256];
		sprintf_s(mes,256,"%d：%d",m_debugPower[0],m_debugPower[1]);
		m_message->PrintMessage(0,0,mes);
	}


	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<1;i++)
		{
			int hp = m_hqHP[pl][i];
			int st = 0;
			if (hp < 750) st = 1;
			if (hp < 500) st = 2;
			if (hp < 250) st = 3;

			int x = (int)m_baseX[pl][i];
			int y = (int)m_baseY[pl][i];

			m_hqPic->Put(x,y,st,pl);
		}
	}


	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_battleStatusNumber[pl];i++)
		{
			CBattleStatus* people = m_battleStatus[pl][i];
			if (people->m_playerEnemy != -1)
			{
				int x = (int)(people->m_x);
				int y = (int)(people->m_y);
				m_putPeople->Put(x,y,pl,1,0);

				//item
				for (int k=0;k<2;k++)
				{
					int equip = people->m_haveItem[k];
					if (equip > 0)
					{
						int equipType = m_cardList->GetEquipType(equip);
						int pic = m_cardList->GetEquipPic(equip);
						m_putPeople->PutItem(x,y,pl,equipType,pic);
					}
				}
			}
		}
	}

	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_itemStatusNumber[pl];i++)
		{
			CItemStatus* item = m_itemStatus[pl][i];
			if (item->m_playerEnemy != -1)
			{
				int x = (int)(item->m_x);
				int y = (int)(item->m_y);
				int card = item->m_card;
				int pic = m_cardList->GetItemPic(card);
				m_itemPic->Put(x,y,pic,0);
			}
		}
	}

	for (int i=0;i<m_attackObjectControl->m_attackObjectNumber;i++)
	{
		CAttackObject* obj = m_attackObjectControl->GetAttackObject(i);
		if (obj != NULL)
		{
			if (obj->m_flag)
			{
				int targetPlayer = obj->m_targetPlayer;
				int targetSerial = obj->m_targetSerial;
				int targetNumber = obj->m_targetNumber;
				if (obj->m_type == 0)
				{
					float toX = m_baseX[targetPlayer][targetNumber];
					float toY = m_baseY[targetPlayer][targetNumber];

					POINT pt = obj->GetPoint(toX,toY);

					CAllGeo::BoxFill(pt.x-3,pt.y-3,7,7,255,64,128);
				}
				else
				{
					if (CheckLegalTarget(targetPlayer,targetNumber,targetSerial))
					{
						CBattleStatus* enemy = m_battleStatus[targetPlayer][targetNumber];

						float toX = enemy->m_x;
						float toY = enemy->m_y;

						POINT pt = obj->GetPoint(toX,toY);
	//					int type = obj->m_type;

						//dummy
						CAllGeo::BoxFill(pt.x-3,pt.y-3,7,7,64,128,255);
					}
				}
			}
		}
	}


	m_printDamageEffect->Print();


	for (int i=0;i<2;i++)
	{
		m_landTimer[i]->Print();
	}


	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_placeMax;i++)
		{
			POINT pt = GetHandPoint(pl,i);
			int card = m_hand[pl][i];
			if (card > 0)
			{
				//mana check
				int md = 0;

				if (CheckMana(pl,card))
				{
					md = 1;
				}

				if (md == 1)
				{
					m_putCard->PutMiniCard(pt,card);
				}
				else
				{
					m_putCard->PutMiniCard(pt,card,50);
				}
			}
		}
	}

	m_damageSuuji->Print();


	if (m_worldCard != 0)
	{
		m_putCard->PutMiniCard(m_worldCardPrintX,m_worldCardPrintY,m_worldCard,70);
	}

	m_enchantControl->Print();


	for (int pl=0;pl<2;pl++)
	{
		m_mana[pl]->Print();
	}


	if (m_playMode == PLAY_MODE)
	{
		PrintHelpCard();
	}


	if (m_enemyMessageCount > 0)
	{
		m_enemyMessageCount--;
		int putX = 10;
		int putY = 10;
		CAllGeo::BoxFill(putX,putY,404,2,255,255,255);
		CAllGeo::BoxFill(putX,putY+34-2,404,2,255,255,255);
		CAllGeo::BoxFill(putX,putY,2,34,255,255,255);
		CAllGeo::BoxFill(putX+404-2,putY,2,34,255,255,255);

		CAllGeo::TransBoxFill(putX+2,putY+2,400,30,16,32,255,30);
		m_message->PrintMessage(putX+5,putY+5,m_enemyMessage,24);
	}

	if (m_playMode == USECARD_MODE)
	{
		m_putCard->PutCard(270,480,m_selectedCard);

		m_useButton->Print();
		m_dropButton->Print();
		m_cancelButton->Print();
	}
	
	if ((m_playMode == STAGECLEAR_MODE) || (m_playMode == GAMEOVER_MODE))
	{
		if (m_lastCount < 100)
		{
			int ps = (m_lastCount * 100) / 100;

			m_commonParts->TransLucentBlt2(270-128,480-128,0,0,256,256,ps);
		}
		else
		{
			m_commonParts->Put(270-128,480-128,TRUE);
		}
	}

	return -1;
}



void CPlay::FinalExitRoutine(void)
{
}


int CPlay::GetOnPlace(POINT pt)
{
	int dx = pt.x - (m_miniCardPoint[0].x - m_miniCardSize.cx / 2);
	int dy = pt.y - (m_miniCardPoint[0].y - m_miniCardSize.cy / 2);

	if ((dx>=0) && (dy>=0))
	{
		int nx = dx / m_miniCardNext.cx;
		int ny = dy / m_miniCardNext.cy;
		if ((nx < m_placeMax) && (ny == 0))
		{
			int ax = dx % m_miniCardNext.cx;
			if (ax < m_miniCardSize.cx)
			{
				return nx;
			}
		}
	}

	return -1;
}

POINT CPlay::GetHandPoint(int pl,int n)
{
	POINT pt;
	pt.x = m_miniCardPoint[pl].x + m_miniCardNext.cx * n;
	pt.y = m_miniCardPoint[pl].y;
	return pt;
}

BOOL CPlay::CheckMana(int pl,int card)
{
	int need[16];
	for (int i=0;i <= m_manaTypeMax;i++)
	{
		need[i] = m_cardList->GetNeedMana(card,i);
	}

	for (int i=1;i <= m_manaTypeMax;i++)
	{
		if (m_mana[pl]->GetMana(i) < need[i]) return FALSE;
	}

	int fusoku = need[0] - m_mana[pl]->GetMana(0);
	if (fusoku <= 0) return TRUE;

	for (int i=1;i <= m_manaTypeMax;i++)
	{
		int amari = m_mana[pl]->GetMana(i) - need[i];
		if (amari > 0)
		{
			fusoku -= amari;
			if (fusoku <= 0) return TRUE;
		}
	}

	return FALSE;
}

BOOL CPlay::CheckMaxMana(int pl,int card)
{
	int need[16];
	for (int i=0;i <= m_manaTypeMax;i++)
	{
		need[i] = m_cardList->GetNeedMana(card,i);
	}

	for (int i=1;i <= m_manaTypeMax;i++)
	{
		if (m_mana[pl]->GetManaMax(i) < need[i]) return FALSE;
	}

	int fusoku = need[0] - m_mana[pl]->GetManaMax(0);
	if (fusoku <= 0) return TRUE;

	for (int i=1;i <= m_manaTypeMax;i++)
	{
		int amari = m_mana[pl]->GetManaMax(i) - need[i];
		if (amari > 0)
		{
			fusoku -= amari;
			if (fusoku <= 0) return TRUE;
		}
	}

	return FALSE;
}

void CPlay::UseMana(int pl,int card)
{
	int need[16];
	for (int i=0;i <= m_manaTypeMax;i++)
	{
		need[i] = m_cardList->GetNeedMana(card,i);
	}

	int fusoku = m_cardList->GetNeedMana(card,0);


	for (int i=1;i <= m_manaTypeMax;i++)
	{
		int need = m_cardList->GetNeedMana(card,i);
		int mana = m_mana[pl]->GetMana(i);
		if (need > mana)
		{
			need = mana;
		}
		m_mana[pl]->UseMana(i,need);
	}

	if (1)
	{
		int mana = m_mana[pl]->GetMana(0);
		if (fusoku <= mana)
		{
			m_mana[pl]->UseMana(0,fusoku);
			return;
		}

		m_mana[pl]->UseMana(0,mana);
		fusoku -= mana;
	}

	for (int i=1;i <= m_manaTypeMax;i++)
	{
		int mana = m_mana[pl]->GetMana(i);
		if (fusoku < mana)
		{
			m_mana[pl]->UseMana(i,fusoku);
			return;
		}

		m_mana[pl]->UseMana(i,mana);
		fusoku -= mana;
	}

	//error!!
	OutputDebugString("*** ERROR マナ不足 ***");
}


void CPlay::ClearButton(void)
{
	m_useButton->Init();
	m_dropButton->Init();
	m_cancelButton->Init();
}


void CPlay::DeleteLastEmpty(void)
{
	for (int i=0;i<2;i++)
	{
		if (m_battleStatusNumber[i] > 0)
		{
			if (m_battleStatus[i][m_battleStatusNumber[i]-1]->m_playerEnemy == -1)
			{
				m_battleStatusNumber[i]--;
			}
		}
	}

	for (int i=0;i<2;i++)
	{
		if (m_itemStatusNumber[i] > 0)
		{
			if (m_itemStatus[i][m_itemStatusNumber[i]-1]->m_playerEnemy == -1)
			{
				m_itemStatusNumber[i]--;
			}
		}
	}
}


void CPlay::CheckTargetExist(void)
{
	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_battleStatusNumber[pl];i++)
		{
			CBattleStatus* people = m_battleStatus[pl][i];
			if (people->m_playerEnemy != -1)
			{
				int targetType = people->m_targetType;
				if (targetType == 0)
				{
					//base
				}
				else if (targetType == 1)
				{
					//people
					int targetNumber = people->m_targetNumber;
					int targetSerial = people->m_targetSerial;
					BOOL f = FALSE;
					if (targetNumber != -1)
					{
						if (targetNumber < m_battleStatusNumber[1-pl])
						{
							CBattleStatus* enemy = m_battleStatus[1-pl][targetNumber];

							if (enemy->m_playerEnemy != -1)
							{
								if (enemy->m_serial == targetSerial)
								{
									f = TRUE;
								}
							}
						}
					}

					if (!f)
					{
						//free
						people->m_targetNumber = -1;
					}
				}
				else if (targetType == 2)
				{
					//item
					int itemSerial = people->m_targetItemSerial;
					int itemNumber = people->m_targetItemNumber;
					//check item exist

					BOOL f = FALSE;
					if (CheckLegalItem(pl,itemNumber,itemSerial))
					{
						f = TRUE;
					}

					if (!f)
					{
						people->m_targetItemNumber = -1;
					}
				}
			}
			//from
			int fromTarget = people->m_fromNumber;
			int fromSerial = people->m_fromSerial;
			if (fromTarget != -1)
			{
				BOOL f = FALSE;
				if (fromTarget < m_battleStatusNumber[1-pl])
				{
					CBattleStatus* enemy = m_battleStatus[1-pl][fromTarget];
					if (enemy->m_playerEnemy != -1)
					{
						if (enemy->m_serial == fromSerial)
						{
							f = TRUE;
						}
					}
				}

				if (!f)
				{
					//free
					people->m_fromNumber = -1;
				}
			}

		}
	}


	for (int pl=0;pl<2;pl++)
	{
		for (int i=0;i<m_itemStatusNumber[pl];i++)
		{
			CItemStatus* item = m_itemStatus[pl][i];
			if (item->m_playerEnemy != -1)
			{
				//from
				int fromTarget = item->m_fromNumber;
				int fromSerial = item->m_fromSerial;
				if (fromTarget != -1)
				{
					BOOL f = FALSE;
					if (fromTarget < m_battleStatusNumber[pl])
					{
						CBattleStatus* enemy = m_battleStatus[pl][fromTarget];
						if (enemy->m_playerEnemy != -1)
						{
							if (enemy->m_serial == fromSerial)
							{
								f = TRUE;
							}
						}
					}
					if (!f)
					{
						//free
						item->m_fromNumber = -1;
					}
				}
			}

		}
	}

}

void CPlay::StartGameover(void)
{
	if (m_playMode != STAGECLEAR_MODE)
	{
		m_playMode = GAMEOVER_MODE;
		m_commonParts->LoadDWQ("sys\\ta_play_lose");
		m_lastCount = 0;
	}
}

void CPlay::StartClear(void)
{
	if (m_playMode != GAMEOVER_MODE)
	{
		m_playMode = STAGECLEAR_MODE;
		m_commonParts->LoadDWQ("sys\\ta_play_win");
		m_lastCount = 0;
	}
}

void CPlay::AddEnemyDropMessage(int card)
{
	char mes[256];
	LPSTR title = m_cardList->GetName(card);
	sprintf_s(mes,256,"捨てる：%s",title);
	AddEnemyMessage(mes);
}

void CPlay::AddEnemyUseMessage(int card)
{
	char mes[256];
	LPSTR title = m_cardList->GetName(card);
	sprintf_s(mes,256,"%s",title);
	AddEnemyMessage(mes);
}

void CPlay::AddEnemyMessage(LPSTR mes)
{
	int ln = strlen(mes);
	memcpy(m_enemyMessage,mes,ln+1);
	m_enemyMessageCount = 30;
}


int CPlay::GetSpellEffectByWorld(void)
{
	if (m_worldCard == 0) return 0;

	int effect = 0;

	int worldType = m_cardList->GetWorldType(m_worldCard);
	if (worldType == 2)
	{
		effect = m_cardList->GetAttack(m_worldCard);
	}

	return effect;
}

int CPlay::GetAttackEffectByWorld(void)
{
	if (m_worldCard == 0) return 0;

	int effect = 0;

	int worldType = m_cardList->GetWorldType(m_worldCard);
	if (worldType == 1)
	{
		effect = m_cardList->GetAttack(m_worldCard);
	}

	return effect;
}

float CPlay::GetWorldSpeedEffect(void)
{
	if (m_worldCard == 0) return 1.0f;
	int worldType = m_cardList->GetWorldType(m_worldCard);
	if (worldType != 3) return 1.0f;
	
	float f = (float)m_cardList->GetMoveSpeed(m_worldCard);
	f *= 0.01f;
	return f;
}

int CPlay::GetWorldMulti(void)
{
	if (m_worldCard == 0) return 1;
	int worldType = m_cardList->GetWorldType(m_worldCard);
	if (worldType != 4) return 1;
	int m = m_cardList->GetNumbers(m_worldCard);
	if (m<1) m = 1;//@@
	return m;
}


void CPlay::CheckHelpCard(POINT pt)
{
	if (m_worldCard > 0)
	{
		int dx = pt.x - m_worldCardPrintX;
		int dy = pt.y - m_worldCardPrintY;
		if ((dx > -32) && (dy > -32) && (dx < 32) && (dy < 32))
		{
			m_helpCard = m_worldCard;
			m_helpType = 2;
			return;
		}
	}

	//enchant
	for (int pl=0;pl<2;pl++)
	{
		int card = m_enchantControl->GetOnEnchant(pl,pt);
		if (card > 0)
		{
			m_helpCard = card;
			m_helpType = pl;
			return;
		}
	}
}

void CPlay::PrintHelpCard(void)
{
	if (m_helpCard > 0)
	{
		m_putCard->PutCard(270,480,m_helpCard);

		int putX = 100;
		int putY = 220;
		CAllGeo::BoxFill(putX,putY,340,40,32,96,64);

		m_message->PrintMessage(putX+6,putY+6,m_enchantTypeMessage[m_helpType],24);


	}
}

/*_*/


