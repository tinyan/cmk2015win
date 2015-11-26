

#include <windows.h>

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

#include "bug.h"

#include "play.h"

#include "area.h"
#include "stageData.h"

#include "game.h"

#define GAMEPLAY_MODE 0
#define GAMEOVER_MODE 1
#define STAGECLEAR_MODE 2
#define RETRY_OR_EXIT_MODE 3
#define NEXT_OR_EXIT_MODE 4

int m_gradTable[][3]=
{
	{255,0,0},
	{255,128,0},
	{255,128,128},
	{255,128,255},
	{128,128,255},
	{128,255,255},
	{  0,255,255},
	{128,128,128},

	{0,0,0},
};

int m_deltaTh[][5]=
{
	{0,},

	{0},
	{-60,60},
	{0,-60,60},
	{-20,20,-60,60},
	{0,-30,30,-60,60},
};

int m_hintColorTable[][3]=
{
	{255,255,255},//white
	{0,0,255},//blue
	{255,0,0},//bred
	{255,0,255},//purp
	{0,255,0},//green
	{0,255,255},//water
	{255,255,0},//yellow
	{255,255,255},//white
	{128,128,128},//grey
};


int m_grad[256][3];

CPlay::CPlay(CGame* lpGame) : CCommonGeneral(lpGame)
{
	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();

	m_bugMax = 20;

	m_pic = new CPicture();
	m_pic->LoadDWQ("sys\\ta_stageclear");

	for (int i=0;i<m_bugMax;i++)
	{
		m_bug[i] = new CBug();
	}

	for (int i=0;i<24;i++)
	{
		m_stageData[i] = new CStageData(i);
	}

	m_startArea = new CArea();
	for (int i=0;i<3;i++)
	{
		m_button[i] = new CArea();
	}
	m_button[0]->SetArea(250,250,100,50);//retry
	m_button[1]->SetArea(250,250,100,50);//next
	m_button[2]->SetArea(450,250,100,50);//exit


	for (int i=0;i<100;i++)
	{
		m_block[i] = new CArea();
	}

	for (int i=0;i<100;i++)
	{
		m_mirror[i] = new CArea();
	}

	for (int i=0;i<100;i++)
	{
		m_target[i] = new CArea();
	}


	for (int k=0;k<8;k++)
	{
		int r0 = m_gradTable[k][0];
		int g0 = m_gradTable[k][1];
		int b0 = m_gradTable[k][2];

		int r1 = m_gradTable[k+1][0];
		int g1 = m_gradTable[k+1][1];
		int b1 = m_gradTable[k+1][2];

		int lp = 16;
		for (int i=0;i<lp;i++)
		{
			int r = r0 + ((r1 - r0) * i) / lp;
			int g = g0 + ((g1 - g0) * i) / lp;
			int b = b0 + ((b1 - b0) * i) / lp;

			m_grad[lp*k+i][0] = r;
			m_grad[lp*k+i][1] = g;
			m_grad[lp*k+i][2] = b;
		}
	}




//	m_printGameStatus = m_game2->GetPrintGameStatus();

//	m_highScoreData = new CHighScoreData();

//	m_stageData = new CNameList();
//	m_stageData->LoadFile("stage.txt");
//
//	m_playClassNumber = 0;

//	m_stage = 0;
//	m_stageKosuu = (m_stageData->GetNameKosuu() / 50)-1;

//	m_game2->SetStageKosuu(m_stageKosuu);

	//load from file
//	m_highScore = m_highScoreData->GetHighScore();
//	m_maxStage = m_highScoreData->GetMaxStage();

//	m_highScore = 12345;
//	m_maxStage = 30;

/*
	m_clearStage = m_game2->GetClearStage();

	for (int i=0;i<10;i++)
	{
		m_mapData[i] = new CMapData(i);
	}

	for (int j=0;j<5;j++)
	{
		for (int i=0;i<3;i++)
		{
			m_demoPlay[j][i] = new CDemoPlay(j,i);
		}
	}

	m_hajike = new CHajike();

	m_pic = new CPicture();
	m_pic->LoadDWQ("sys\\ta_panel");

	m_bg = new CPicture();
	m_bg->LoadDWQ("sys\\bg_mokomoko");

	m_autoDemoTime = 60*300;

	m_mapSizeX = 16;
	m_mapSizeY = 16;

	m_panelSizeX = 32;
	m_panelSizeY = 32;

	m_panelPrintX = 32;
	m_panelPrintY = 64;

	m_panel = new int[(m_mapSizeX+2)*(m_mapSizeY+2)];
	m_panelCount = new int[(m_mapSizeX+2)*(m_mapSizeY+2)];
	m_panelCheck = new int[(m_mapSizeX+2)*(m_mapSizeY+2)];

	m_panelCountMax = 60;
	m_panelSpeed[0] = 2;
	m_panelSpeed[1] = 4;
	m_panelSpeed[2] = 6;
*/

//	m_demoFlag = FALSE;

//	m_printCountDown = new CPrintCountDown();
//	m_printHaikei = new CPrintHaikei();
//	m_printPlate = new CPrintPlate();
//	m_printScore = new CPrintScore();

//	m_printGameStatus = new CPrintGameStatus();

//	m_resultControl = new CResultControl();

//	for (int i=0;i<10;i++)
//	{
//		m_playStageClass[i] = NULL;
//	}

//	m_playStageClass[0] = new CPlayStageType1(m_game2,m_resultControl);
//	m_playStageClass[1] = new CPlayStageType1B(m_game2,m_resultControl);
//	m_playStageClass[2] = new CPlayStageType2(m_game2,m_resultControl);
//	m_playStageClass[3] = new CPlayStageType3(m_game2,m_resultControl);


}

