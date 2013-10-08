#pragma once
#include "transgraphic.h"
class HealthBar :
	public TransGraphic
{
public:
	HealthBar(void);
	void update(int xPos, int yPos, int health);

	//the amount of pixels it hangs above(or below) the unit
	static const int yOffset = -5;

	static const int X100 = 120;
	static const int Y100 = 5;
	static const int X90 = 120;
	static const int Y90 = 10;
	static const int X80 = 120;
	static const int Y80 = 15;
	static const int X70 = 120;
	static const int Y70 = 20;
	static const int X60 = 120;
	static const int Y60 = 25;
	static const int X50 = 120;
	static const int Y50 = 30;
	static const int X40 = 120;
	static const int Y40 = 35;
	static const int X30 = 120;
	static const int Y30 = 40;
	static const int X20 = 120;
	static const int Y20 = 45;
	static const int X10 = 120;
	static const int Y10 = 50;
	static const int X0 = 120;
	static const int Y0 = 55;
};

