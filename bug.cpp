//
//
//

#include <windows.h>
#include <Math.h>

#include "..\..\systemNNN\nyanLib\include\commonMacro.h"

#include "bug.h"






CBug::CBug()
{
	m_pointMax = 256;
	m_point = new float[m_pointMax*2];
	m_angle = new float[m_pointMax*2];
	m_length = new float[m_pointMax*2];

	for (int i=0;i<m_pointMax;i++)
	{
		m_point[i*2+0] = 0;
		m_point[i*2+1] = 0;

		m_angle[i*2+0] = 0;
		m_angle[i*2+1] = 0;

		m_length[i*2+0] = 1;
		m_length[i*2+1] = 1;
	}

	m_realPointMax = 2048;
	m_realPoint = new float[m_realPointMax*2];
	m_realPointInt = new int[m_realPointMax*2];

	m_realPointPrintLength = 500;

	for (int i=0;i<m_realPointMax;i++)
	{
		m_realPoint[i*2+0] = 0;
		m_realPoint[i*2+1] = 0;
		m_realPointInt[i*2+0] = 0;
		m_realPointInt[i*2+1] = 0;
	}

	Clear();
}

CBug::~CBug()
{
	End();
}

void CBug::End(void)
{
	DELETEARRAY(m_point);
	DELETEARRAY(m_angle);
	DELETEARRAY(m_length);
	DELETEARRAY(m_realPoint);
	DELETEARRAY(m_realPointInt);
}

void CBug::Clear(void)
{
	m_pointNumber = 0;
	m_pointPointer = 0;
	m_lengthTotal = 0;
	m_startFlag = FALSE;

	m_realPointNumber = 0;
	m_realPointPointer = 0;
	m_usedLength = 0;
	m_flag = FALSE;
	m_deathFlag = FALSE;
	m_life = -1;
}

BOOL CBug::AddPoint(POINT pt)
{
	return AddPoint((float)(pt.x),(float)(pt.y));
}

BOOL CBug::AddPoint(float x ,float y)
{
	if (m_pointNumber >= m_pointMax)
	{
		return FALSE;
	}

	if (m_deathFlag) return FALSE;

	if (m_pointNumber > 0)
	{
		float x0 = m_point[(m_pointNumber-1)*2+0];
		float y0 = m_point[(m_pointNumber-1)*2+1];

		if ((x0 == x) && (y0 == y)) return FALSE;


		float angle = atan2(y-y0,x-x0);
		m_angle[(m_pointNumber-1)*2+0] = angle;
		if (m_pointNumber > 1)
		{
			float a = m_angle[(m_pointNumber-1)*2+0] - m_angle[(m_pointNumber-2)*2+0];
			a = AdjustAngle(a);
			m_angle[(m_pointNumber-1)*2+1] = a;
		}
		else
		{
			m_angle[(m_pointNumber-1)*2+1] = 0;
		}

		float ln = sqrt((x-x0)*(x-x0) + (y-y0)*(y-y0));
		m_length[(m_pointNumber-1)*2+0] = m_lengthTotal;
		m_length[(m_pointNumber-1)*2+1] = ln;
		m_lengthTotal += ln;
	}

	m_point[m_pointNumber*2+0] = x;
	m_point[m_pointNumber*2+1] = y;

	m_pointNumber++;

	return TRUE;
}

BOOL CBug::Start(int life)
{
	if (m_startFlag) return FALSE;
	m_startFlag = TRUE;
	m_deathFlag = FALSE;
	m_life = life;
	m_flag =TRUE;

	m_realAngle = 0;
	if (m_pointNumber > 0)
	{
		m_realAngle = m_angle[0*2+0];
	}

	m_realPointNumber = 1;
	m_realPointPointer = 0;
	m_usedLength = 0;

	m_realPoint[0*2+0] = m_point[0*2+0];
	m_realPoint[0*2+1] = m_point[0*2+1];
	m_realPointInt[0*2+0] = (int)(m_realPoint[0*2+0]+0.5f);
	m_realPointInt[0*2+1] = (int)(m_realPoint[0*2+1]+0.5f);

//	Calcu(m_realPointPrintLength);

	return TRUE;
}

BOOL CBug::CalcuNext(BOOL limitFlag)
{
	if (!m_flag) return FALSE;

	float ln = GetNowLength();
	if (limitFlag)
	{
		if ((ln-m_usedLength) <= 1.0f) return FALSE;
	}


	if (m_deathFlag)
	{
		m_realPointPointer++;
		m_realPointPointer %= m_realPointMax;
		m_realPointNumber--;
		if (m_realPointNumber <= 1)
		{
			m_flag = FALSE;
		}

		return TRUE;
	}

	if (m_life >0)
	{
		m_life--;
		if (m_life == 0)
		{
			m_deathFlag = TRUE;
			return FALSE;
		}
	}

//OutputDebugString("@");

//	float angle = GetNowAngle();

	float vx = cos(m_realAngle);
	float vy = sin(m_realAngle);


	m_usedLength += 1.0f;
	if (m_usedLength >= ln)
	{
	//	OutputDebugString("next from point\n");
		//nextpoint
		float amari = m_usedLength - ln;
		vx *= (1.0f - amari);
		vy *= (1.0f - amari);


		//new point
		m_usedLength = amari;
		m_pointPointer++;
		if (m_pointPointer >= m_pointNumber-1)
		{
			m_pointPointer = 0;
		}
		m_realAngle += GetNowDeltaAngle();
		m_realAngle = AdjustAngle(m_realAngle);

		float dx = cos(m_realAngle);
		float dy = sin(m_realAngle);
		vx += dx * m_usedLength;
		vy += dy * m_usedLength;
	}

	int tail = GetRealTailPointer();

	float x = m_realPoint[tail*2+0];
	float y = m_realPoint[tail*2+1];
	x += vx;
	y += vy;
	m_calcuedX = x;
	m_calcuedY = y;
	
	if (m_realPointNumber >= m_realPointPrintLength)
	{
		m_realPointPointer++;
		m_realPointPointer %= m_realPointMax;
	}
	else
	{
		m_realPointNumber++;
	}

	int tail2 = GetRealTailPointer();


	m_realPoint[tail2*2+0] = x;
	m_realPoint[tail2*2+1] = y;
	m_realPointInt[tail2*2+0] = (int)(x+0.5f);
	m_realPointInt[tail2*2+1] = (int)(y+0.5f);


	m_calcuedAngle = m_realAngle;

	return TRUE;
}

