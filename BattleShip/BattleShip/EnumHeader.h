#pragma once

enum HitResult
{
	HIT_NONE,
	HIT,
	MISS,
	DESTROY,
	AIRCRAFT_DESTROY,
	BATTLESHIP_DESTROY,
	CRUISER_DESTROY,
	DESTROYER_DESTROY,
};


enum ShipDirection
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	MAX_DIRECTION,
};

enum ShipHP
{
	HP_ZERO,
	HP_ONE,
	DESTROYER_HP,
	CRUISER_HP,
	BATTLESHIP_HP,
	AIRCRAFT_HP,
	MAX_HP,
	//�̰� ���
	
};

struct ShipPos
{
	char x;
	char y;
};

enum ShipSize
{
	SHIP_SIZE_ZERO,
	SHIP_SIZE_ONE, //���� ��ĭ¥�� �߰� ���� ����
	DESTROYER_SIZE,
	CRUISER_SIZE,
	BATTLESHIP_SZIE,
	AIRCRAFT_SIZE,
	MAX_SHIP_SIZE,
};

enum ShipType
{
	SHIP_NONE,
	AIRCRAFT,
	BATTLESHIP,
	CRUISER,
	DESTROYER,
};


enum MapMark
{
	SHIP_LAUNCH = 1,
};

enum MapSize
{
	MAX_HORIZONTAL = 8,
	MAX_VERTICAL = 8,
};

