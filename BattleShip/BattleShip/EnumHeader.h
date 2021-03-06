#pragma once



enum GameMode
{
	HUNTMODE,
	TARGETMODE,
};

enum GameNum
{
	GAMENUM = 10,
};


enum HitResult
{
	HIT_NONE,
	MISS,
	HIT,
	AIRCRAFT_DESTROY,
	BATTLESHIP_DESTROY,
	CRUISER_DESTROY,
	DESTROYER_DESTROY,
	DESTROY,
	HITREUSLT_MAX,
};

enum MapState
{
	MAP_NONE,
	SHIP_LAUNCH,
	SHIP_ATTACEKED,
	MISSED_ATTACK,
	SHIP_DESTROYED,

	
};




enum MapSize
{
	HORIZONTAL_ZERO = 0,
	VERTICAL_ZERO = 0,
	MAX_HORIZONTAL = 8,
	MAX_VERTICAL = 8,
};

enum OverLapCheck
{
	WRONGINPUT = -1,
	OVERLAP = 0,
	OVERLAP_NONE = 1,
};

enum PointLevel
{
	ZERO_POINT = 0,
	ONE_POINT = 10,
	TWO_POINT = 20,
	THREE_POINT = 30,
	FOUR_POINT = 40,
	FIVE_POINT = 50,
	SIX_POINT = 60,
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
	//이건 고민
	
};

struct ShipPos
{
	char x;
	char y;
};


enum ShipSize
{
	SHIP_SIZE_ZERO,
	SHIP_SIZE_ONE, //추후 한칸짜리 추가 가능 공간
	DESTROYER_SIZE,
	CRUISER_SIZE,
	BATTLESHIP_SZIE,
	AIRCRAFT_SIZE,
	MAX_SHIP_SIZE,
};

enum ShipType
{
	SHIP_TYPE_NONE,
	AIRCRAFT,
	BATTLESHIP,
	CRUISER,
	DESTROYER,
	SHIP_TYPE_END,
};

enum HitPos
{
	MAX_HITPOS = DESTROYER_SIZE * 2 + CRUISER_SIZE + 
				 BATTLESHIP_SZIE + AIRCRAFT_SIZE,

};



