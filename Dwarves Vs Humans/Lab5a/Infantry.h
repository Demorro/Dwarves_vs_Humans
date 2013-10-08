#pragma once
#include "unit.h"
class Infantry :
	public Unit
{
public:
	Infantry(void);
	~Infantry(void);


	//the moveValue of the unit
	static const int moveRange = 8;
	//the attackValue of the unit
	static const int attackRange = 1;
	//the health of the unit
	static const int health = 100;
	//the damage of this units attack
	static const int attackDamage = 60;


	void setup(float xGrid, float yGrid, int xTileWidth, int yTileWidth, Race unitRace, LPSTR imagePath);
	void setupSpecificVariables(float xPos, float yPos, Race unitRace, LPSTR imagePath);


};

