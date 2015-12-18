#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"
#include "..\..\systemNNN\nyanlib\include\allGraphics.h"

#include "..\..\systemNNN\nnnUtilLib\systempicture.h"

#include "putChara.h"

#include "putEquip.h"

POINT CPutEquip::m_delta[2][4]=
{
	{
		{16,-8},
		{-16,-8},
		{0,0},
		{0,0},
	},

	{
		{-16,-8},
		{16,-8},
		{0,0},
		{0,0},
	},
};

CPutEquip::CPutEquip()
{
	m_equipPic = new CPutChara("sys\\ta_equip",4,2);
}

CPutEquip::~CPutEquip()
{
	End();
}

void CPutEquip::End(void)
{
	ENDDELETECLASS(m_equipPic);
}

void CPutEquip::Put(int x,int y,int pl,int pic,int type,int houkou)
{
	int dx = m_delta[houkou][type].x;
	int dy = m_delta[houkou][type].y;
	m_equipPic->Put(x+dx,y+dy,pic,pl);

}



/*_*/



