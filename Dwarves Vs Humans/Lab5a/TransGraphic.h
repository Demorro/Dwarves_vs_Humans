#pragma once
#include "windowssprite.h"
class TransGraphic :
	public WindowsSprite
{
	public:
		TransGraphic(void);
		TransGraphic(int xpos, int ypos, LPSTR imagepath);

		static const int tileWidth = 20;
		static const int tileHeight = 18;

		//Scales x and y for the tiles, probably wont be changed through the code
		float scaleFactorX;
		float scaleFactorY;

		//Adjusting these should change the rect used on the spriteSheet
		int sourceX;
		int sourceY;

		int sourceWidth;
		int sourceHeight;

		void drawTrans(HDC bitmapHDC, HDC backHDC);
		void setup(int xPos, int yPos, int sourceX, int sourceY, int sourceWidth, int sourceHeight, LPSTR imagePath);
		void changeSource(int x, int y, int width, int height);
	private:
		void setupSpecificVariables(int xPos, int yPos, int sourceX, int sourceY, int sourceWidth, int sourceHeight, LPSTR imagePath);
};

