// BattleShip_pp.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include "Ship.h"
#include "Player.h"

int _tmain(int argc, _TCHAR* argv[])
{
	argc, argv;
	
	Player player;
	player.SetupShips();
	player.PrintShips();
	getchar();


/*
	char inputChar;
	char inputCharToNum;
	int inputNum;
	int randNum;
	int select;
	int destroyCnt = 0;

	srand((unsigned int)time(NULL));
	std::string shipList[] = { "Aircraft", "BattleShip", "Cruiser", "Destroyer", "Destroyer" };
	std::string result[] = { "HIT!!", "MISS!!", "DESTROY!!" };i

	while (true)
	{
		while (true)
		{
			std::cout << "input character(A~H) : ";
			std::cin >> inputChar;

			if (inputChar >= 'A' && inputChar <= 'H') break;
		}

		while (true)
		{
			std::cout << "input number(1~8) : ";
			std::cin >> inputCharToNum;
			inputNum = atoi(&inputCharToNum);

			if (inputNum >= 1 && inputNum <= 8) break;
		}




		randNum = rand() % _countof(result);

		for (int i = 0; i < _countof(shipList); i++)
		{
			if (!shipList[i].empty())
			{
				printf_s("%s  ", shipList[i].c_str());
			}

		}
		printf_s("\n");

		if (randNum == 0)
		{
			std::cout << result[randNum] << std::endl;
		}
		else if (randNum == 1)
		{
			std::cout << result[randNum] << std::endl;
		}
		else
		{
			

			while (true)
			{
				select = rand() % _countof(shipList);
				if (!shipList[select].empty())
				{
					printf_s("%s Destroy!!\n", shipList[select].c_str());

					shipList[select] = "";
				
					destroyCnt++;
					break;
				}


			}

		}
		if (destroyCnt == _countof(shipList))
		{
			printf_s("종료!\n");
			break;
		}
		printf_s("\n");
	}*/




	return 0;
}

