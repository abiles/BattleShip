#include "stdafx.h"
#include "Aircraft.h"


Aircraft::Aircraft()
{
	m_ShipType = AIRCRAFT;
	m_ShipName = "Aircraft";
	m_Size = AIRCRAFT_SIZE;
	m_HP = AIRCRAFT_HP;

}


Aircraft::~Aircraft()
{
}

HitResult Aircraft::CheckAttack(ShipPos attackPos)
{
	HitResult result = Ship::CheckAttack(attackPos);

	return (result == DESTROY) ? AIRCRAFT_DESTROY : result;
}