CPlay::~CPlay()
{
	End();
}

void CPlay::End(void)
{
	//save high score

	ENDDELETECLASS(m_pic);

	for (int i=0;i<m_bugMax;i++)
	{
		ENDDELETECLASS(m_bug[i]);
	}

	for (int i=0;i<24;i++)
	{
		ENDDELETECLASS(m_stageData[i]);
	}


	ENDDELETECLASS(m_startArea);

	for (int i=0;i<100;i++)
	{
		ENDDELETECLASS(m_block[i]);
		ENDDELETECLASS(m_target[i]);
		ENDDELETECLASS(m_mirror[i]);
	}

	for (int i=0;i<10;i++)
	{
//		ENDDELETECLASS(m_playStageClass[i]);
	}
//
//	ENDDELETECLASS(m_resultControl);

//	ENDDELETECLASS(m_printGameStatus);
//	ENDDELETECLASS(m_printScore);
//	ENDDELETECLASS(m_printPlate);
//	ENDDELETECLASS(m_printHaikei);
//	ENDDELETECLASS(m_printCountDown);

//	DELETEARRAY(m_panelCheck);
//	DELETEARRAY(m_panelCount);
//	DELETEARRAY(m_panel);
//	ENDDELETECLASS(m_bg);
//	ENDDELETECLASS(m_pic);

//	ENDDELETECLASS(m_hajike);

/*
	for (int j=0;j<5;j++)
	{
		for (int i=0;i<3;i++)
		{
			ENDDELETECLASS(m_demoPlay[j][i]);
		}
	}

	for (int i=0;i<10;i++)
	{
		ENDDELETECLASS(m_mapData[i]);
	}
*/

//	ENDDELETECLASS(m_highScoreData);
}


int CPlay::Init(void)
{
	m_stageNumber = m_game2->GetSelectedStage();

	InitNewStage();


	return -1;
}



