#include "stdafx.h"
#include "Ship.h"


Ship::Ship()
{
	memset(m_Pos, 0, sizeof(m_Pos)*MAX_SHIP_LENGTH);
}


Ship::~Ship()
{
}


void Ship::AddPosition(Position Pos)
{
	
	// pos�� ���� �ʾ��� ��쿡 ���� ������ ÷���ؾ� ������

	/*if (m_Pos[MAX_SHIP_LENGTH - 1].x  || m_Pos[MAX_SHIP_LENGTH - 1].y)
	{
	printf_s("ship pos full\n");
	return;
	}*/


	for (int i = 0; i <MAX_SHIP_LENGTH; i++)
	{
		if (m_Pos[i].x == 0)
		{
			m_Pos[i] = Pos;
			break;
		}
	}





	return;
}

//HitResult Ship::HitCheck(Position hitPos)
//{
//
//}
