// BattleShip_pp.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

int _tmain(int argc, _TCHAR* argv[])
{
	argc, argv;
	char inputChar;
	char inputCharToNum;
	int inputNum;
	int randNum;

	srand(time(NULL));

	while (1)
	{
		std::cout << "input character(A~H) : ";
		std::cin >> inputChar;

		if (inputChar >= 'A' && inputChar <= 'H') break;
	}

	while (1)
	{
		std::cout << "input number(1~8) : ";
		std::cin >> inputCharToNum;
		inputNum = atoi(&inputCharToNum);

		if (inputNum >= 1 && inputNum <= 8) break;
	}


	randNum = rand() % 3;
	if (randNum == 0)
	{
		std::cout << "Hit!!" << std::endl;
	}
	else if (randNum == 1)
	{
		std::cout << "Miss!" << std::endl;
	}
	else
	{
		std::cout << "Destroy!!!" << std::endl;
	}



	return 0;
}

