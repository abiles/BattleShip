#include "stdafx.h"
#include "Destroyer.h"


Destroyer::Destroyer()
{
	m_ShipType = DESTROYER;
	m_ShipName = "Destroyer";
	m_Size = DESTROYER_SIZE;
	m_HP = DESTROYER_HP;
}


Destroyer::~Destroyer()
{
}

HitResult Destroyer::CheckAttack(ShipPos attackPos)
{
	HitResult result = Ship::CheckAttack(attackPos);

	return (result == DESTROY) ? DESTROYER_DESTROY : result;
}
