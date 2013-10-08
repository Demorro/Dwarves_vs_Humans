#include "HexHighlight.h"

HexHighlight::HexHighlight()
{
	setupSpecificVariables(0,0,"TileSheet.bmp");
}


HexHighlight::HexHighlight(int xPos, int yPos, LPSTR imagePath)
{
	setupSpecificVariables(xPos,yPos,"TileSheet.bmp");
	
}

void HexHighlight::setup(int xPos, int yPos, LPSTR imagePath)
{
	setupSpecificVariables(xPos,yPos,"TileSheet.bmp");
}


void HexHighlight::drawTrans(HDC bitmapHDC, HDC backHDC)
{
	HBITMAP originalBitMap;
	originalBitMap = (HBITMAP)SelectObject(bitmapHDC, bitmap);
	TransparentBlt(backHDC, x * scaleFactorX, y * scaleFactorY, width * scaleFactorX, height * scaleFactorY, bitmapHDC, sourceX, sourceY, sourceWidth, sourceHeight, TRANSPARENT_MASK);
	SelectObject(bitmapHDC,originalBitMap); 
}

void HexHighlight::setupSpecificVariables(int xPos, int yPos, LPSTR imagePath)
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

	width = tileWidth;
	height = tileHeight;
	sourceWidth = tileWidth;
	sourceHeight = tileHeight;

	sourceX = 40;
	sourceY = 30;
}

void HexHighlight::changeSource(int x, int y, int width, int height)
{
	sourceX = x;
	sourceY = y;
	sourceWidth = width;
	sourceHeight = height;
}
