#pragma once

#include "Aircraft.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Destroyer.h"


class Player
{
public:
	Player();
	~Player();



public:

	void SetupShips();
	void PrintShips();
private:
	int myMap[8][8];
	int enemyMap[8][8];

	Aircraft m_Aircraft;
	Battleship m_BattleShip;
	Cruiser m_Cruiser;
	Destroyer m_Destroyer[2];

};

