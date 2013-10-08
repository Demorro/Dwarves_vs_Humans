#include "HealthBar.h"


HealthBar::HealthBar(void)
{
}


void HealthBar::update(int xPos, int yPos, int health)
{
	x = xPos;
	y = yPos;

	if((health <= 100) && (health > 90))
	{
		changeSource(X100,Y100,sourceWidth,sourceHeight);
	}
	else if((health <= 90) && (health > 80))
	{
		changeSource(X90,Y90,sourceWidth,sourceHeight);
	}
	else if((health <= 80) && (health > 70))
	{
		changeSource(X80,Y80,sourceWidth,sourceHeight);
	}
	else if((health <= 70) && (health > 60))
	{
		changeSource(X70,Y70,sourceWidth,sourceHeight);
	}
	else if((health <= 60) && (health > 50))
	{
		changeSource(X60,Y60,sourceWidth,sourceHeight);
	}
	else if((health <= 50) && (health > 40))
	{
		changeSource(X50,Y50,sourceWidth,sourceHeight);
	}
	else if((health <= 40) && (health > 30))
	{
		changeSource(X40,Y40,sourceWidth,sourceHeight);
	}
	else if((health <= 30) && (health > 20))
	{
		changeSource(X30,Y30,sourceWidth,sourceHeight);
	}
	else if((health <= 20) && (health > 10))
	{
		changeSource(X20,Y20,sourceWidth,sourceHeight);
	}
	else if((health <= 10) && (health > 0))
	{
		changeSource(X10,Y10,sourceWidth,sourceHeight);
	}
	else if(health <= 0)
	{
		changeSource(X0,Y0,sourceWidth,sourceHeight);
	}
}