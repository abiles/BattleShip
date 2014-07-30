#include "stdafx.h"
#include "Player.h"
#include <stdlib.h>


Player::Player()
{
}


Player::~Player()
{
}

void Player::SetupShips()
{
	/*Position pos[5];

	for (int i = 0; i < 5; i++)
	{
	pos[i] = { 'c', '1' + i };
	m_Aircraft.AddPosition(pos[i]);

	}*/

	m_Aircraft.AddPosition('c', '1');
	m_Aircraft.AddPosition('c', '2');
	m_Aircraft.AddPosition('c', '3');
	m_Aircraft.AddPosition('c', '4');
	m_Aircraft.AddPosition('c', '5');
}

void Player::PrintShips()
{


	m_Aircraft.Print();
	m_BattleShip.Print();
	m_Cruiser.Print();
	m_Destroyer[0].Print();
	m_Destroyer[1].Print();

	/*Position buf;

	printf_s("%s: ", m_Aircraft.GetName().c_str());

	for (int i = 0; i < m_Aircraft.GetSize(); i++)
	{
	buf = m_Aircraft.GetPos(i);

	printf_s("%c%c ", buf.x, buf.y);

	}

	printf_s("\n");

	m_Destroyer[0].AddPosition('d', '1');
	m_Destroyer[0].AddPosition('d', '2');
	m_Destroyer[1].AddPosition('e', '1');
	m_Destroyer[1].AddPosition('e', '2');


	for (int i = 0; i < _countof(m_Destroyer); i++)
	{
	printf_s("%s %d: ", m_Destroyer[i].GetName().c_str(), i+1);



	for (int j = 0; j < m_Destroyer[i].GetSize(); j++)
	{
	buf = m_Destroyer[i].GetPos(j);

	printf_s("%c%c ", buf.x, buf.y);

	}
	printf_s("\n");
	}*/
}
