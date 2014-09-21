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
	m_PlayerMap = new Map();
	m_OtherPlayerMap = new Map();
	
	m_ShipVector.reserve(SHIP_TYPE_END);
	m_ShipVector.push_back(new Aircraft());
	m_ShipVector.push_back(new BattleShip());
	m_ShipVector.push_back(new Cruiser());
	m_ShipVector.push_back(new Destroyer());
	m_ShipVector.push_back(new Destroyer());
	memset(m_NetworkMap, 0, sizeof(char)*(MAX_HORIZONTAL*MAX_VERTICAL));
	m_StartAttackPos.x = -1;
	m_StartAttackPos.y = -1;
	
	m_HitPosVec.reserve(MAX_HITPOS);
	

}


Player::~Player()
{
	if (m_PlayerMap)
	{
		delete   m_PlayerMap;
		m_PlayerMap = nullptr;

	}
	if (m_OtherPlayerMap)
	{
		delete   m_OtherPlayerMap;
		m_OtherPlayerMap = nullptr;
		
	}



	for (auto iterShip = m_ShipVector.begin(); iterShip != m_ShipVector.end();)
	{
		if ((*iterShip))
		{
			delete (*iterShip);
			*iterShip = nullptr;
			iterShip = m_ShipVector.erase(iterShip);
		}
		else
		{
			iterShip = m_ShipVector.erase(iterShip);
		}
	}

	
	m_ShipVector.clear();
}

void Player::RandomAssignShips()
{
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
	_ASSERT((unsigned int)shipIdx <= m_ShipVector.size() && shipIdx >= 0);

	if (!((unsigned int)shipIdx <= m_ShipVector.size() && shipIdx >= 0))
	{
		return false;
	}

	if ((unsigned int)shipIdx >= m_ShipVector.size())
	{
		return true;
	}

	ShipPos tmpPos = { 0, };

	int shipSize = m_ShipVector[shipIdx]->GetSize();
	for (int i = 0; i < shipSize; ++i)
	{
		tmpPos = m_ShipVector[shipIdx]->GetPos(i);
		if (tmpPos.x == -1 || tmpPos.y == -1)
		{
			return false;
		}
	}



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

	int shipSize = m_ShipVector[shipIdx]->GetSize();
	for (int i = 0; i < shipSize; ++i)
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

	int shipSize = m_ShipVector[shipIdx]->GetSize();
	for (int i = 0; i < shipSize; ++i)
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

	
	int shipSize = m_ShipVector[shipIdx]->GetSize();
	for (int i = 0; i < shipSize; ++i)
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
	++m_AttackTurn;

	if (m_AttackedResultFromGM == HIT)
	{
		m_GameMode = TARGETMODE;
	}

	switch (m_GameMode)
	{
	case HUNTMODE:
	ChooseRandPosWithPairity();
	break;

	case TARGETMODE:
	if (m_AttackedResultFromGM == HIT)
	{
		SetPotentialTarget();
	}

	
	while (!(m_PotentialTargetStack.empty()) && !SelectFineAttackPos())
	{
		m_AttackPos = m_PotentialTargetStack.top();
		m_PotentialTargetStack.pop();

	}
	
	if (m_PotentialTargetStack.empty() && !SelectFineAttackPos())
	{
		m_GameMode = HUNTMODE;

		ChooseRandPosWithPairity();
	}
	break;
	default:
	break;
	}
	
	return m_AttackPos;
}

