#pragma once
#include <string>

#define MAX_SHIP_LENGTH 5

struct Position
{
	char x;
	char y;
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

enum Direction
{
	DIRECTION_NONE,
	NORTH,
	EAST,
	SOUTH,
	WEST,
};


class Ship
{
public:
	Ship();
	~Ship();


	HitResult HitCheck(Position hitPos);
	int GetHP(){ return m_HP; }
	int GetSize(){ return m_Size; }
	std::string GetName(){ return m_Name; }

	void AddPosition(Position pos);
	void AddPosition(char x, char y);
	Position GetPos(int i){ return m_Pos[i]; }
	void PrintHP();
	void Print();

protected:
	
	std::string m_Name;
	ShipType m_Type;
	Position m_Pos[MAX_SHIP_LENGTH]; 
	int m_HP;
	int m_Size;

};
			