int CBug::GetRealTailPointer(void)
{
	int n = m_realPointPointer;
	n += m_realPointNumber;
	n -= 1;
	n += m_realPointMax;
	n %= m_realPointMax;
	return n;
}

float CBug::AdjustAngle(float angle)
{
	if (angle > 3.14159f)
	{
		angle -= 3.14159f * 2.0f;
	}
	else if (angle < -3.14159f)
	{
		angle += 3.14159f * 2.0f;
	}
	return angle;
}

float CBug::GetNowLength(void)
{
	if (m_pointNumber <= 0) return 1;//error!!

	return m_length[m_pointPointer*2+1];
}

float CBug::GetNowAngle(void)
{
	if (m_pointNumber <= 0) return 0;//error!!

	return m_angle[m_pointPointer*2];
}

float CBug::GetNowDeltaAngle(void)
{
	if (m_pointNumber <= 0) return 0;//error!!

	return m_angle[m_pointPointer*2+1];
}



void CBug::Calcu(int count)
{
	for (int i=0;i<count;i++)
	{
		CalcuNext();
	}
}


void CBug::AllCopy(CBug* from)
{
	m_pointNumber = from->GetPointNumber();
	m_lengthTotal = from->GetTotalLength();
	m_pointPointer = from->GetPointPointer();
	m_usedLength = from->GetUsedLength();

	float* lpPoint = from->GetPoint();
	for (int i=0;i<m_pointNumber;i++)
	{
		m_point[i*2+0] = lpPoint[i*2+0];
		m_point[i*2+1] = lpPoint[i*2+1];
	}

	float* lpAngle = from->GetAngle();
	for (int i=0;i<m_pointNumber;i++)
	{
		m_angle[i*2+0] = lpAngle[i*2+0];
		m_angle[i*2+1] = lpAngle[i*2+1];
	}

	float* lpLength = from->GetLength();
	for (int i=0;i<m_pointNumber;i++)
	{
		m_length[i*2+0] = lpLength[i*2+0];
		m_length[i*2+1] = lpLength[i*2+1];
	}

	m_realPointNumber = from->GetRealPointNumber();
	m_realPointPointer = from->GetRealPointPointer();
	m_realAngle = from->GetRealAngle();


	m_calcuedX = from->GetCalcuedX();
	m_calcuedY = from->GetCalcuedY();
	m_calcuedAngle = from->GetCalcuedAngle();


	int k = m_realPointPointer;
	float* lpReal = from->GetRealPoint();
	int* lpRealInt = from->GetRealPointInt();
	for (int i=0;i<m_realPointNumber;i++)
	{
		m_realPoint[k*2+0] = lpReal[k*2+0];
		m_realPoint[k*2+1] = lpReal[k*2+1];

		m_realPointInt[k*2+0] = lpRealInt[k*2+0];
		m_realPointInt[k*2+1] = lpRealInt[k*2+1];

		k++;
		k %= m_realPointMax;
	}

	m_startFlag = from->GetStartFlag();
	m_flag = from->GetFlag();
	m_deathFlag = from->GetDeathFlag();
	m_life = from->GetLife();

}

POINT CBug::GetHeadPoint(void)
{
	return GetPrintPoint(m_realPointNumber-1);
}


POINT CBug::GetPrintPoint(int k)
{
	POINT pt;

	int n = m_realPointPointer;
	n += k;
	n %= m_realPointMax;
	pt.x = m_realPointInt[n*2+0];
	pt.y = m_realPointInt[n*2+1];

	return pt;
}

void CBug::SetDeath(void)
{
	m_deathFlag = TRUE;
}

void CBug::Reflect(int tate)
{
	float dx = cos(m_realAngle);
	float dy = sin(m_realAngle);
	if (tate)
	{
		dy *= -1;
	}
	else
	{
		dx *= -1;
	}
	m_realAngle = atan2(dy,dx);
	m_calcuedAngle = m_realAngle;

	if (m_realPointNumber >= 2)
	{
		int from = m_realPointPointer + m_realPointNumber;
		from -= 2;
		from += m_realPointMax;
		from %= m_realPointMax;

		int to = m_realPointPointer + m_realPointNumber;
		to -= 1;
		to += m_realPointMax;
		to %= m_realPointMax;

		m_realPointInt[to*2+0] = m_realPointInt[from*2+0];
		m_realPointInt[to*2+1] = m_realPointInt[from*2+1];
		m_realPoint[to*2+0] = m_realPoint[from*2+0];
		m_realPoint[to*2+1] = m_realPoint[from*2+1];
	}
}

void CBug::Turn(int angle)
{
	float th = (float)angle;
	th *= 3.14159f / 180.0f;
	m_realAngle += th;
	m_realAngle = AdjustAngle(m_realAngle);

	m_calcuedAngle = m_realAngle;
}

/*_*/

