#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"


#include "soundControl.h"

CSoundControl::CSoundControl()
{
	Clear();
}

CSoundControl::~CSoundControl()
{
	End();
}

void CSoundControl::End(void)
{
}

void CSoundControl::Clear(void)
{
	for (int i=0;i<64;i++)
	{
		m_sound[i] = 0;
	}
}

void CSoundControl::AddSound(int type)
{
	if ((type < 0) || (type >= 64)) return;
	m_sound[type]++;
}

int CSoundControl::GetSound(int type)
{
	if ((type < 0) || (type >= 64)) return 0;
	return m_sound[type];
}



/*_*/



