#include "WindowsSprite.h"
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <vector>
#include <string>



WindowsSprite::WindowsSprite()
{
}


WindowsSprite::~WindowsSprite(void)
{
}

void WindowsSprite::draw(HDC bitmapHDC, HDC backHDC)
{
	HBITMAP originalBitMap;
	originalBitMap = (HBITMAP)SelectObject(bitmapHDC, bitmap);
	BitBlt(backHDC,x,y,width,height,bitmapHDC,0,0,SRCCOPY);
	SelectObject(bitmapHDC,originalBitMap); 
}

void WindowsSprite::drawTrans(HDC bitmapHDC, HDC backHDC)
{
	
	HBITMAP originalBitMap;
	originalBitMap = (HBITMAP)SelectObject(bitmapHDC, bitmap);
	TransparentBlt(backHDC,x,y,width * scaleFactorX,height * scaleFactorY,bitmapHDC,0,0,width,height,TRANSPARENT_MASK);
	SelectObject(bitmapHDC,originalBitMap); 
}


HBITMAP WindowsSprite::LoadABitmap(LPSTR szFileName)
{
	return (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}


void WindowsSprite::setup(int xPos, int yPos, int scaleX, int scaleY, LPSTR imagePath)
{
	bitmap = LoadABitmap(imagePath);
	if (!bitmap)
	{
		MessageBox(NULL, "File Not Loaded",imagePath, MB_OK);
	}
		

	x = xPos;
	y = yPos;
	scaleFactorX = scaleX;
	scaleFactorY = scaleY;
	findDimensions();

	sourceX = 0;
	sourceY = 0;
	sourceWidth = width;
	sourceHeight = height;


}
/*
void WindowsSprite::setup(int xPos, int yPos, int scaleX, int scaleY, LPSTR imagePath,int inputSourceX, int inputSourceY, int inputSourceWidth, int inputSourceHeight)
{
	bitmap = LoadABitmap(imagePath);
	if (!bitmap)
	{
		MessageBox(NULL, "File Not Loaded",imagePath, MB_OK);
	}
		

	x = xPos;
	y = yPos;
	scaleFactorX = scaleX;
	scaleFactorY = scaleY;
	findDimensions();

	sourceX = inputSourceX;
	sourceY = inputSourceY;
	sourceWidth = inputSourceWidth;
	sourceHeight = inputSourceHeight;


}
*/


void WindowsSprite::findDimensions()
{
	BITMAP bmap;
	GetObject(bitmap, sizeof(bmap), &bmap);
	height = bmap.bmHeight;
	width = bmap.bmWidth;
}

void WindowsSprite::loadAndChangeSprite(LPSTR imagePath)
{
	bitmap = LoadABitmap(imagePath);
	if (!bitmap)
	{
		MessageBox(NULL, "File Not Loaded",imagePath, MB_OK);
	}

	findDimensions();
}

void WindowsSprite::setSprite(HBITMAP sprite)
{
	bitmap = sprite;
	if (!bitmap)
	{
		MessageBox(NULL, "File Not Loaded","changingsprite", MB_OK);
	}

	findDimensions();
}

void WindowsSprite::setPosition(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
}

