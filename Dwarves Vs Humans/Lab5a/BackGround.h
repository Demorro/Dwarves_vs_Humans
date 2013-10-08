#pragma once
#include "windowssprite.h"
class BackGround :
	public WindowsSprite
{
public:
	BackGround(void);
	~BackGround(void);

	//Stores the window dimensions so we can use them for all kinds of things
	RECT windowDimensions;
	void setup(int xPos, int yPos, int scaleX, int scaleY, LPSTR imagePath,HWND hwnd);
	void update(float scrollSpeed);
	bool movingLeft;
};