bool Player::SelectFineAttackPos()
{

	//if (m_OtherRemainShipCheck[DESTROYER] == 0 &&
	//	m_OtherRemainShipCheck[CRUISER] == 0 &&
	//	m_OtherRemainShipCheck[BATTLESHIP] == 0)
	//{
	//	if (!IsFullSizePosInMap(AIRCRAFT_SIZE))
	//	{
	//		
	//		if (((m_AttackPos.x + m_AttackPos.y) % AIRCRAFT_SIZE) != 0)
	//		{
	//			return false;
	//		}
	//	}
	//	else
	//	{
	//	
	//		/*for (char i = 0; i < MAX_HORIZONTAL; ++i)
	//		{
	//			for (char j = 0; j < MAX_VERTICAL; ++j)
	//			{
	//				if (m_OtherPlayerMap->GetEachPosDataInMap(i, j) == MAP_NONE)
	//				{
	//					m_AttackPos.x = i;
	//					m_AttackPos.y = j;
	//				}
	//			}
	//		}*/
	//	}

	//}
	//else if (m_OtherRemainShipCheck[DESTROYER] == 0 &&
	//		 m_OtherRemainShipCheck[CRUISER] == 0)
	//{
	//	if (!IsFullSizePosInMap(BATTLESHIP_SZIE))
	//	{
	//		if (((m_AttackPos.x + m_AttackPos.y) % BATTLESHIP_SZIE) != 0)
	//		{
	//			return false;
	//		}
	//	}
	//	else
	//	{
	//		for (char i = 0; i < MAX_HORIZONTAL; ++i)
	//		{
	//			for (char j = 0; j < MAX_VERTICAL; ++j)
	//			{
	//				if (m_OtherPlayerMap->GetEachPosDataInMap(i, j) == MAP_NONE)
	//				{
	//					m_AttackPos.x = i;
	//					m_AttackPos.y = j;
	//				}
	//			}
	//		}

	//	}
	//}
	//else if (m_OtherRemainShipCheck[DESTROYER] == 0)
	//{
	//	if (!IsFullSizePosInMap(CRUISER_SIZE))
	//	{
	//		if (((m_AttackPos.x + m_AttackPos.y) % CRUISER_SIZE) != 0)
	//		{
	//			return false;
	//		}
	//	}
	//	else
	//	{
	//		for (char i = 0; i < MAX_HORIZONTAL; ++i)
	//		{
	//			for (char j = 0; j < MAX_VERTICAL; ++j)
	//			{
	//				if (m_OtherPlayerMap->GetEachPosDataInMap(i, j) == MAP_NONE)
	//				{
	//					m_AttackPos.x = i;
	//					m_AttackPos.y = j;
	//				}
	//			}
	//		}

	//	}
	//}
	//else
	//{
	//	if (!IsFullSizePosInMap(DESTROYER_SIZE))
	//	{
	//		if (((m_AttackPos.x + m_AttackPos.y) % DESTROYER_SIZE) != 0)
	//		{
	//			return false;
	//		}
	//	}
	//	else
	//	{
	//		for (char i = 0; i < MAX_HORIZONTAL; ++i)
	//		{
	//			for (char j = 0; j < MAX_VERTICAL; ++j)
	//			{
	//				if (m_OtherPlayerMap->GetEachPosDataInMap(i, j) == MAP_NONE)
	//				{
	//					m_AttackPos.x = i;
	//					m_AttackPos.y = j;
	//				}
	//			}
	//		}

	//	}
	//}


	if (m_AttackPos.x >= MAX_HORIZONTAL || m_AttackPos.x < ZERO_POINT ||
		m_AttackPos.y >= MAX_VERTICAL || m_AttackPos.y < ZERO_POINT)
	{
		return false;
	}


	if (m_OtherPlayerMap->GetEachPosDataInMap(m_AttackPos) == MAP_NONE)
	{
		return true;
	}
	else
	{
		return false;
	}
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




void Player::SetAttackedResult()
{
	//전체 배를 돌면서 어디에 맞았는지 확인 하는 거야? 
	//왜?

	/*if (m_PlayerMap->GetEachPosDataInMap(m_PosAttackedFromOtherPlayer) == SHIP_ATTACEKED)
	{
		m_AttackedResult = HIT;
	}
	else
	{
		m_AttackedResult = MISS;
	}*/
	HitResult tmpHitResult;
	m_AttackedResult = HIT_NONE;
	
	for (std::vector<Ship*>::size_type i = 0; i < m_ShipVector.size(); ++i)
	{
		tmpHitResult = m_ShipVector[i]->CheckAttack(m_PosAttackedFromOtherPlayer);
		
		if (tmpHitResult != HIT_NONE)
		{
			m_AttackedResult = tmpHitResult;
			return;
		}
	}

	if (m_AttackedResult == HIT_NONE)
	{
		m_AttackedResult = MISS;
	}
}

void Player::SetAttackedResultFromGM(HitResult inputHitResult)
{
	_ASSERT(inputHitResult >= HIT_NONE && inputHitResult < HITREUSLT_MAX);
	if (!(inputHitResult >= HIT_NONE && inputHitResult < HITREUSLT_MAX))
	{
		m_AttackedResultFromGM = HIT_NONE;
	}

	m_AttackedResultFromGM = inputHitResult;
}

void Player::MakrAttackResultToOtherPlayerMap()
{
	ShipPos tmpAttackPos = m_AttackPos;

	if (m_AttackedResultFromGM == MISS)
	{
		m_OtherPlayerMap->MarkAttackResult(m_AttackPos, MISSED_ATTACK);
	}
	else
	{
		m_OtherPlayerMap->MarkAttackResult(m_AttackPos, SHIP_ATTACEKED);
	}
	
}

bool Player::IsAllShipDestroyed()
{
	for (std::vector<Ship*>::size_type i = 0; i < m_ShipVector.size(); ++i)
	{
		if (m_ShipVector[i]->GetHP() != 0)
		{
			return false;
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
	printf_s("\n");
	printf_s("\t\t\t\t");
	printf_s("My Map\n");
	//printf_s("Defender's Map\n");
	m_PlayerMap->PrintMapData();
}

void Player::InitAttackedResult()
{
	m_AttackedResult = HIT_NONE;
}

void Player::InitAttacekedPos()
{
	m_PosAttackedFromOtherPlayer.x = -1;
	m_PosAttackedFromOtherPlayer.y = -1;

}



void Player::InitAttackPos()
{
	m_AttackPos.x = -1;
	m_AttackPos.y = -1;
}

void Player::InitOtherPlayerMap()
{
	m_OtherPlayerMap->InitMap();
}

void Player::InitPlayerMap()
{
	m_PlayerMap->InitMap();
}

void Player::InitShipPos()
{

	for (auto pShip : m_ShipVector)
	{
		pShip->InitPos();
	}

	//for (std::vector<Ship*>::size_type i = 0; i < m_ShipVector.size(); ++i)
	//{
	//	m_ShipVector[i]->InitPos();
	//}
}

void Player::InitAttacker()
{
	InitAttackPos();
	InitAttackResultFromGM();
	InitOtherPlayerMap();
	InitRemainShip();
	InitHitPosVec();
	InitAttackTurn();
	InitGameMode();
	

}

void Player::InitDefender()
{
	InitAttackedResult();
	InitAttacekedPos();
	InitPlayerMap();
	InitShipPos();
	InitShipHP();
//	InitAttackedPosArr();
}

void Player::InitShipHP()
{

	for (auto pShip : m_ShipVector)
	{
		pShip->InitHP();
	}

	//for (std::vector<Ship*>::size_type i = 0; i < m_ShipVector.size(); ++i)
	//{
	//	m_ShipVector[i]->InitHP();
	//}
}

void Player::MakrAttackResultToPlayerMap(ShipPos attackedPos)
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


	if (m_AttackedResult == MISS)
	{
		m_PlayerMap->MarkAttackResult(attackedPos, MISSED_ATTACK);
	}
	else
	{
		m_PlayerMap->MarkAttackResult(attackedPos, SHIP_ATTACEKED);
	}

	//ShipPos movePos = { 0, };
	//ShipPos tmpAttackPos = attackedPos;

	//switch (m_AttackedResult)
	//{
	//case HIT_NONE:
	//break;
	//case HIT:
	//m_PlayerMap->MarkAttackResult(attackedPos, SHIP_ATTACEKED);
	//break;
	//case MISS:
	//m_PlayerMap->MarkAttackResult(attackedPos, MISSED_ATTACK);
	//break;
	//case DESTROY:
	//break;
	//case AIRCRAFT_DESTROY:
	//

	//movePos.x = m_AttackPosArr[m_AttackTurn - 1].x - tmpAttackPos.x;
	//movePos.y = m_AttackPosArr[m_AttackTurn - 1].y - tmpAttackPos.y;

	//for (int i = 0; i < AIRCRAFT_SIZE; ++i)
	//{
	//	m_PlayerMap->MarkAttackResult(attackedPos, SHIP_DESTROYED);
	//	tmpAttackPos.x += movePos.x;
	//	tmpAttackPos.y += movePos.y;

	//}
	//break;

	//case BATTLESHIP_DESTROY:
	//
	//movePos.x = m_AttackPosArr[m_AttackTurn - 1].x - tmpAttackPos.x;
	//movePos.y = m_AttackPosArr[m_AttackTurn - 1].y - tmpAttackPos.y;

	//for (int i = 0; i < BATTLESHIP_SZIE; ++i)
	//{
	//	m_PlayerMap->MarkAttackResult(attackedPos, SHIP_DESTROYED);
	//	tmpAttackPos.x += movePos.x;
	//	tmpAttackPos.y += movePos.y;

	//}
	//break;

	//case CRUISER_DESTROY:
	//
	//movePos.x = m_AttackPosArr[m_AttackTurn - 1].x - tmpAttackPos.x;
	//movePos.y = m_AttackPosArr[m_AttackTurn - 1].y - tmpAttackPos.y;

	//for (int i = 0; i < CRUISER_SIZE; ++i)
	//{
	//	m_PlayerMap->MarkAttackResult(attackedPos, SHIP_DESTROYED);
	//	tmpAttackPos.x += movePos.x;
	//	tmpAttackPos.y += movePos.y;
	//}
	//break;

	//case DESTROYER_DESTROY:
	//


	////이부분은 추가할것이 있다. 
	//movePos.x = m_AttackPosArr[m_AttackTurn - 1].x - tmpAttackPos.x;
	//movePos.y = m_AttackPosArr[m_AttackTurn - 1].y - tmpAttackPos.y;

	//for (int i = 0; i < DESTROYER_SIZE; ++i)
	//{
	//	m_PlayerMap->MarkAttackResult(attackedPos, SHIP_DESTROYED);
	//	tmpAttackPos.x += movePos.x;
	//	tmpAttackPos.y += movePos.y;

	//}
	//break;
	//case HITREUSLT_MAX:
	//break;
	//default:
	//break;
	//}
}

void Player::InitRemainShip()
{
	m_OtherRemainShipCheck[SHIP_TYPE_NONE] = 0;
	m_OtherRemainShipCheck[AIRCRAFT] = 1;
	m_OtherRemainShipCheck[BATTLESHIP] = 1;
	m_OtherRemainShipCheck[CRUISER] = 1;
	m_OtherRemainShipCheck[DESTROYER] = 2;
}

//void Player::InitAttakPosArr()
//{
//	memset(m_AttackPosArr, -1, sizeof(ShipPos)*(MAX_HORIZONTAL*MAX_VERTICAL));
//}

//void Player::InitHitResultArr()
//{
//	memset(m_HitResultArr, HIT_NONE, sizeof(HitResult)*(MAX_HORIZONTAL*MAX_VERTICAL));
//}

//void Player::InitAttackedPosArr()
//{
//	memset(m_AttackedPosFromOtherPlayerArr, -1, sizeof(ShipPos)*(MAX_HORIZONTAL*MAX_VERTICAL));
//}

void Player::SetAttackedPosArr(ShipPos attackedPos, int eachGameTurn)
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

	m_AttackedPosFromOtherPlayerArr[eachGameTurn] = attackedPos;
}



void Player::InitAttackTurn()
{
	m_AttackTurn = -1;
}

void Player::CheckRemainShip()
{
	switch (m_AttackedResultFromGM)
	{
	
	case AIRCRAFT_DESTROY:
	--m_OtherRemainShipCheck[AIRCRAFT];
	break;
	case BATTLESHIP_DESTROY:
	--m_OtherRemainShipCheck[BATTLESHIP];
	break;
	case CRUISER_DESTROY:
	--m_OtherRemainShipCheck[CRUISER];
	break;
	case DESTROYER_DESTROY:
	--m_OtherRemainShipCheck[DESTROYER];
	break;
	
	default:
	break;
	}
}

void Player::PrintOtherPlayerMap()
{
	printf_s("\n");
	printf_s("\t\t\t\t");
	printf_s("Enemy Map\n");
	//printf_s("Attacker's Map\n");
	m_OtherPlayerMap->PrintMapData();
}


void Player::SetPotentialTarget()
{
	
	//m_PotentialTargetSetCheck = true;
	if (m_AttackPos.y-1 >= VERTICAL_ZERO &&
		m_OtherPlayerMap->GetEachPosDataInMap(m_AttackPos.x, m_AttackPos.y-1) == MAP_NONE)
	{
		ShipPos tmpPos;
		tmpPos.x = m_AttackPos.x;
		tmpPos.y = m_AttackPos.y-1;
		m_PotentialTargetStack.push(tmpPos);
	}

	if (m_AttackPos.x +1 < MAX_HORIZONTAL &&
		m_OtherPlayerMap->GetEachPosDataInMap(m_AttackPos.x +1, m_AttackPos.y) == MAP_NONE)
	{
		ShipPos tmpPos;
		tmpPos.x = m_AttackPos.x+1;
		tmpPos.y = m_AttackPos.y;
		m_PotentialTargetStack.push(tmpPos);
	}

	if (m_AttackPos.y+1 < MAX_VERTICAL &&
		m_OtherPlayerMap->GetEachPosDataInMap(m_AttackPos.x, m_AttackPos.y +1) == MAP_NONE)
	{
		ShipPos tmpPos;
		tmpPos.x = m_AttackPos.x;
		tmpPos.y = m_AttackPos.y+1;
		m_PotentialTargetStack.push(tmpPos);
	}

	if (m_AttackPos.x -1 >= HORIZONTAL_ZERO &&
		m_OtherPlayerMap->GetEachPosDataInMap(m_AttackPos.x - 1, m_AttackPos.y) == MAP_NONE)
	{
		ShipPos tmpPos;
		tmpPos.x = m_AttackPos.x - 1;
		tmpPos.y = m_AttackPos.y;
		m_PotentialTargetStack.push(tmpPos);
	}

	
}



bool Player::IsReMainShipInPlayerMap()
{
	ShipPos tmpPos = { 0, };

	for (char i = 0; i < MAX_HORIZONTAL; ++i)
	{
		for (char j = 0; j < MAX_VERTICAL; ++j)
		{
			if (m_PlayerMap->GetEachPosDataInMap(i,j) == SHIP_LAUNCH)
			{
				return true;
			}
			
		}
		
	}

	return false;
}

void Player::InitGameMode()
{
	m_GameMode = HUNTMODE;
}

void Player::InitAttackResultFromGM()
{
	m_AttackedResultFromGM = HIT_NONE;
}

bool Player::IsFullSizePosInMap(ShipSize inputSize)
{
	for (char i = 0; i < MAX_HORIZONTAL; ++i)
	{
		for (char j = 0; j < MAX_VERTICAL; ++j)
		{
			if ((i + j) % inputSize == 0)
			{
				if (m_OtherPlayerMap->GetEachPosDataInMap(i, j) == MAP_NONE)
				{
					/*m_AttackPos.x = i;
					m_AttackPos.y = j;*/
					return false;
				}
			}
		}
	}

	return true;
}

void Player::InitPlayer()
{
	InitDefender();
	InitAttacker();
	memset(m_NetworkMap, 0, sizeof(char)*(MAX_HORIZONTAL*MAX_VERTICAL));
}

void Player::SetNetworAttackedResult(HitResult inputResult)
{
	_ASSERT(inputResult < HITREUSLT_MAX &&
		inputResult >= 0);

	if (!(inputResult < HITREUSLT_MAX &&inputResult >= 0))
	{
		m_AttackedResult = HIT_NONE;
	}
	m_AttackedResult = inputResult;

}

ShipData Player::ParseAssignShip()
{
	ShipData shipData;
	Coord tmpCoord;

	for (unsigned int i = 0; i < m_ShipVector.size(); ++i)
	{
		for (int j = 0; j < m_ShipVector[i]->GetSize(); ++j)
		{
			tmpCoord.mX = m_ShipVector[i]->GetPos(j).x;
			tmpCoord.mY = m_ShipVector[i]->GetPos(j).y;
			shipData.SetShipCoord((ShipData::ShipType)(i + 1), j, tmpCoord);
		}
	}

	return shipData;
}



void Player::ChooseRandPosWithPairity()
{
	int whileCheck = 0;

	while (true)
	{
		m_AttackPos.x = rand() % MAX_HORIZONTAL;
		m_AttackPos.y = rand() % MAX_VERTICAL;

		if (m_OtherRemainShipCheck[DESTROYER] == 0 &&
			m_OtherRemainShipCheck[CRUISER] == 0 &&
			m_OtherRemainShipCheck[BATTLESHIP] == 0)
		{
			if ((m_AttackPos.x + m_AttackPos.y) % AIRCRAFT_SIZE == 0
				&& SelectFineAttackPos())
			{
				return;
			}

		}
		else if (m_OtherRemainShipCheck[DESTROYER] == 0 &&
			m_OtherRemainShipCheck[CRUISER] == 0)
		{
			if ((m_AttackPos.x + m_AttackPos.y) % BATTLESHIP_SZIE == 0
				&& SelectFineAttackPos())
			{
				return;
			}
		}
		else if (m_OtherRemainShipCheck[DESTROYER] == 0)
		{
			if ((m_AttackPos.x + m_AttackPos.y) % CRUISER_SIZE == 0
				&& SelectFineAttackPos())
			{
				return;
			}
		}
		else
		{
			if ((m_AttackPos.x + m_AttackPos.y) % DESTROYER_SIZE == 0
				&& SelectFineAttackPos())
			{
				return;
			}
		}

		++whileCheck;

		if (whileCheck == 300)
		{
			break;
		}


	}


	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		for (int j = 0; j < MAX_VERTICAL; ++j)
		{
			if (m_OtherPlayerMap->GetEachPosDataInMap(i, j) == MAP_NONE)
			{
				m_AttackPos.x = i;
				m_AttackPos.y = j;
			}
		}
	}

}

