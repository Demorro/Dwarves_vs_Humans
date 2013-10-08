#pragma once
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <vector>
#include <string>

//Pink transparency mask
#define TRANSPARENT_MASK RGB(255,0,255)

class WindowsSprite
{
private:

protected:
	HBITMAP LoadABitmap(LPSTR);
	void loadImage(LPSTR);
	void findDimensions();
public:
	HBITMAP bitmap;
	float x;
	float y;
	int width;
	int height;
	int scaleFactorX;
	int scaleFactorY;
	int sourceX;
	int sourceY;
	int sourceWidth;
	int sourceHeight;

	WindowsSprite();
	~WindowsSprite(void);
	void draw(HDC bitMapHDC,HDC backHDC);
	void drawTrans(HDC bitMapHDC,HDC backHDC);
	void setup(int xPos, int yPos, int scaleX, int scaleY, LPSTR imagePath);
	//void setup(int xPos, int yPos, int scaleX, int scaleY, LPSTR imagePath,int sourceX, int sourceY, int sourceWidth, int sourceHeight);
	void loadAndChangeSprite(LPSTR imagePath);
	void setSprite(HBITMAP sprite);
	void setPosition(int x, int y);
};

/* Instructions
	
	Declare as so at the top of main (or wherever) WindowsSprite spritename;
	in WinMain() run spritename.setup(int XPosition, int YPosition, "ImagePath");	These images need to be wherever the program is running from ,so the debug folder mostly, but if you build a release(might have to play with the linker, winmm.lib fixed something for me before,) they should be in the release folder

	below that in the else section of the while loop run

	spritename.run(bitmapHDC, backHDC);		here you have to pass it two hardware device contexts, which should be defined at the top of main, hopefully they will just be called bitmapHDC and backHDC
											however, for posterities sake im putting the HDC definitions here, you shouldnt ever have to really use this :	 HDC	backHDC, frontHDC, bitmapHDC;	//Hardware device contexts for the Buffers

*/