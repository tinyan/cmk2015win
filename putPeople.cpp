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
	int anime = 0;

	m_people[type]->Put(x,y,anime,pic);
}


void CPutPeople::PutItem(int x,int y,int pl,int type,int item,int houkou)
{
	if (houkou == -1)
	{
		houkou = pl;
	}

	if (item != -1)
	{
		m_equipPic->Put(x,y,pl,item,type,houkou);
	}
}

void CPutPeople::PutLife(int x,int y,int type,int life,int lifeMax)
{
}




/*_*/