void Player::InitHitPosVec()
{
	m_HitPosVec.clear();
}

void Player::InitPotentialTargetStack()
{

	while (!m_PotentialTargetStack.empty())
	{
		m_PotentialTargetStack.pop();
	}
}

ShipPos Player::SelectPosWithHitVec()
{
	++m_AttackTurn;

	if (!(m_AttackedResultFromGM == HIT_NONE ||
		m_AttackedResultFromGM == MISS))
	{
		m_HitPosVec.push_back(m_AttackPos);
		m_GameMode = TARGETMODE;
	}

	switch (m_GameMode)
	{
	case HUNTMODE:
	ChooseRandPosWithPairity();
	break;
	case TARGETMODE:

	break;
	default:
	break;
	}
}

void Player::ChooseAttackDir()
{
	

	int northSize = 0, southSize = 0, 
		eastSize = 0, westSize = 0;

	for (int i = (m_AttackPos.x)-1; i >= 0; --i)
	{
		if (m_OtherPlayerMap->GetEachPosDataInMap(i, m_AttackPos.y) == MAP_NONE)
		{
			++northSize;
		}
		else
		{
			break;
		}
	}

	for (int i = (m_AttackPos.x) + 1; i < MAX_HORIZONTAL; ++i)
	{
		if (m_OtherPlayerMap->GetEachPosDataInMap(i,m_AttackPos.y) == MAP_NONE)
		{
			++southSize;
		}
		else
		{
			break;
		}
	}

	for (int i = (m_AttackPos.y) + 1; i < MAX_VERTICAL; ++i)
	{
		if (m_OtherPlayerMap->GetEachPosDataInMap(m_AttackPos.x, i) == MAP_NONE)
		{
			++eastSize;
		}
		else
		{
			break;
		}
	}

	for (int i = (m_AttackPos.y) - 1; i >= 0; --i)
	{
		if (m_OtherPlayerMap->GetEachPosDataInMap(m_AttackPos.x, i) == MAP_NONE)
		{
			++westSize;
		}
		else
		{
			break;
		}
	}

	
	if (northSize == 0 && southSize == 0 && eastSize == 0 && westSize == 0)
	{
		; // 이런게 있을 수가 있나. 
	}

	int biggerSize = northSize >= southSize ? northSize : southSize;
	int biggerSize2 = eastSize >= westSize ? eastSize : westSize;
	int biggestSize = biggerSize >= biggerSize2 ? biggerSize : biggerSize2;
	

}