int CPlay::Calcu(void)
{
//	if (m_cannotClickCount > 0)
//	{
//		m_cannotClickCount--;
//	}


	m_mirrorSound = 0;
	m_getSound = 0;

//	if (m_mouseStatus->CheckClick(2))
//	{
//		return ReturnFadeOut(GAMETITLE_MODE);
//	}


	if (m_waitClickOff)
	{
		if (m_mouseStatus->GetTrig(0) == 0)
		{
			m_waitClickOff = 0;
		}
		return -1;
	}

	POINT pt = m_mouseStatus->GetZahyo();

	if (m_playMode == GAMEPLAY_MODE)
	{
		if (m_drawingFlag)
		{
			if (m_mouseStatus->GetTrig(0) == 0)
			{
				m_drawingFlag = FALSE;
				m_movingFlag = TRUE;
			}
			else
			{
				if (!CheckInRange(pt,m_lastPoint,4))
				{
					//outofarea?
					if (m_startArea->CheckInArea(pt))
					{
						m_bug[0]->AddPoint(pt);
						//
						m_bug[0]->Start();
						m_bug[0]->CalcuNext(FALSE);
						for (int i=0;i<100;i++)
						{
							m_bug[0]->CalcuNext(TRUE);
						}
						m_lastPoint = pt;
						//limit length?
						if (m_bug[0]->GetTotalLength() > 1500.0f)
						{
							m_drawingFlag = FALSE;
							m_movingFlag = TRUE;
						}
						else
						{
					//		m_game->PlaySystemSound(0);
						}

					}
					else
					{
						m_drawingFlag = FALSE;
						m_movingFlag = TRUE;
					}

				}
			}

			if (m_movingFlag)
			{
				//check short
				if (m_bug[0]->GetTotalLength() < 3.0f)
				{
					m_game->PlaySystemSound(7);

					m_drawingFlag = FALSE;
					m_movingFlag = FALSE;
					m_waitClickOff = 1;
					m_bug[0]->Clear();

				}
			}
		}
		else
		{
			if (m_movingFlag)
			{
				if (m_mouseStatus->GetTrig(1))
				{
					StartRetryOrExitMode();
				}

				//check gameover

				BOOL live = FALSE;
				for (int i=0;i<m_bugMax;i++)
				{
					if (m_bug[i]->GetFlag())
					{
						live = TRUE;
						break;
					}
				}

				if (!live)
				{
					StartGameOverMode();
				}
			}
			else
			{
				if (m_mouseStatus->GetTrig(0))
				{
					//check in
					if (m_startArea->CheckInArea(pt))
					{
						m_startPoint = m_mouseStatus->GetZahyo();
						m_lastPoint = m_startPoint;
						m_bug[0]->Clear();
						m_bug[0]->AddPoint(m_startPoint);
		//				m_bug[0]->Start();


						m_movingFlag = FALSE;
						m_drawingFlag = TRUE;
					}
					else
					{
						m_game->PlaySystemSound(7);
						m_waitClickOff = 1;
					}
				}
			}
		}

		if (m_drawingFlag == FALSE)
		{
			if (m_movingFlag)
			{
				for (int k=0;k<m_bugMax;k++)
				{
					if (m_bug[k]->GetFlag())
					{
						for (int i=0;i<10;i++)
						{
							m_bug[k]->CalcuNext();
							//block death check
							if (!(m_bug[k]->GetDeathFlag()))
							{
								POINT pt = m_bug[k]->GetHeadPoint();
								for (int block=0;block<m_blockNumber;block++)
								{
									if (m_block[block]->CheckInArea(pt))
									{
										m_game->PlaySystemSound(1);
										m_bug[k]->SetDeath();
										break;
									}
								}
							}

							//outofrange
							if (!(m_bug[k]->GetDeathFlag()))
							{
								POINT pt = m_bug[k]->GetHeadPoint();
								if ((pt.x<-800) || (pt.x > 1600) || (pt.y<-600) || (pt.y>1200))
								{
									m_game->PlaySystemSound(1);
									m_bug[k]->SetDeath();
								}

							}

							//ref
							if (!(m_bug[k]->GetDeathFlag()))
							{
								POINT pt = m_bug[k]->GetHeadPoint();
								for (int mirror=0;mirror<m_mirrorNumber;mirror++)
								{
									if (m_mirror[mirror]->CheckInArea(pt))
									{
										int hit = m_mirror[mirror]->CheckKabe(pt,m_mirrorType[mirror]);

										//
										if (hit)
										{
											m_bug[k]->Reflect(m_mirrorType[mirror]);
										}
										else
										{
											m_bug[k]->Reflect(1-m_mirrorType[mirror]);
										}

										m_mirrorSound = 1;
										break;
									}
								}
							}

							//get


							//bunretsu
							if (!(m_bug[k]->GetDeathFlag()))
							{
								POINT pt = m_bug[k]->GetHeadPoint();
								for (int t=0;t<m_targetNumber;t++)
								{
									if (m_targetFlag[t])
									{
										if (m_target[t]->CheckInArea(pt))
										{
											int type = m_targetType[t];
											if (type > 1)
											{
												for (int b=0;b<type-1;b++)
												{
													//search aki
													int found = SearchAkiBug();
													if (found != -1)
													{
														m_bug[found]->AllCopy(m_bug[k]);
														m_bug[found]->Turn(m_deltaTh[type][b+1]);
													}
												}
											}
											m_bug[k]->Turn(m_deltaTh[type][0]);



											//add get effect
											AddGetEffect(m_target[t]->GetRect());


											m_targetFlag[t] = 0;
											m_getSound = 1;

											//check clear
											m_targetNokori--;
											if (m_targetNokori <= 0)
											{
												//clear!!!
												StartClearStage();
											}

										}
									}
								}

							}


						}
					}
				}
			}
		}
	}


	if ((m_playMode == STAGECLEAR_MODE) || (m_playMode == NEXT_OR_EXIT_MODE))
	{
		for (int k=0;k<m_bugMax;k++)
		{
			if (m_bug[k]->GetFlag())
			{
				for (int i=0;i<10;i++)
				{
					m_bug[k]->CalcuNext();
					//block death check
					if (!(m_bug[k]->GetDeathFlag()))
					{
						POINT pt = m_bug[k]->GetHeadPoint();
						for (int block=0;block<m_blockNumber;block++)
						{
							if (m_block[block]->CheckInArea(pt))
							{
//								m_game->PlaySystemSound(1);
								m_bug[k]->SetDeath();
								break;
							}
						}
					}

					//outofrange
					if (!(m_bug[k]->GetDeathFlag()))
					{
						POINT pt = m_bug[k]->GetHeadPoint();
						if ((pt.x<-800) || (pt.x > 1600) || (pt.y<-600) || (pt.y>1200))
						{
//							m_game->PlaySystemSound(1);
							m_bug[k]->SetDeath();
						}
					}

					//ref
					if (!(m_bug[k]->GetDeathFlag()))
					{
						POINT pt = m_bug[k]->GetHeadPoint();
						for (int mirror=0;mirror<m_mirrorNumber;mirror++)
						{
							if (m_mirror[mirror]->CheckInArea(pt))
							{
								int hit = m_mirror[mirror]->CheckKabe(pt,m_mirrorType[mirror]);

								//
								if (hit)
								{
									m_bug[k]->Reflect(m_mirrorType[mirror]);
								}
								else
								{
									m_bug[k]->Reflect(1-m_mirrorType[mirror]);
								}

//								m_mirrorSound = 1;
								break;
							}
						}
					}
				}
			}
		}
	}


	if (m_playMode == STAGECLEAR_MODE)
	{
		m_stageClearCount++;
		if (m_stageClearCount > 180)
		{
			StartNextOrExitMode();
			return -1;
		}
		else
		{
			if (m_mouseStatus->GetTrig(0))
			{
				StartNextOrExitMode();
				return -1;
			}
		}

	}

	if (m_playMode == GAMEOVER_MODE)
	{
		m_gameOverCount++;
		if (m_gameOverCount > 180)
		{
			StartRetryOrExitMode();
			return -1;
		}
		else
		{
			if (m_mouseStatus->GetTrig(0))
			{
				StartRetryOrExitMode();
				return -1;
			}
		}
	}



	if (m_playMode == RETRY_OR_EXIT_MODE)
	{
		if (m_mouseStatus->GetTrig(0))
		{
			if (CheckOnRetryButton(pt))
			{
				InitNewStage();
				return -1;
			}


			if (CheckOnExitButton(pt))
			{
				return GAMETITLE_MODE;
			}
		}
	}

	if (m_playMode == NEXT_OR_EXIT_MODE)
	{
		if (m_mouseStatus->GetTrig(0))
		{
			if (m_stageNumber < 23)
			{
				if (CheckOnNextButton(pt))
				{
					m_stageNumber++;
					InitNewStage();
					return -1;
				}
			}

			if (CheckOnExitButton(pt))
			{
				return GAMETITLE_MODE;
			}

		}

	}


	if (m_getSound)
	{
		m_game->PlaySystemSound(3);
	}
	else if (m_mirrorSound)
	{
		m_game->PlaySystemSound(0);
	}

	if (m_stageClearSound > 0)
	{
		m_stageClearSound--;
		if (m_stageClearSound <= 0)
		{
			m_game->PlaySystemSound(9);
		}
	}


	if (m_gameOverSound > 0)
	{
		m_gameOverSound--;
		if (m_gameOverSound <= 0)
		{
			m_game->PlaySystemSound(8);
		}
	}


	return -1;
}


