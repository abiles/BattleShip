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
	m_Player = new Player();
}


GameManager::~GameManager()
{
	delete m_Attacker;
	delete m_Defender;
	delete m_Player;
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
			m_AttackPosFromPlayer = m_Attacker->SelectPosWithHitList();
			m_Defender->SetAttackedPos(m_AttackPosFromPlayer);
			m_Defender->SetAttackedResult();
			//system("cls");
			m_Defender->MakrAttackResultToPlayerMap(m_AttackPosFromPlayer);
			m_AttackedResultFromDef = m_Defender->GetAttackedResult();
			m_Attacker->SetAttackedResultFromGM(m_AttackedResultFromDef);
			m_Attacker->MakrAttackResultToOtherPlayerMap();
			m_Attacker->CheckRemainShip();
			//m_Defender->PrintShips();
			//HitResultPrint();
			//m_Attacker->PrintOtherPlayerMap();
			//m_Defender->PrintMap();
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
	return !(m_Defender->IsReMainShipInPlayerMap());
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


void GameManager::NetworkGamePlaying()
{
	// Server IP & Port
	const char*				IP = "10.73.42.117";	// �ڱ� ��ǻ�Ϳ��� ���� ���� 127.0.0.1
	const unsigned short	PORT = 9000;

	Network network;
	PacketType type;
	ErrorType error;
	ShipData shipData;
	ShipPos tmpPos;
	ShipPos tmpPos2;
	Coord tmpCoord;
	char mapData[MAX_HORIZONTAL*MAX_VERTICAL];
	
	


	try
	{
		Network::Initialize();
	}
	catch (Network::Exception)
	{
		puts("�ʱ�ȭ ���� ������ �߻��߽��ϴ�.");
		return;
	}

	try
	{
		network.Connect(IP, PORT);
	}
	catch (Network::Exception ex)
	{
		switch (ex)
		{
		case Network::NETWORK_ERROR:
		puts("������ ���ῡ �����߽��ϴ�.");
		break;
		case Network::PARAMETER_ERROR:
		puts("�Լ��� �μ��� �߸��Ǿ����ϴ�.");
		break;
		}
		return;
	}
	puts("���� ����!");

	try	// ���� ó���� ���� try������ ��� ���Ѵ�.
	{
		/*
		** �̸�&�й� ����
		�ִ� ���̴� MAX_NAME_LEN-1 == 15����.
		������ ET_OK�� ���ϵȴ�.
		�̹� �ִ� �̸��� ���� ET_DUPLICATED_NAME�� �´�.
		*/
		const wchar_t name[MAX_NAME_LEN] = L"KSY";
		const int studentID = 141014;

		error = network.SubmitName(name, studentID);
		if (error == ET_DUPLICATED_NAME)
		{
			puts("�̹� �����ϴ� �̸��Դϴ�.");
			return;
		}

		/*
		** ���� ���� ���
		������ ���۵Ǹ� ������ ������ ���´�.
		Network::GameStartData ����ü�� ���� ������ �����´�.
		*/
		Network::GameStartData gameStartData;
		puts("���� ���� �����");
		network.WaitForStart(&gameStartData);
		wprintf_s(L"��Ī�Ǿ����ϴ�. ���� �̸�: %s, �й�: %d\n", gameStartData.oppositionName, gameStartData.oppositionStudentID);

		/*
		** ���� ����
		�� ������� ���� ������� nȸ �ݺ��Ѵ�.
		�ϳ��� ������ ������ ���� ������ �����ؾ� �Ѵٸ� PKT_SC_NEXT_GAME ��Ŷ��
		��� ������ ������ PKT_SC_ALL_OVER ��Ŷ�� ���´�.
		*/
		bool allOver = false;
		while (!allOver)
		{
			
			m_Player->InitPlayer();
			m_Player->RandomAssignShips();



			shipData = m_Player->ParseAssignShip();
		

			shipData.ToMapData(mapData);

			/*
			** �� ����
			�ڽ��� ��ġ�� �� �����͸� ������ �����Ѵ�.
			�� �����͸� ����� ������� �� ������ �ִ�.
			�ϳ��� ���� MAP_WIDHT * MAP_HEIGHT ũ���� ���� ����� ���̰�,
			�ϳ��� ShipData ����ü�� �̿��ؼ� ����� ���̴�.
			*/

			while (true)
			{
				

				error = network.SubmitMap(mapData);
				if (error == ET_INVALID_MAP)
					puts("��ȿ���� ���� �� �������Դϴ�.");
				else
					break;
			}

			/*
			** ���� ����
			�� ���ʶ�� ���� ��ġ�� �����Ѵ�.
			���ʰ� ������ �����ڿ� ���� ��ġ, ���� ����� �޴´�.
			�� ������ ������ PKT_SC_GAME_OVER ��Ŷ�� ���´�.
			*/
			bool gameOver = false;

			while (!gameOver)
			{
				error = network.GetPacketType(&type);

				switch (type)
				{
					// ������ �߻��ϴ� ���(������ ���� ����)
				case PKT_SC_ERROR:
				if (error == ET_OPPOSITION_DISCONNECTED)
					puts("������ ������ ���������ϴ�.");
				else
					puts("�� �� ���� �����Դϴ�.");
				return;

				// �� ����
				case PKT_SC_MY_TURN:
				{
									   /*
									   ** ���� ��ġ ����
									   x, y�� 0~7 ������ �����̴�.
									   */
									   while (true)
									   {
										   ShipPos AttackPos = m_Player->SelectPosWithHitList();
										   Coord pos(AttackPos.x,AttackPos.y);
										   error = network.SubmitAttack(pos);
										   if (error == ET_INVALID_ATTACK)
											   puts("��ȿ���� ���� ���� ��ġ�Դϴ�.");
										   else
											   break;
									   }
									   break;
				}

				// ���� ���
				case PKT_SC_ATTACK_RESULT:
				{
											 
											 Network::AttackResultData attackResult = network.GetAttackResult();
											 if (attackResult.isMine)
											 {
												 puts("���� ���:");
												 tmpPos = m_Player->GetAttackPos();
												 
												 tmpPos2.x = attackResult.pos.mX;
												 tmpPos2.y = attackResult.pos.mY;
												 if (tmpPos.x == tmpPos2.x && tmpPos.y == tmpPos2.y)
												 {
													m_Player->SetAttackedResultFromGM((HitResult)attackResult.attackResult);
													m_Player->MakrAttackResultToOtherPlayerMap();
												 }
												 else
												 {
													 printf_s("���� ���� ���ݰ� �������� ���� ������ �ٸ�\n");
												 }
												 
											 }
											 else
											 {
												 puts("�ǰ� ���:");
												 tmpPos.x = attackResult.pos.mX;
												 tmpPos.y = attackResult.pos.mY;
												 m_Player->SetAttackedPos(tmpPos);
												 m_Player->SetNetworAttackedResult((HitResult)attackResult.attackResult);
												 m_Player->MakrAttackResultToPlayerMap(tmpPos);
											 }
											 printf_s("X: %d, Y: %d, RESULT: %s\n", attackResult.pos.mX, attackResult.pos.mY, 
															 NetworkAttackResultPrint((HitResult)attackResult.attackResult));

											//m_Player->PrintMap();
											//m_Player->PrintOtherPlayerMap();
											 break;
				}

				// ���� ����
				case PKT_SC_GAME_OVER:
				{
										 Network::GameResultData gameResult = network.GetGameResult();
										 if (gameResult.isWinner)
											 puts("�¸�!!!");
										 else
											 puts("�й�...");
										 printf_s("�� ��: %d\n", gameResult.turns);
										 gameOver = true;
										 break;
				}

				default:
				throw Network::UNEXPECTED_PACKET;
				break;
				}
			}

			/*
			** ������ ó��
			*/
			network.GetPacketType(&type);

			if (type == PKT_SC_NEXT_GAME)
			{
				puts("���� ������ �غ����ּ���.");
			}
			else if (type == PKT_SC_ALL_OVER)
			{
				Network::FinalResultData finalResult = network.GetFinalResult();
				puts("��� ����");
				printf_s("�¸� Ƚ��: %d, ��� �� ��: %.1f", finalResult.winCount, finalResult.avgTurns);
				
				network.WaitForStart(&gameStartData);
				wprintf_s(L"��������. ���� �̸�: %s, �й�: %d\n", gameStartData.oppositionName, gameStartData.oppositionStudentID);
				allOver = true;
			}
			else
				throw Network::UNEXPECTED_PACKET;
		}
	}
	catch (Network::Exception ex)
	{
		switch (ex)
		{
		case Network::NETWORK_ERROR:
		puts("��Ʈ��ũ�� ������ �߻��߽��ϴ�.");
		break;
		case Network::SERVER_CLOSED:
		puts("�������� ������ ���������ϴ�.");
		break;
		case Network::PARAMETER_ERROR:
		puts("�Լ��� �μ��� �߸��Ǿ����ϴ�.");
		break;
		case Network::UNEXPECTED_PACKET:
		puts("�������� �߸��� ������ ���۵Ǿ����ϴ�.");
		break;
		default:
		break;
		}
	}

	
	/*
	** ���� ����
	����� �Ҹ�ÿ��� �ڵ����� Disconnect�� ȣ���Ѵ�.
	*/
	network.Disconnect();

	_getch();

}


char* GameManager::NetworkAttackResultPrint(HitResult inputResult)
{
	char* tmpChar= nullptr;
	switch (inputResult)
	{
	
	case MISS:
	tmpChar = "MISS";
	break;
	case HIT:
	tmpChar = "HIT";
	break;
	case AIRCRAFT_DESTROY:
	tmpChar = "AIRCRAFT_DESTROY";
	break;
	case BATTLESHIP_DESTROY:
	tmpChar = "BATTLESHIP_DESTROY";
	break;
	case CRUISER_DESTROY:
	tmpChar = "CRUISER_DESTROY";
	break;
	case DESTROYER_DESTROY:
	tmpChar = "DESTROYER_DESTROY";
	break;
	case DESTROY:
	break;
	case HITREUSLT_MAX:
	break;
	default:
	break;
	}

	return tmpChar;
}
