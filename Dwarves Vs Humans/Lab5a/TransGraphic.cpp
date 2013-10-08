#include "TransGraphic.h"

TransGraphic::TransGraphic()
{
	setupSpecificVariables(0,0,0,0,width,height,"TileSheet.bmp");
}


TransGraphic::TransGraphic(int xPos, int yPos, LPSTR imagePath)
{
	setupSpecificVariables(xPos,yPos,0,0,width,height,"TileSheet.bmp");
	
}

void TransGraphic::setup(int xPos, int yPos, int sourceX, int sourceY, int sourceWidth, int sourceHeight, LPSTR imagePath)
{
	setupSpecificVariables(xPos,yPos,sourceX,sourceY,sourceWidth,sourceHeight,"TileSheet.bmp");
}


void TransGraphic::drawTrans(HDC bitmapHDC, HDC backHDC)
{
	HBITMAP originalBitMap;
	originalBitMap = (HBITMAP)SelectObject(bitmapHDC, bitmap);
	TransparentBlt(backHDC, x * scaleFactorX, y * scaleFactorY, width * scaleFactorX, height * scaleFactorY, bitmapHDC, sourceX, sourceY, sourceWidth, sourceHeight, TRANSPARENT_MASK);
	SelectObject(bitmapHDC,originalBitMap); 
}

void TransGraphic::setupSpecificVariables(int xPos, int yPos, int inputSourceX, int inputSourceY, int inputSourceWidth, int inputSourceHeight, LPSTR imagePath)
{

	bitmap = LoadABitmap(imagePath);
	if (!bitmap)
	{
		MessageBox(NULL, "File Not Loaded",imagePath, MB_OK);
	}

	x = xPos;
	y = yPos;
	findDimensions();

	scaleFactorX = 2.0f;
	scaleFactorY = 2.0f;

	width = inputSourceWidth;
	height = inputSourceHeight;
	sourceWidth = inputSourceWidth;
	sourceHeight = inputSourceHeight;

	sourceX = inputSourceX;
	sourceY = inputSourceY;
}

void TransGraphic::changeSource(int x, int y, int width, int height)
{
	sourceX = x;
	sourceY = y;
	sourceWidth = width;
	sourceHeight = height;
}
