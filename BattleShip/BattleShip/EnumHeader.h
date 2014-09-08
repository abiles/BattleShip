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

struct ShipPos
{
	char x;
	char y;
};

enum ShipSize
{
	MAX_SHIP_SIZE = 5,
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

