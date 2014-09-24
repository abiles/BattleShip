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
	const char*				IP = "10.73.42.117";	// 자기 컴퓨터에서 돌릴 때는 127.0.0.1
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
		puts("초기화 도중 문제가 발생했습니다.");
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
		puts("서버와 연결에 실패했습니다.");
		break;
		case Network::PARAMETER_ERROR:
		puts("함수의 인수가 잘못되었습니다.");
		break;
		}
		return;
	}
	puts("접속 성공!");

	try	// 예외 처리를 위해 try문으로 모두 감싼다.
	{
		/*
		** 이름&학번 전송
		최대 길이는 MAX_NAME_LEN-1 == 15글자.
		성공시 ET_OK가 리턴된다.
		이미 있는 이름을 쓰면 ET_DUPLICATED_NAME이 온다.
		*/
		const wchar_t name[MAX_NAME_LEN] = L"KSY";
		const int studentID = 141014;

		error = network.SubmitName(name, studentID);
		if (error == ET_DUPLICATED_NAME)
		{
			puts("이미 존재하는 이름입니다.");
			return;
		}

		/*
		** 게임 시작 대기
		게임이 시작되면 상대방의 정보가 들어온다.
		Network::GameStartData 구조체로 상대방 정보를 가져온다.
		*/
		Network::GameStartData gameStartData;
		puts("게임 시작 대기중");
		network.WaitForStart(&gameStartData);
		wprintf_s(L"매칭되었습니다. 상대방 이름: %s, 학번: %d\n", gameStartData.oppositionName, gameStartData.oppositionStudentID);

		/*
		** 게임 시작
		맵 제출부터 게임 종료까지 n회 반복한다.
		하나의 게임이 끝나고 다음 게임을 시작해야 한다면 PKT_SC_NEXT_GAME 패킷이
		모든 게임이 끝나면 PKT_SC_ALL_OVER 패킷이 들어온다.
		*/
		bool allOver = false;
		while (!allOver)
		{
			
			m_Player->InitPlayer();
			m_Player->RandomAssignShips();



			shipData = m_Player->ParseAssignShip();
		

			shipData.ToMapData(mapData);

			/*
			** 맵 제출
			자신이 배치한 맵 데이터를 서버로 전송한다.
			맵 데이터를 만드는 방법에는 두 가지가 있다.
			하나는 직접 MAP_WIDHT * MAP_HEIGHT 크기의 맵을 만드는 것이고,
			하나는 ShipData 구조체를 이용해서 만드는 것이다.
			*/

			while (true)
			{
				

				error = network.SubmitMap(mapData);
				if (error == ET_INVALID_MAP)
					puts("유효하지 않은 맵 데이터입니다.");
				else
					break;
			}

			/*
			** 게임 루프
			내 차례라면 공격 위치를 전송한다.
			차례가 끝나면 공격자와 공격 위치, 공격 결과를 받는다.
			한 게임이 끝나면 PKT_SC_GAME_OVER 패킷이 들어온다.
			*/
			bool gameOver = false;

			while (!gameOver)
			{
				error = network.GetPacketType(&type);

				switch (type)
				{
					// 에러가 발생하는 경우(상대방의 접속 종료)
				case PKT_SC_ERROR:
				if (error == ET_OPPOSITION_DISCONNECTED)
					puts("상대방의 접속이 끊어졌습니다.");
				else
					puts("알 수 없는 에러입니다.");
				return;

				// 내 차례
				case PKT_SC_MY_TURN:
				{
									   /*
									   ** 공격 위치 전송
									   x, y는 0~7 사이의 정수이다.
									   */
									   while (true)
									   {
										   ShipPos AttackPos = m_Player->SelectPosWithHitList();
										   Coord pos(AttackPos.x,AttackPos.y);
										   error = network.SubmitAttack(pos);
										   if (error == ET_INVALID_ATTACK)
											   puts("유효하지 않은 공격 위치입니다.");
										   else
											   break;
									   }
									   break;
				}

				// 공격 결과
				case PKT_SC_ATTACK_RESULT:
				{
											 
											 Network::AttackResultData attackResult = network.GetAttackResult();
											 if (attackResult.isMine)
											 {
												 puts("공격 결과:");
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
													 printf_s("내가 보낸 공격과 서버에서 받은 공격이 다름\n");
												 }
												 
											 }
											 else
											 {
												 puts("피격 결과:");
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

				// 게임 종료
				case PKT_SC_GAME_OVER:
				{
										 Network::GameResultData gameResult = network.GetGameResult();
										 if (gameResult.isWinner)
											 puts("승리!!!");
										 else
											 puts("패배...");
										 printf_s("턴 수: %d\n", gameResult.turns);
										 gameOver = true;
										 break;
				}

				default:
				throw Network::UNEXPECTED_PACKET;
				break;
				}
			}

			/*
			** 종료후 처리
			*/
			network.GetPacketType(&type);

			if (type == PKT_SC_NEXT_GAME)
			{
				puts("다음 게임을 준비해주세요.");
			}
			else if (type == PKT_SC_ALL_OVER)
			{
				Network::FinalResultData finalResult = network.GetFinalResult();
				puts("모두 종료");
				printf_s("승리 횟수: %d, 평균 턴 수: %.1f", finalResult.winCount, finalResult.avgTurns);
				
				network.WaitForStart(&gameStartData);
				wprintf_s(L"게임종료. 상대방 이름: %s, 학번: %d\n", gameStartData.oppositionName, gameStartData.oppositionStudentID);
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
		puts("네트워크에 문제가 발생했습니다.");
		break;
		case Network::SERVER_CLOSED:
		puts("서버와의 연결이 끊어졌습니다.");
		break;
		case Network::PARAMETER_ERROR:
		puts("함수의 인수가 잘못되었습니다.");
		break;
		case Network::UNEXPECTED_PACKET:
		puts("서버에서 잘못된 정보가 전송되었습니다.");
		break;
		default:
		break;
		}
	}

	
	/*
	** 연결 종료
	참고로 소멸시에도 자동으로 Disconnect를 호출한다.
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
