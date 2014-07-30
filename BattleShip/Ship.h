#pragma once
#include <string>

#define MAX_SHIP_LENGTH 5

struct Position
{
	char x;
	char y;

	//왜 캐릭터?
};

enum ShipType
{
	SHIP_NONE,
	AIRCRAFT,
	BATTLESHIP,
	CRUISER,
	DESTROYER,

};

enum HitResult
{
	HITRESULT_NONE,
	MISS,
	HIT,
	AIRCRAFT_DESTROYED,
	BATTLESHIP_DESTROYED,
	CRUISER_DESTROYED,
	DESTROYER_DESTROYED,

};

class Ship
{
public:
	Ship();
	~Ship();

public:

	HitResult HitCheck(Position hitPos);
	int GetHP() { return m_HP; }
	//어떤 포지션 값을 받아서 m_pos에 차례대로 넣겠다. 
	void AddPosition(Position Pos);

protected:

	std::string m_Name;
	Position m_Pos[MAX_SHIP_LENGTH];
	ShipType m_Type;
	int m_HP;

};