int CPlay::Print(void)
{
	CAreaControl::SetNextAllPrint();

	CAllGraphics::FillScreen();

	for (int i=0;i<m_blockNumber;i++)
	{
		RECT rc = m_block[i]->GetRect();

		PutBlock(rc);
//		CAllGeo::BoxFill(rc.left,rc.top,rc.right,rc.bottom,255,0,0);
	}

	for (int i=0;i<m_mirrorNumber;i++)
	{
		RECT rc = m_mirror[i]->GetRect();
		PutMirror(rc,m_mirrorType[i]);
//		CAllGeo::BoxFill(rc.left,rc.top,rc.right,rc.bottom,0,255,0);
	}

	if ((m_playMode == GAMEPLAY_MODE) && (m_movingFlag == FALSE))
	{
		PutStartArea(m_startArea->GetRect());
	}

	for (int i=0;i<m_targetNumber;i++)
	{
		if (m_targetFlag[i])
		{
			RECT rc = m_target[i]->GetRect();

			PutTarget(rc,m_targetType[i]);
//			CAllGeo::BoxFill(rc.left,rc.top,rc.right,rc.bottom,0,0,255);
		}
	}

//	m_message->PrintMessage(100,100,"タイトル");

//	char mes[100];
//	sprintf_s(mes,100,"ぽいんと数：%d",ln);
//	m_message->PrintMessage(100,200,mes);

//	if (ln > 0)
//	{
//		POINT p = m_bug[0]->GetPrintPoint(ln-1);
//		sprintf_s(mes,100,"%d：%d",p.x,p.y);
//		m_message->PrintMessage(100,300,mes);
//	}

	for (int k=0;k<m_bugMax;k++)
	{
		int c = 0;
		if (m_bug[k]->GetFlag())
		{
			int ln = m_bug[k]->GetRealPointNumber();
			for (int i=0;i<ln;i+=4)
			{
				POINT pt = m_bug[k]->GetPrintPoint(i);
				int r = m_grad[c][0];
				int g = m_grad[c][1];
				int b = m_grad[c][2];
				c++;
				c %= 128;

				CAllGeo::BoxFill(pt.x-2,pt.y-2,5,5,r,g,b);
			}
		}
	}


	if ((m_playMode == GAMEPLAY_MODE) && (m_movingFlag == FALSE))
	{
		int hintKosuu = m_stageData[m_stageNumber]->GetHintNumber();
		for (int i=0;i<hintKosuu;i++)
		{
			RECT rc = m_stageData[m_stageNumber]->GetHintRect(i);
			LPSTR mes = m_stageData[m_stageNumber]->GetHintMessage(i);
			int fontSize = m_stageData[m_stageNumber]->GetFontSize(i);
			int hintColor = m_stageData[m_stageNumber]->GetHintColor(i);

			int r = m_hintColorTable[hintColor][0];
			int g = m_hintColorTable[hintColor][1];
			int b = m_hintColorTable[hintColor][2];

			m_message->PrintMessage(rc.left,rc.top,mes,fontSize,r,g,b);
		}
	}

	if (m_playMode == STAGECLEAR_MODE)
	{
		m_pic->Put(142,108,TRUE);
	}

	if (m_playMode == GAMEOVER_MODE)
	{
		m_pic->Put(142,108,TRUE);
	}

	if (m_playMode == RETRY_OR_EXIT_MODE)
	{
		PutRetryButton();
		PutExitButton();
	}

	if (m_playMode == NEXT_OR_EXIT_MODE)
	{
		if (m_stageNumber < 23)
		{
			PutNextButton();
		}
		PutExitButton();
	}

	PrintEffect();





	return -1;
}

