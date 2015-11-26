

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

#include "nekoPic.h"

#include "area.h"
#include "stageData.h"

#include "game.h"

int m_bugSpeedTable[3] = {17,10,6};
int m_bugLengthTable[3] = {1000,500,300};
int m_bugSizeTable[3] = {7,5,3};


int m_gradTable0[9][16][3]=
{
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
	},

	{
		{60,60,60},
		{100,100,100},
		{140,140,140},
		{192,192,192},
		{255,255,255},
		{192,192,192},
		{128,128,128},
		{60,60,60},

		{0,0,0},
	},

	{
		{94,255,255,},
		{64,255,178,},
		{124,255,225,},
		{64,225,255,},
		{64,225,255,},
		{64,255,255,},
		{64,255,225,},
		{94,255,255,},
		{94,255,255,},

		{0,0,0},
	},

	{
		{64,255,32},
		{64,255,62},
		{84,255,62},
		{84,255,32},
		{64,255,32},
		{64,205,32},
		{94,225,32},
		{124,255,32},
		{94,255,32},

		{0,0,0},
	},

	{
		{255,64,64},
		{192,64,64},
		{192,64,94},
		{165,64,124},
		{195,64,94},
		{255,34,64},
		{255,34,64},
		{255,64,64},
		{255,64,64},

		{0,0,0},
	},

	{
		{255,200,32},
		{255,200,62},
		{255,200,92},
		{255,230,62},
		{255,230,32},
		{215,200,32},
		{175,200,32},
		{215,200,32},
		{255,200,32},

		{0,0,0},
	},

	{
		{255,255,192},
		{255,255,255},
		{255,255,255},
		{192,255,255},
		{255,255,255},
		{255,255,255},
		{255,255,255},
		{255,192,255},
		{255,255,255},

		{0,0,0},
	},

	{
		{32,64,255},
		{32,64,255},
		{32,64,255},
		{32,64,193},
		{32,64,255},
		{32,32,255},
		{32,32,255},
		{96,64,255},
		{32,64,255},

		{0,0,0},
	},

	{
		{255,158,32},
		{255,128,32},
		{245,128,92},
		{245,128,92},
		{235,128,92},
		{235,128,32},
		{245,128,32},
		{245,158,32},
		{255,158,32},

		{0,0,0},
	},

};

int m_buttonTable[18][6]=
{
	{20,0,  0,500,  0,0},
	{100,0, 50,500, 0,1},
	{180,0, 100,500,0,2},

	{295,0, 150,500, 1,0},
	{375,0, 200,500, 1,1},
	{435,0, 250,500, 1,2},

	{570,0, 300,500, 2,0},
	{650,0, 350,500, 2,1},
	{730,0, 400,500, 2,2},

	{ 80,550, 0,550, 3,0},
	{160,550, 50,550, 3,1},
	{240,550, 100,550, 3,2},
	{320,550, 150,550, 3,3},
	{400,550, 200,550, 3,4},
	{480,550, 250,550, 3,5},
	{560,550, 300,550, 3,6},
	{640,550, 350,550, 3,7},
	{720,550, 400,550, 3,8},

};


int m_grads[9][256][3];



CNekoPic::CNekoPic(CGame* lpGame) : CCommonGeneral(lpGame)
{
	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();

	m_stageData = new CStageData(24);

	m_mirrorNumber = m_stageData->GetMirrorNumber();
	for (int i=0;i<m_mirrorNumber;i++)
	{
		m_mirror[i] = new CArea();
		m_mirror[i]->SetArea(m_stageData->GetMirrorRect(i));
		m_mirrorType[i] = m_stageData->GetMirrorType(i);
	}

	m_bugMax = 20;

	m_buttonEffectCount = 0;

	for (int i=0;i<m_bugMax;i++)
	{
		m_bug[i] = new CBug();
	}

	for (int col=0;col<9;col++)
	{
		for (int k=0;k<8;k++)
		{
			int r0 = m_gradTable0[col][k][0];
			int g0 = m_gradTable0[col][k][1];
			int b0 = m_gradTable0[col][k][2];

			int r1 = m_gradTable0[col][k+1][0];
			int g1 = m_gradTable0[col][k+1][1];
			int b1 = m_gradTable0[col][k+1][2];

			int lp = 16;
			for (int i=0;i<lp;i++)
			{
				int r = r0 + ((r1 - r0) * i) / lp;
				int g = g0 + ((g1 - g0) * i) / lp;
				int b = b0 + ((b1 - b0) * i) / lp;

				m_grads[col][lp*k+i][0] = r;
				m_grads[col][lp*k+i][1] = g;
				m_grads[col][lp*k+i][2] = b;
			}
		}
	}

}

