#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "Ship.h"
#include "Map.h"
#include "Aircraft.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::SetAttackedResultFromDef(HitResult HitResultFromDef)
{
	_ASSERT(HitResultFromDef >= HIT_NONE && HitResultFromDef < HITREUSLT_MAX);
	if (!(HitResultFromDef >= HIT_NONE && HitResultFromDef < HITREUSLT_MAX))
	{
		m_AttackedResultFromDef = HIT_NONE;
		return;
	}
	m_AttackedResultFromDef = HitResultFromDef;
}

void GameManager::SetAttackPosFromPlayer(ShipPos inputPos)
{
	_ASSERT(inputPos.x >= HORIZONTAL_ZERO && inputPos.x < MAX_HORIZONTAL);
	_ASSERT(inputPos.y >= VERTICAL_ZERO && inputPos.y < MAX_VERTICAL);

	if (!(inputPos.x >= HORIZONTAL_ZERO && inputPos.x < MAX_HORIZONTAL))
	{
		return;
	}
	if (!(inputPos.y >= VERTICAL_ZERO && inputPos.y < MAX_VERTICAL))
	{
		return;
	}

	m_AttackPosFromPlayer = inputPos;
}