BOOL CPlay::CheckInRange(POINT pt1,POINT pt2,int range)
{
	int dx = pt1.x - pt2.x;
	int dy = pt1.y - pt2.y;
	if ((dx<-range) || (dx>range) || (dy<-range) || (dy>range)) return FALSE;

	return TRUE;
}

int CPlay::SearchAkiBug(void)
{
	for (int i=0;i<m_bugMax;i++)
	{
		if (m_bug[i]->GetFlag() == FALSE)
		{
			return i;
		}
	}
	return -1;
}

void CPlay::PutBlock(RECT rc)
{
	PutBlock(rc.left,rc.top,rc.right,rc.bottom);
}

void CPlay::PutBlock(POINT pt,SIZE sz)
{
	PutBlock(pt.x,pt.y,sz.cx,sz.cy);
}

void CPlay::PutBlock(int x,int y,int sizeX,int sizeY)
{
	int srcX = 200;
	int srcY = 50;
	int srcSizeX = 100;
	int srcSizeY = 100;
	PutRoutine(x,y,sizeX,sizeY,srcX,srcY,srcSizeX,srcSizeY);
}

void CPlay::PutMirror(RECT rc,int tate)
{
	PutMirror(rc.left,rc.top,rc.right,rc.bottom,tate);
}

void CPlay::PutMirror(POINT pt,SIZE sz,int tate)
{
	PutMirror(pt.x,pt.y,sz.cx,sz.cy,tate);
}

