#include "stdafx.h"
#include "Cruiser.h"


Cruiser::Cruiser()
{
	m_ShipType = CRUISER;
	m_ShipName = "Cruiser\t";
	m_Size = CRUISER_SIZE;
	m_HP = CRUISER_HP;
}


Cruiser::~Cruiser()
{
}

HitResult Cruiser::CheckAttack(ShipPos attackPos)
{
	HitResult result = Ship::CheckAttack(attackPos);

	return (result == DESTROY) ? CRUISER_DESTROY : result;
}
