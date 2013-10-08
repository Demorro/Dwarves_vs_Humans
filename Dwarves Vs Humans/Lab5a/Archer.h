#pragma once
#include "unit.h"
class Archer :
	public Unit
{
public:
	Archer(void);
	~Archer(void);


	//the moveValue of the unit
	static const int moveRange = 6;
	//the attackValue of the unit
	static const int attackRange = 3;
	//the health of the unit
	static const int health = 100;
	//the damage of this units attack
	static const int attackDamage = 40;


	void setup(float xGrid, float yGrid, int xTileWidth, int yTileWidth, Race unitRace, LPSTR imagePath);
	void setupSpecificVariables(float xPos, float yPos, Race unitRace, LPSTR imagePath);


};