void CPlay::PutMirror(int x,int y,int sizeX,int sizeY,int tate)
{
	int srcX = 100;
	int srcY = 50;
	int srcSizeX = 50;
	int srcSizeY = 100;
	if (tate)
	{
		srcX = 100;
		srcY = 0;
		srcSizeX = 100;
		srcSizeY = 50;
	}

	PutRoutine(x,y,sizeX,sizeY,srcX,srcY,srcSizeX,srcSizeY);
}

void CPlay::PutStartArea(RECT rc)
{
	PutStartArea(rc.left,rc.top,rc.right,rc.bottom);
}

void CPlay::PutStartArea(POINT pt,SIZE sz)
{
	PutStartArea(pt.x,pt.y,sz.cx,sz.cy);
}

void CPlay::PutStartArea(int x,int y,int sizeX,int sizeY)
{
	int srcX = 400;
	int srcY = 0;
	int srcSizeX = 100;
	int srcSizeY = 100;
	if ((sizeX >= 150) || (sizeY >= 150))
	{
		srcX = 500;
		srcY = 0;
		srcSizeX = 200;
		srcSizeY = 200;
	}
	PutRoutine(x,y,sizeX,sizeY,srcX,srcY,srcSizeX,srcSizeY);
}

void CPlay::PutTarget(RECT rc,int type)
{
	PutTarget(rc.left,rc.top,rc.right,rc.bottom,type);
}

void CPlay::PutTarget(POINT pt,SIZE sz,int type)
{
	PutTarget(pt.x,pt.y,sz.cx,sz.cy,type);
}

void CPlay::PutTarget(int x,int y,int sizeX,int sizeY,int type)
{
	int srcSizeX = 25;
	int srcSizeY = 25;
	int srcX = (type-1)*srcSizeX;
	int srcY = 150;
	PutRoutine(x,y,sizeX,sizeY,srcX,srcY,srcSizeX,srcSizeY);
}

void CPlay::PutRetryButton(void)
{
	RECT rc = m_button[0]->GetRect();
	int srcX = 0;
	int srcY = 0;
	int srcSizeX = 100;
	int srcSizeY = 50;
	PutRoutine(rc.left,rc.top,rc.right,rc.bottom,srcX,srcY,srcSizeX,srcSizeY);

}

void CPlay::PutNextButton(void)
{
	RECT rc = m_button[1]->GetRect();
	int srcX = 0;
	int srcY = 50;
	int srcSizeX = 100;
	int srcSizeY = 50;
	PutRoutine(rc.left,rc.top,rc.right,rc.bottom,srcX,srcY,srcSizeX,srcSizeY);
}

void CPlay::PutExitButton(void)
{
	RECT rc = m_button[2]->GetRect();
	int srcX = 0;
	int srcY = 100;
	int srcSizeX = 100;
	int srcSizeY = 50;
	PutRoutine(rc.left,rc.top,rc.right,rc.bottom,srcX,srcY,srcSizeX,srcSizeY);
}


void CPlay::PutRoutine(int x,int y,int sizeX,int sizeY,int srcX,int srcY,int srcSizeX,int srcSizeY,BOOL transFlag)
{
	if ((sizeX == srcSizeX) && (sizeY == srcSizeY))
	{
		m_commonParts->Blt(x,y,srcX,srcY,sizeX,sizeY,transFlag);
	}
	else
	{
		m_commonParts->StretchBlt1(x,y,sizeX,sizeY,srcX,srcY,srcSizeX,srcSizeY);
	}
}

void CPlay::AddGetEffect(RECT rc)
{
	for (int i=0;i<100;i++)
	{
		if (m_effectFlag[i] == 0)
		{
			m_effectFlag[i] = 1;
			m_effectRect[i] = rc;
			m_effectCount[i] = 0;
			return;
		}
	}
}

