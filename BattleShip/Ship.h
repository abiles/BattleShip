#pragma once
#include <string>

#define MAX_SHIP_LENGTH 5

struct Position
{
	char x;
	char y;

	//�� ĳ����?
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
	//� ������ ���� �޾Ƽ� m_pos�� ���ʴ�� �ְڴ�. 
	void AddPosition(Position Pos);

protected:

	std::string m_Name;
	Position m_Pos[MAX_SHIP_LENGTH];
	ShipType m_Type;
	int m_HP;

};

