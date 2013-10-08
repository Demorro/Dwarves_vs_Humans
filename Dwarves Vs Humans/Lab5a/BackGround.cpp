#include "BackGround.h"


BackGround::BackGround(void)
{
}


BackGround::~BackGround(void)
{
}

void BackGround::setup(int xPos, int yPos, int scaleX, int scaleY, LPSTR imagePath, HWND hwnd)
{
	bitmap = LoadABitmap(imagePath);
	if (!bitmap)
	{
		MessageBox(NULL, "File Not Loaded",imagePath, MB_OK);
	}
		
	GetWindowRect(hwnd, &windowDimensions);

	x = xPos;
	y = yPos;
	scaleFactorX = scaleX;
	scaleFactorY = scaleY;
	findDimensions();

	movingLeft = true;
}


void BackGround::update(float scrollSpeed)
{
	if(movingLeft == true)
	{
		x-= scrollSpeed;
	}
	else if(movingLeft == false)
	{
		x+= scrollSpeed;
	}

	if((x+(width * scaleFactorX)) < windowDimensions.right)
	{
		movingLeft = false;
	}
	else if(x >= 0)
	{
		movingLeft = true;
	}

}