void CPlay::PrintEffect(void)
{
	for (int i=0;i<100;i++)
	{
		if (m_effectFlag[i])
		{
			int c = m_effectCount[i]++;
			if (c>12)
			{
				m_effectFlag[i] = 0;
			}
			else
			{
				int x = m_effectRect[i].left;
				int y = m_effectRect[i].top;
				int sizeX = m_effectRect[i].right;
				int sizeY = m_effectRect[i].bottom;
				int srcSizeX = 25;
				int srcSizeY = 25;

				int srcX = (c / 2) * srcSizeX;
				int srcY = 175;

				PutRoutine(x,y,sizeX,sizeY,srcX,srcY,srcSizeX,srcSizeY);

			}

		}
	}
}

void CPlay::InitNewStage(void)
{
	m_waitClickOff = 1;
	m_drawingFlag = FALSE;
	m_movingFlag = FALSE;

	m_stageClearSound = 0;
	m_playMode = GAMEPLAY_MODE;


	for (int i=0;i<m_bugMax;i++)
	{
		m_bug[i]->Clear();
	}


	m_blockNumber = m_stageData[m_stageNumber]->GetBlockNumber();
	m_mirrorNumber = m_stageData[m_stageNumber]->GetMirrorNumber();
	m_targetNumber = m_stageData[m_stageNumber]->GetTargetNumber();
//	m_hintNumber = m_stageData[m_stageNumber]->GetHintNumber();
	m_targetNokori = m_targetNumber;

	m_startArea->SetArea(m_stageData[m_stageNumber]->GetStartArea());

	for (int i=0;i<100;i++)
	{
		m_targetFlag[i] = 0;
	}
	for (int i=0;i<m_targetNumber;i++)
	{
		m_targetFlag[i] = 1;
		m_targetType[i] = m_stageData[m_stageNumber]->GetTargetType(i);
		m_target[i]->SetArea(m_stageData[m_stageNumber]->GetTargetRect(i));
	}

	for (int i=0;i<m_blockNumber;i++)
	{
		m_block[i]->SetArea(m_stageData[m_stageNumber]->GetBlockRect(i));
	}


	for (int i=0;i<m_mirrorNumber;i++)
	{
		m_mirror[i]->SetArea(m_stageData[m_stageNumber]->GetMirrorRect(i));
		m_mirrorType[i] = m_stageData[m_stageNumber]->GetMirrorType(i);
	}


	for (int i=0;i<100;i++)
	{
		m_effectFlag[i] = 0;
	}


	m_commonParts->LoadDWQ("sys\\ta_drbugpanel");


}


void CPlay::StartClearStage(void)
{
	m_stageClearSound = 30;

	m_game2->SetSaveData(m_stageNumber,1);//clear!!
	if (m_stageNumber < 23)
	{
		m_pic->LoadDWQ("sys\\ta_stageclear");
	}
	else
	{
		m_pic->LoadDWQ("sys\\ta_complete");
	}

	m_stageClearCount = 0;


	m_waitClickOff = 1;
	m_playMode = STAGECLEAR_MODE;
}

void CPlay::StartRetryOrExitMode(void)
{

	m_waitClickOff = 1;
	m_playMode = RETRY_OR_EXIT_MODE;
}

void CPlay::StartNextOrExitMode(void)
{
	m_waitClickOff = 1;
	m_playMode = NEXT_OR_EXIT_MODE;
}


void CPlay::StartGameOverMode(void)
{
	m_gameOverSound = 10;
	m_pic->LoadDWQ("sys\\ta_gameover");
	m_waitClickOff = 1;
	m_gameOverCount = 0;
	m_playMode = GAMEOVER_MODE;
}


BOOL CPlay::CheckOnRetryButton(POINT pt)
{
	if (m_button[0]->CheckInArea(pt)) return TRUE;

	return FALSE;
}

BOOL CPlay::CheckOnNextButton(POINT pt)
{
	if (m_button[1]->CheckInArea(pt)) return TRUE;

	return FALSE;
}

BOOL CPlay::CheckOnExitButton(POINT pt)
{
	if (m_button[2]->CheckInArea(pt)) return TRUE;

	return FALSE;
}


void CPlay::FinalExitRoutine(void)
{
}





/*_*/


