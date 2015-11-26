

#include <windows.h>
#include <Math.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"
#include "..\..\systemNNN\nyanlib\include\myFile.h"

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

//#include "printGameStatus.h"
#include "gameTitle.h"

#include "game.h"






CGameTitle::CGameTitle(CGame* lpGame) : CCommonGeneral(lpGame)
{
	m_game2 = lpGame;
	m_message = m_game->GetMyMessage();
//	m_printStart = m_game2->GetPrintGameStatus();

//	m_titlePic = new CPicture();
//	m_titlePic->LoadDWQ("sys\\bg_title");
//	m_titlePic->LoadDWQ("sys\\testPattern");
//	SIZE sz = m_titlePic->GetPicSize();

//	m_startPicSizeX = 512;
//	m_startPicSizeY = 384;

//	m_clearStage = m_game2->GetClearStage();
//	m_stage = 0;
//
//	m_stageMax = 10;

//	m_starX = 1200;
//	m_starY = 300;
//	m_starTargetX = 400;
//	m_starTargetY = 300;
//	m_starMoveMode = 0;
	m_buttonPrintX = 400;
	m_buttonPrintY = 300;
	m_buttonNextX = 80;
	m_buttonNextY = 60;
	m_buttonSizeX = 70;
	m_buttonSizeY = 50;

	m_waveCount = 0;
	m_waveMax = 100;
	m_waveSize = 35;
	m_waveStart = 30;
}



CGameTitle::~CGameTitle()
{
	End();
}

void CGameTitle::End(void)
{
//	ENDDELETECLASS(m_titlePic);
}


int CGameTitle::Init(void)
{
	m_commonBG->LoadDWQ("bg\\bg_nekosi_open");
	m_commonParts->LoadDWQ("sys\\ta_drbugpanel");


	for (int i=0;i<25;i++)
	{
		m_selectOk[i] = 0;
		m_clear[i] = m_game2->GetSaveData(i);
	}

	m_selectOk[24] = 1;
	for (int i=0;i<24;i++)
	{
		if (m_clear[i] == 0)
		{
			m_selectOk[24] = 0;
			break;
		}
	}

#if _DEBUG
	m_selectOk[24] = 1;
#endif

	m_selectOk[0] = 1;
	for (int i=1;i<24;i++)
	{
		if (m_clear[i])
		{
			m_selectOk[i] = 1;
		}
		if (m_clear[i-1])
		{
			m_selectOk[i] = 1;
		}
		if (i >= 5)
		{
			if (m_clear[i-5])
			{
				m_selectOk[i] = 1;
			}
		}
	}

	for (int i=0;i<25;i++)
	{
		m_deltaXY[i].x = 0;
		m_deltaXY[i].y = 0;
		m_multi[i].cx = 100;
		m_multi[i].cy = 100;
	}

	m_waveCount = 0;
	m_waveSpeed = 1;

	m_nowOnButton = -1;

	return -1;
}

int CGameTitle::Calcu(void)
{
	int r = rand();
	CalcuWave();


	POINT pt = m_mouseStatus->GetZahyo();
	int old = m_nowOnButton;
	int on = GetOnButton(pt);
	m_nowOnButton = -1;

	if (on != -1)
	{
		if (m_selectOk[on])
		{
			m_nowOnButton = on;
			if (on != old)
			{
				//reset effect

				m_game->PlaySystemSound(4);
			}
		}
	}


	if (m_mouseStatus->CheckClick(0))
	{
		if (m_nowOnButton != -1)
		{
			if (m_nowOnButton < 24)
			{
				m_game->PlaySystemSound(10);
				m_game2->SetSelectedStage(m_nowOnButton);
				return ReturnFadeOut(PLAY_MODE);
			}
			else
			{
				//free draw tool mode
				return ReturnFadeOut(NEKOPIC_MODE);
			}
		}
		else
		{
			m_game->PlaySystemSound(7);
		}
	}


	return -1;
}

int CGameTitle::Print(void)
{
	CAreaControl::SetNextAllPrint();

//	CAllGraphics::FillScreen();

	m_commonBG->Put(0,0);


	for (int j=0;j<5;j++)
	{
		for (int i=0;i<5;i++)
		{
			int k = i + j * 5;
			int x = m_buttonPrintX + m_buttonNextX * i;
			int y = m_buttonPrintY + m_buttonNextY * j;
			int md = 0;

			int sizeX = m_buttonSizeX;
			int sizeY = m_buttonSizeY;
			int srcSizeX = sizeX;
			int srcSizeY = sizeY;

			x += m_deltaXY[k].x;
			y += m_deltaXY[k].y;

			sizeX *= m_multi[k].cx;
			sizeY *= m_multi[k].cy;
			sizeX /= 100;
			sizeY /= 100;

			int srcX =       m_buttonSizeX * i;
			int srcY = 200 + m_buttonSizeY * j;

			if (m_selectOk[k] == 0)
			{
				m_commonParts->GreyBlt(x,y,srcX,srcY,sizeX,sizeY);
			}
			else
			{
				if (k == m_nowOnButton)
				{
					int deltaSizeX = 10;//dummy
					int deltaSizeY = 10;

					x -= deltaSizeX / 2;
					y -= deltaSizeY / 2;
					sizeX += deltaSizeX;
					sizeY += deltaSizeY;


					m_commonParts->StretchBlt1(x,y,sizeX,sizeY,srcX,srcY,srcSizeX,srcSizeY);
				}
				else
				{
					m_commonParts->Blt(x,y,srcX,srcY,sizeX,sizeY,TRUE);
				}
			}

			//clear mark
			if (m_clear[k])
			{
				m_commonParts->Blt(x,y,0,150,25,25,TRUE);
			}
		}
	}


//	m_commonParts->Put(0,0,TRUE);



	return -1;
}

void CGameTitle::CalcuWave(void)
{
	m_waveCount += m_waveSpeed;
	if (m_waveCount <0)
	{
		m_waveCount = 0;
		m_waveSpeed = 1;
	}
	else if (m_waveCount >= m_waveMax)
	{
		m_waveCount = m_waveMax-1;
		m_waveSpeed = -1;
	}

	for (int i=0;i<25;i++)
	{
		m_deltaXY[i].x = 0;
		m_deltaXY[i].y = 0;
	}

	for (int i=0;i<5;i++)
	{
		int k = m_waveCount + i*5;
		if (k>=m_waveStart)
		{
			k -= m_waveStart;
			if (k<m_waveSize)
			{
				float th = (float)k;
				th /= (float)m_waveSize;
				th *= 3.14159f * 2.0f;
				float dy = sin(th) * 8.0f;
				for (int j=0;j<5;j++)
				{
					if (m_selectOk[i+j*5])
					{
						m_deltaXY[i+j*5].y = (int)(dy+0.5f);
					}
				}
			}
		}
	}


}

int CGameTitle::GetOnButton(POINT pt)
{
	int x = pt.x - m_buttonPrintX;
	int y = pt.y - m_buttonPrintY;
	if ((x<0) || (y<0)) return -1;
	int nx = x / m_buttonNextX;
	int ny = y / m_buttonNextY;
	if ((nx>=5) || (ny>=5)) return -1;
	int ax = x % m_buttonNextX;
	int ay = y % m_buttonNextY;
	if ((ax>=m_buttonSizeX) || (ay >= m_buttonSizeY)) return -1;
	return nx + ny * 5;
}


void CGameTitle::FinalExitRoutine(void)
{
}



/*_*/