CNekoPic::~CNekoPic()
{
	End();
}

void CNekoPic::End(void)
{
	ENDDELETECLASS(m_stageData);
	for (int i=0;i<m_mirrorNumber;i++)
	{
		ENDDELETECLASS(m_mirror[i]);
	}

	for (int i=0;i<m_bugMax;i++)
	{
		ENDDELETECLASS(m_bug[i]);
	}

}


int CNekoPic::Init(void)
{
	m_commonParts->LoadDWQ("sys\\ta_drbugpanel");
	m_buttonFlag = TRUE;

	m_firstClick = FALSE;

	for (int i=0;i<m_bugMax;i++)
	{
		m_bug[i]->Clear();

		m_bugSpeed[i] = 1;
		m_bugColor[i] = 1;
		m_bugLength[i] = 1;
		m_bugSize[i] = 1;
	}


	m_nowSelectBug = 0;
	m_waitClickOff = 1;

	return -1;
}

int CNekoPic::Calcu(void)
{
	if (m_mouseStatus->GetTrig(2)) return GAMETITLE_MODE;


	if (m_waitClickOff)
	{
		if (m_mouseStatus->GetTrig(0) == 0)
		{
			m_waitClickOff = 0;
		}
		return -1;
	}

	if (m_mouseStatus->GetTrig(0))
	{
		m_firstClick = TRUE;
	}

	if (m_mouseStatus->CheckClick(1))
	{
		m_buttonFlag = !m_buttonFlag;
	}

	POINT pt = m_mouseStatus->GetZahyo();

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
				m_bug[m_nowSelectBug]->AddPoint(pt);
						//
				m_bug[m_nowSelectBug]->Start();
				m_bug[m_nowSelectBug]->CalcuNext(FALSE);
				for (int i=0;i<100;i++)
				{
					m_bug[m_nowSelectBug]->CalcuNext(TRUE);
				}
				m_lastPoint = pt;
				//limit length?
				if (m_bug[m_nowSelectBug]->GetTotalLength() > 1500.0f)
				{
					m_drawingFlag = FALSE;
					m_movingFlag = TRUE;
				}
			}
			else
			{
		//		m_drawingFlag = FALSE;
		//		m_movingFlag = TRUE;
			}
		}

		if (m_movingFlag)
		{
			//check short
			if (m_bug[m_nowSelectBug]->GetTotalLength() < 3.0f)
			{
				m_drawingFlag = FALSE;
				m_movingFlag = FALSE;
				m_waitClickOff = 1;
				m_bug[m_nowSelectBug]->Clear();
				m_bug[m_nowSelectBug]->SetRealPrintLength(m_bugLengthTable[m_bugLength[m_nowSelectBug]]);
			}
			else
			{
				m_nowSelectBug++;
				m_nowSelectBug %= m_bugMax;
			}
		}
	}
	else
	{
		if (m_mouseStatus->GetTrig(0))
		{
			//check button
			BOOL btn = FALSE;

			if (m_buttonFlag)
			{
				for (int i=0;i<18;i++)
				{
					if (CheckOnButton(i,pt))
					{
						int type = m_buttonTable[i][4];
						int sub = m_buttonTable[i][5];
						if (type == 0)
						{
							m_bugLength[m_nowSelectBug] = sub;
						}
						else if (type == 1)
						{
							m_bugSize[m_nowSelectBug] = sub;
						}
						else if (type == 2)
						{
							m_bugSpeed[m_nowSelectBug] = sub;
						}
						else if (type == 3)
						{
							m_bugColor[m_nowSelectBug] = sub;
						}

						btn = TRUE;
						break;
					}
				}
			}

			if (btn == FALSE)
			{
				m_startPoint = m_mouseStatus->GetZahyo();
				m_lastPoint = m_startPoint;
				m_bug[m_nowSelectBug]->Clear();
				m_bug[m_nowSelectBug]->SetRealPrintLength(m_bugLengthTable[m_bugLength[m_nowSelectBug]]);
				m_bug[m_nowSelectBug]->AddPoint(m_startPoint);
			//				m_bug[0]->Start();


				m_movingFlag = FALSE;
				m_drawingFlag = TRUE;
			}
		}
	}

	for (int k=0;k<m_bugMax;k++)
	{
		if (k != m_nowSelectBug)
		{
			if (m_bug[k]->GetFlag())
			{
				int speed = m_bugSpeedTable[m_bugSpeed[k]];

				for (int i=0;i<speed;i++)
				{
					m_bug[k]->CalcuNext();

					//outofrange
					if (!(m_bug[k]->GetDeathFlag()))
					{
						POINT pt = m_bug[k]->GetHeadPoint();
						if ((pt.x<-800) || (pt.x > 1600) || (pt.y<-600) || (pt.y>1200))
						{
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

//										m_mirrorSound = 1;
								break;
							}
						}
					}
				}
			}
		}
	}



	return -1;
}


