#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"


#include "putChara.h"
#include "putEquip.h"
#include "putPeople.h"


CPutPeople::CPutPeople()
{
	m_people[0] = new CPutChara("sys\\ta_people",16,16);
	m_people[1] = new CPutChara("sys\\ta_enemy",16,16);
	m_equipPic = new CPutEquip();

	m_peopleAnime = 0;
	m_itemAnime = 0;

	m_peopleDeltaX = 0;
	m_peopleDeltaY = 0;
	m_itemDeltaX = 0;
	m_itemDeltaY = 0;
	m_peopleAnimePattern = 0;
}

CPutPeople::~CPutPeople()
{
	End();
}

void CPutPeople::End(void)
{
	ENDDELETECLASS(m_equipPic);
	for (int i=0;i<2;i++)
	{
		ENDDELETECLASS(m_people[i]);
	}
}


void CPutPeople::Put(int x,int y,int type,int pic,int houkou)
{
	int anime = m_peopleAnimePattern;

	m_people[type]->Put(x+m_peopleDeltaX,y+m_peopleDeltaY,anime,pic);
}


void CPutPeople::PutItem(int x,int y,int pl,int type,int item,int houkou)
{
	if (houkou == -1)
	{
		houkou = pl;
	}

	if (item != -1)
	{
		m_equipPic->Put(x+m_itemDeltaX,y+m_itemDeltaY,pl,item,type,houkou);
	}
}

void CPutPeople::PutLife(int x,int y,int type,int life,int lifeMax)
{
}

void CPutPeople::CalcuAnime(void)
{
	m_peopleAnime++;
	m_peopleAnime %= 32;
	m_itemAnime++;
	m_itemAnime %= 40;

	int p1 = m_peopleAnime / 8;
	int p2 = m_itemAnime / 10;
	int table1[] = {0,1,0,-1};
	int table2[] = {0,1,0,-1};

	m_peopleAnimePattern = p1;
//	m_peopleDeltaY = table1[p1];
	m_itemDeltaY = table2[p2];
}



/*_*/



