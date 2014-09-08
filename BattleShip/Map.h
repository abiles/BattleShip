#pragma once
#include <iostream>

class Map
{
public:
	Map();
	~Map();


public:
	bool IsShip(int x, int y);

private:
	bool mapStatus[8][8];

};