int CNekoPic::Print(void)
{
	CAreaControl::SetNextAllPrint();
	CAllGraphics::FillScreen();


	for (int i=0;i<m_mirrorNumber;i++)
	{
		RECT rc = m_mirror[i]->GetRect();
		PutMirror(rc,m_mirrorType[i]);
	}

	for (int k=0;k<m_bugMax;k++)
	{
		int c = 0;
		if (m_bug[k]->GetFlag())
		{
			int ln = m_bug[k]->GetRealPointNumber();


			int col = m_bugColor[k];
			int size = m_bugSizeTable[m_bugSize[k]];
			int offset = size / 2;
			int skip = size-1;

			for (int i=0;i<ln;i+=skip)
			{
				POINT pt = m_bug[k]->GetPrintPoint(i);

				int r = m_grads[col][c][0];
				int g = m_grads[col][c][1];
				int b = m_grads[col][c][2];
				c++;
				c %= 128;

				CAllGeo::BoxFill(pt.x-offset,pt.y-offset,size,size,r,g,b);
			}
		}
	}

	if (m_buttonFlag)
	{
		m_buttonEffectCount++;
		m_buttonEffectCount %= 60;
		float th = (float)m_buttonEffectCount;
		th /= 60.0f;
		th *= 3.14159f * 2.0f;
		int delta = (int)(sin(th) * 5);

		for (int i=0;i<18;i++)
		{
			int x = m_buttonTable[i][0];
			int y = m_buttonTable[i][1];
			int srcX = m_buttonTable[i][2];
			int srcY = m_buttonTable[i][3];
			int type = m_buttonTable[i][4];
			int sub = m_buttonTable[i][5];

			int sizeX = 50;
			int sizeY = 50;
			int srcSizeX = sizeX;
			int srcSizeY = sizeY;

			BOOL flg = FALSE;

			if (type == 0)
			{
				if (m_bugLength[m_nowSelectBug] == sub) flg = TRUE;
			}
			else if (type == 1)
			{
				if (m_bugSize[m_nowSelectBug] == sub) flg = TRUE;
			}
			else if (type == 2)
			{
				if (m_bugSpeed[m_nowSelectBug] == sub) flg = TRUE;
			}
			else
			{
				if (m_bugColor[m_nowSelectBug] == sub) flg = TRUE;
			}

			if (flg)
			{
				sizeX += delta*2;
				sizeY += delta*2;
				x -= delta;
				y -= delta;
			}

			PutRoutine(x,y,sizeX,sizeY,srcX,srcY,srcSizeX,srcSizeY);
		}
	}

	if (!m_firstClick)
	{
		m_message->PrintMessage(300,400,"”Lƒ^[ƒgƒ‹‚¨ŠG‚©‚«");
	}

	return -1;
}


void CNekoPic::FinalExitRoutine(void)
{
}


void CNekoPic::PutMirror(RECT rc,int tate)
{
	PutMirror(rc.left,rc.top,rc.right,rc.bottom,tate);
}

void CNekoPic::PutMirror(POINT pt,SIZE sz,int tate)
{
	PutMirror(pt.x,pt.y,sz.cx,sz.cy,tate);
}

void CNekoPic::PutMirror(int x,int y,int sizeX,int sizeY,int tate)
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

void CNekoPic::PutRoutine(int x,int y,int sizeX,int sizeY,int srcX,int srcY,int srcSizeX,int srcSizeY,BOOL transFlag)
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


BOOL CNekoPic::CheckInRange(POINT pt1,POINT pt2,int range)
{
	int dx = pt1.x - pt2.x;
	int dy = pt1.y - pt2.y;
	if ((dx<-range) || (dx>range) || (dy<-range) || (dy>range)) return FALSE;

	return TRUE;
}


BOOL CNekoPic::CheckOnButton(int n,POINT pt)
{

	int bx = m_buttonTable[n][0];
	int by = m_buttonTable[n][1];
	int x = pt.x - bx;
	int y = pt.y - by;
	if ((x>=0) && (x<50) && (y>=0) && (y<50)) return TRUE;

	return FALSE;

}

/*_*/


