//Windows Example Code
//Paul Robertson 2012

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <vector>
#include "WindowsSprite.h"
#include "WindowsInput.h"
#include "GameManager.h"


using namespace std;

int ticker =0;
HBITMAP		theOldFrontBitMap, theOldBackBitMap;
HWND        ghwnd;
RECT		screenRect;
HDC			backHDC, frontHDC, bitmapHDC;	//Hardware device contexts for the Buffers

bool isPlaying = true;

WindowsInput input;
GameManager gameManager;
int timeSkip = 20;

BOOL waitFor(unsigned long delay);
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);


void RegisterMyWindow(HINSTANCE hInstance)
{
    WNDCLASSEX  wcex;									

    wcex.cbSize        = sizeof (wcex);				
    wcex.style         = CS_HREDRAW | CS_VREDRAW;		
    wcex.lpfnWndProc   = WndProc;						
    wcex.cbClsExtra    = 0;								
    wcex.cbWndExtra    = 0;								
    wcex.hInstance     = hInstance;						
    wcex.hIcon         = 0; 
    wcex.hCursor       = LoadCursor (NULL, IDC_ARROW);	
															
    wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
    wcex.lpszMenuName  = NULL;							
    wcex.lpszClassName = "FirstWindowClass";				
    wcex.hIconSm       = 0; 

	RegisterClassEx (&wcex);	
}


BOOL InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow)
{
	HWND        hwnd;
	hwnd = CreateWindow ("FirstWindowClass",					
						 "Dwarves vs Humans",		  	
						 WS_BORDER,	
						 CW_USEDEFAULT,			
						 CW_USEDEFAULT,			
						 1250,			
						 750,			
						 NULL,					
						 NULL,					
						 hInstance,				
						 NULL);		

	if (!hwnd)
	{
		return FALSE;
	}

    ShowWindow (hwnd, nCmdShow);						
    UpdateWindow (hwnd);	
	ghwnd = hwnd;
	return TRUE;

}



BOOL WaitFor(unsigned long delay)
{
	static unsigned long clockStart = 0;
	unsigned long timePassed;
	unsigned long now = timeGetTime();

	timePassed = now - clockStart;
	if (timePassed >  delay)
	{
		clockStart = now;
		return TRUE;
	}
	else
		return FALSE;
}
	
			
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	input.CallInWndProc(hwnd ,message, wParam, lParam);
    switch (message)											
    {	

		case WM_CREATE:	
			break;

		case WM_SIZE:
			InvalidateRect(ghwnd,NULL,false);
			break;	

		case WM_PAINT:
		    break;		

		case WM_DESTROY:	
			
			PostQuitMessage(0);	
								
			break;				
	}													

	return DefWindowProc (hwnd, message, wParam, lParam);		
															
}



void setBuffers()
{
	GetClientRect(ghwnd, &screenRect);	//creates rect based on window client area
	frontHDC = GetDC(ghwnd);			// Initialises front buffer device context (window)
	backHDC = CreateCompatibleDC(frontHDC);// sets up Back DC to be compatible with the front
	bitmapHDC=CreateCompatibleDC(backHDC);
	theOldFrontBitMap = CreateCompatibleBitmap(frontHDC, screenRect.right, 
		screenRect.bottom);		//creates bitmap compatible with the front buffer
    theOldBackBitMap = (HBITMAP)SelectObject(backHDC, theOldFrontBitMap);
								//creates bitmap compatible with the back buffer
	FillRect(backHDC, &screenRect, (HBRUSH)GetStockObject(0));	
}

void displayFrame()
{
		BitBlt(frontHDC, screenRect.left,screenRect.top, screenRect.right, 
		screenRect.bottom, backHDC, 0, 0, SRCCOPY);
		FillRect(backHDC, &screenRect, (HBRUSH)GetStockObject(0));	
}

void releaseResources()
{
	SelectObject(backHDC,theOldBackBitMap);
	DeleteDC(backHDC);
	DeleteDC(bitmapHDC);
	ReleaseDC(ghwnd,frontHDC);
}


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int nCmdShow)			
{									
    MSG         msg;	
	HDC	hdcWindow;

	RegisterMyWindow(hInstance);

   	if (!InitialiseMyWindow(hInstance, nCmdShow))
	return FALSE;
	
	setBuffers();

	//Initialisation

	gameManager.setup(ghwnd);

	while (isPlaying == true)					
    {							
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
		    if (msg.message==WM_QUIT)
				break;
			TranslateMessage (&msg);							
			DispatchMessage (&msg);
		}
		
		else
		{		
			if (WaitFor(10))
			{	
				gameManager.update(input,ghwnd);
				gameManager.render(bitmapHDC,backHDC);
				displayFrame();

			}
			if(input.keys[VK_SPACE])
			{

			}

		}
    }

    releaseResources();
	return msg.wParam ;										
}



