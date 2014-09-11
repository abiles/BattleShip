#include "stdafx.h"
#include "Player.h"
#include "Ship.h"
#include "Map.h"
#include "Aircraft.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::RandomAssignShips()
{
	srand((unsigned int)time(NULL));


	int shipIdx = 0;
	ShipPos StartPos = { 0, };
	ShipDirection direction;

	while (!IsShipAssigned(shipIdx))
	{
		StartPos.x = rand() % MAX_HORIZONTAL;
		StartPos.y = rand() % MAX_VERTICAL;
		direction  = (ShipDirection)(rand() % MAX_DIRECTION);


		if (IsValidPos(StartPos, direction, shipIdx))
		{
			ValidPosLauchToShip(StartPos, direction, shipIdx);
			ValidPosSetToMap(StartPos, direction, shipIdx);
			shipIdx++;
		}

	}


	return;
}

bool Player::IsShipAssigned(int shipIdx)
{
	_ASSERT((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0);
	if (!((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0))
	{
		return false;
	}

	ShipPos tmpPos = { 0, };


	for (int i = 0; i < m_ShipVector[shipIdx]->GetSize(); ++i)
	{
		tmpPos = m_ShipVector[shipIdx]->GetPos(i);
		if (tmpPos.x == -1 || tmpPos.y == -1)
		{
			return false;
		}
	}

/*
	for (std::vector<Ship*>::size_type i = 0; i < m_ShipVector.size(); ++i)
	{
		
		for (int j = 0; j < m_ShipVector[i]->GetSize(); ++j)
		{
			tmpPos = m_ShipVector[i]->GetPos(j);
			if (tmpPos.x == 0 || tmpPos.y == 0)
			{
				return false;
			}
		}
	}
*/
	return true;
}

bool Player::IsValidPos(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx)
{
	_ASSERT(inputShipPos.x  < MAX_HORIZONTAL &&inputShipPos.x >= HORIZONTAL_ZERO);
	_ASSERT(inputShipPos.y < MAX_VERTICAL &&inputShipPos.y >= VERTICAL_ZERO);
	_ASSERT(inputDir < MAX_DIRECTION && inputDir >= NORTH);
	_ASSERT((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0);

	if (!(inputShipPos.x < MAX_HORIZONTAL &&
		inputShipPos.x >= HORIZONTAL_ZERO))
	{
		return false;
	}
	if (!(inputShipPos.y < MAX_VERTICAL &&
		inputShipPos.y >= VERTICAL_ZERO))
	{

		return false;
	}
	if (!(inputDir < MAX_DIRECTION && inputDir >= NORTH))
	{
		return false;
	}
	if (!((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0))
	{
		return false;
	}


	//std::vector<Ship>::iterator findIter;
	//1단계 끝지점이 지도를 넘지 않는지 확인

	if (!IsLastPointFine(inputShipPos, inputDir, shipIdx))
	{
		return false;
	}

	if (IsOtherShipOverlap(inputShipPos, inputDir, shipIdx))
	{
		return false;
	}

	return true;
}

bool Player::IsLastPointFine(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx)
{
	_ASSERT(inputShipPos.x < MAX_HORIZONTAL && inputShipPos.x >= HORIZONTAL_ZERO);
	_ASSERT(inputShipPos.y < MAX_VERTICAL && inputShipPos.y >= VERTICAL_ZERO);
	_ASSERT(inputDir < MAX_DIRECTION && inputDir >= NORTH);
	_ASSERT((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0);

	if (!(inputShipPos.x < MAX_HORIZONTAL &&
		  inputShipPos.x >= HORIZONTAL_ZERO))
	{
		return false;
	}
	if (!(inputShipPos.y < MAX_VERTICAL &&
		  inputShipPos.y >= VERTICAL_ZERO))
	{
		return false;
	}
	if (!(inputDir < MAX_DIRECTION && inputDir >= NORTH))
	{
		return false;
	}
	if (!((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0))
	{
		return false;
	}

	m_ShipVector[shipIdx]->MakeDir();
	//이거 여기서 해야되나? init이라고해서 만들어야 되나? 어짜피 한번만 만들면 되는데 



	for (int i = 0; i < m_ShipVector[shipIdx]->GetSize(); ++i)
	{
		inputShipPos.x += m_ShipVector[shipIdx]->GetDirPos(inputDir).x;
		inputShipPos.y += m_ShipVector[shipIdx]->GetDirPos(inputDir).y;
	}

	if (inputShipPos.x < 0 || inputShipPos.x >= MAX_HORIZONTAL)
	{
		return false;
	}
	if (inputShipPos.y < 0 || inputShipPos.y >= MAX_VERTICAL)
	{
		return false;
	}

	return true;
}

bool Player::IsOtherShipOverlap(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx)
{
	_ASSERT(inputShipPos.x < MAX_HORIZONTAL && inputShipPos.x >= HORIZONTAL_ZERO);
	_ASSERT(inputShipPos.y < MAX_VERTICAL && inputShipPos.y >= VERTICAL_ZERO);
	_ASSERT(inputDir < MAX_DIRECTION && inputDir >= NORTH);
	_ASSERT((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0);

	if (!(inputShipPos.x < MAX_HORIZONTAL &&
		  inputShipPos.x >= HORIZONTAL_ZERO))
	{
		return true;
	}
	if (!(inputShipPos.y < MAX_VERTICAL &&
		  inputShipPos.y >= VERTICAL_ZERO))
	{
		return true;
	}
	if (!(inputDir < MAX_DIRECTION && inputDir >= NORTH))
	{
		return true;
	}
	if (!((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0))
	{
		return true;
	}

	for (int i = 0; i < m_ShipVector[shipIdx]->GetSize(); ++i)
	{
		if (m_PlayerMap->GetEachPosDataInMap(inputShipPos) == SHIP_LAUNCH)
		{
			return true;
		}

		inputShipPos.x += m_ShipVector[shipIdx]->GetDirPos(inputDir).x;
		inputShipPos.y += m_ShipVector[shipIdx]->GetDirPos(inputDir).y;

	}

	return false;
}

void Player::ValidPosLauchToShip(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx)
{
	_ASSERT(inputShipPos.x < MAX_HORIZONTAL && inputShipPos.x >= HORIZONTAL_ZERO);
	_ASSERT(inputShipPos.y < MAX_VERTICAL && inputShipPos.y >= VERTICAL_ZERO);
	_ASSERT(inputDir < MAX_DIRECTION && inputDir >= NORTH);
	_ASSERT((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0);

	if (!(inputShipPos.x < MAX_HORIZONTAL &&
		inputShipPos.x >= HORIZONTAL_ZERO))
	{
		return;
	}
	if (!(inputShipPos.y < MAX_VERTICAL &&
		inputShipPos.y >= VERTICAL_ZERO))
	{
		return;
	}
	if (!(inputDir < MAX_DIRECTION && inputDir >= NORTH))
	{
		return;
	}
	if (!((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0))
	{
		return;
	}

	for (int i = 0; i < m_ShipVector[shipIdx]->GetSize(); ++i)
	{
		m_ShipVector[shipIdx]->AddPos(inputShipPos, i);
		inputShipPos.x += m_ShipVector[shipIdx]->GetDirPos(inputDir).x;
		inputShipPos.y += m_ShipVector[shipIdx]->GetDirPos(inputDir).y;
	}
}

void Player::ValidPosSetToMap(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx)
{
	_ASSERT(inputShipPos.x < MAX_HORIZONTAL && inputShipPos.x >= HORIZONTAL_ZERO);
	_ASSERT(inputShipPos.y < MAX_VERTICAL && inputShipPos.y >= VERTICAL_ZERO);
	_ASSERT(inputDir < MAX_DIRECTION && inputDir >= NORTH);
	_ASSERT((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0);

	if (!(inputShipPos.x < MAX_HORIZONTAL &&
		inputShipPos.x >= HORIZONTAL_ZERO))
	{
		return;
	}
	if (!(inputShipPos.y < MAX_VERTICAL &&
		inputShipPos.y >= VERTICAL_ZERO))
	{
		return;
	}
	if (!(inputDir < MAX_DIRECTION && inputDir >= NORTH))
	{
		return;
	}
	if (!((unsigned int)shipIdx < m_ShipVector.size() && shipIdx >= 0))
	{
		return;
	}

	for (int i = 0; i < m_ShipVector[shipIdx]->GetSize(); ++i)
	{
		m_PlayerMap->SetEachPosDataInMap(inputShipPos);
		inputShipPos.x += m_ShipVector[shipIdx]->GetDirPos(inputDir).x;
		inputShipPos.y += m_ShipVector[shipIdx]->GetDirPos(inputDir).y;
	}

}

ShipPos Player::SelectPosToAttack()
{
	ShipPos tmpPos = { 0, };
	
	return tmpPos;
}

void Player::SetAttackedPos(ShipPos attackedPos)
{
	_ASSERT(attackedPos.x < MAX_HORIZONTAL && attackedPos.x >= HORIZONTAL_ZERO);
	_ASSERT(attackedPos.y < MAX_VERTICAL && attackedPos.y >= VERTICAL_ZERO);
	if (!(attackedPos.x < MAX_HORIZONTAL &&
		attackedPos.x >= HORIZONTAL_ZERO))
	{
		return;
	}
	if (!(attackedPos.y < MAX_VERTICAL &&
		attackedPos.y >= VERTICAL_ZERO))
	{
		return;
	}

	m_PosAttackedFromOtherPlayer = attackedPos;

	
}

void Player::MarkAttackFromOtherPlayer()
{
	//일단 맵에 그린다. 
	m_PlayerMap->MarkAttackedPos(m_PosAttackedFromOtherPlayer);
}

void Player::SetAttackedResult()
{
	//전체 배를 돌면서 어디에 맞았는지 확인 하는 거야? 
	//왜?

	if (m_PlayerMap->GetEachPosDataInMap(m_PosAttackedFromOtherPlayer) == SHIP_ATTACEKED)
	{
		m_AttackedResult = HIT;
	}
	else
	{
		m_AttackedResult = MISS;
	}

	/*
	for (std::vector<Ship*>::size_type i = 0; i < m_ShipVector.size(); ++i)
	{
		m_AttackedResult = m_ShipVector[i]->CheckAttack(m_PosAttackedFromOtherPlayer);
		if (m_AttackedResult != HIT_NONE)
		{
			return;
		}
	}

	if (m_AttackedResult == HIT_NONE)
	{
		m_AttackedResult = MISS;
	}*/
}



bool Player::IsAllShipDestroyed()
{
	

	for (char i = 0; i < MAX_HORIZONTAL; ++i)
	{
		for (char j = 0; j < MAX_VERTICAL; ++j)
		{
			if (m_PlayerMap->GetEachPosDataInMap(i, j) == SHIP_LAUNCH)
			{
				return false;
			}
		}
	}

	return true;
}

void Player::PrintShips()
{
	for (std::vector<Ship*>::size_type i = 0; i < m_ShipVector.size(); ++i)
	{
		m_ShipVector[i]->PrintShipPos();
	}

	return;
}

void Player::PrintMap()
{
	m_PlayerMap->PrintMapData();
}
