#pragma once
#include "Ship.h"
class BattleShip :
	public Ship
{
public:
	BattleShip();
	virtual ~BattleShip();

	HitResult CheckAttack(ShipPos attackPos);
	void	  InitHP(){ m_HP = BATTLESHIP_HP; }
};

