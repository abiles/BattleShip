#pragma once
#include <string>

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



class Ship
{
public:
	Ship();
	~Ship();


	HitResult HitCheck(Position hitPos);
	int GetHP(){ return m_HP; }
	void AddPosition(Position pos);
	void PrintHP();

protected:
	
	std::string m_Name;
	ShipType m_Type;
	Position m_Pos[5]; // 5->#Define으로 해보세열
	int m_HP;

};
			
