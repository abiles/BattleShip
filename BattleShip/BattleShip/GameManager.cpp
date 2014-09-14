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
	m_Attacker = new Player();
	m_Defender = new Player();
}


GameManager::~GameManager()
{
	delete m_Attacker;
	delete m_Defender;
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

void GameManager::InitAttackPosFromPlayer()
{
	m_AttackPosFromPlayer.x = -1;
	m_AttackPosFromPlayer.y = -1;
}

void GameManager::InitAttackResultFromPlayer()
{
	m_AttackedResultFromDef = HIT_NONE;
}

void GameManager::PlayingGame()
{
	int totalTurnNum = 0;
	int EachGameTurn = 0;
	for (int i = 0; i < GAMENUM; ++i)
	{
		m_Attacker->InitAttacker();
		m_Defender->InitDefender();
		m_Defender->RandomAssignShips();
		

		while (!IsGameEnd())
		{
			m_AttackPosFromPlayer = m_Attacker->SelectPosToAttack();
			m_Attacker->SetAttackPosArr();
			system("cls");
			m_Defender->SetAttackedPos(m_AttackPosFromPlayer);
			m_Defender->SetAttackedPosArr(m_AttackPosFromPlayer, EachGameTurn);
			m_Defender->SetAttackedResult();
			m_Defender->MakrAttackResultToPlayerMap(m_AttackPosFromPlayer);
			m_AttackedResultFromDef = m_Defender->GetAttackedResult();
			m_Attacker->SetAttackedResultFromGM(m_AttackedResultFromDef);
			m_Attacker->MakrAttackResultToOtherPlayerMap();
			m_Attacker->CheckRemainShip();
			m_Defender->PrintShips();
			HitResultPrint();
			m_Attacker->PrintOtherPlayerMap();
			m_Defender->PrintMap();
			
			
			++EachGameTurn;
		}
		totalTurnNum += EachGameTurn;
		printf_s("this game turn %d\n", EachGameTurn);
		EachGameTurn = 0;
	
	}

	printf_s("average %d game Turn = %f", GAMENUM, double(totalTurnNum / GAMENUM));
}

bool GameManager::IsGameEnd()
{
	return m_Defender->IsAllShipDestroyed();
}

void GameManager::HitResultPrint()
{
	printf_s("\n");

	switch (m_AttackedResultFromDef)
	{
	case HIT_NONE:
		printf_s("Noting\n");
		break;
	case HIT:
		printf_s("HIT!!\n");
		break;
	case MISS:
		printf_s("MISS!!\n");
		break;
	case DESTROY:
		printf_s("DESTROY!!\n");
		break;
	case AIRCRAFT_DESTROY:
		printf_s("AIRCRAFT_DESTROY\n");
		break;
	case BATTLESHIP_DESTROY:
		printf_s("BATTLESHIP_DESTROY\n");
		break;
	case CRUISER_DESTROY:
		printf_s("CRUISER_DESTROY\n");
		break;
	case DESTROYER_DESTROY:
		printf_s("DESTROYER_DESTROY\n");
		break;
	default:
		break;
	}
}
