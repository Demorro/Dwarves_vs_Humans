#include "WindowsInput.h"
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

WindowsInput::WindowsInput(void)
{
	mouseDistanceSinceLastMove;
	mouseXSinceLastMove = 0;
	mouseYSinceLastMove = 0;
	mouseX = 0;
	mouseY = 0;
	leftButtonDown = false;
	rightButtonDown = false;
	middleButtonDown = false;
}

//call this in the WndProc bit of main to handle input
void WindowsInput::CallInWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	leftButtonDown = false;
	rightButtonDown = false;
	middleButtonDown = false;
	switch (message)											
    {		

		case WM_KEYDOWN:
			keys[wParam]=true;
			break;

		case WM_KEYUP:
			keys[wParam]=false;
			break;

		case WM_MOUSEMOVE:
			mouseX = LOWORD (lParam);
			mouseY = HIWORD (lParam);
			mouseXSinceLastMove = mouseX - mouseXSinceLastMove;
			mouseYSinceLastMove = mouseY - mouseYSinceLastMove;
			break;

		case WM_LBUTTONDOWN:
			leftButtonDown = true;
			break;
		
		case WM_RBUTTONDOWN:
			rightButtonDown = true;
			break;

		case WM_MBUTTONDOWN:
			middleButtonDown = true;
			break;

		case WM_LBUTTONUP:
			leftButtonDown = false;
			break;
		
		case WM_RBUTTONUP:
			rightButtonDown = false;
			break;

		case WM_MBUTTONUP:
			middleButtonDown = false;
			break;
	}	
}

float WindowsInput :: MouseTravelledSinceLastMove()
{
	mouseDistanceSinceLastMove = (mouseXSinceLastMove * mouseXSinceLastMove) + (mouseYSinceLastMove * mouseYSinceLastMove);
	mouseDistanceSinceLastMove = sqrt(mouseDistanceSinceLastMove);
	return mouseDistanceSinceLastMove;
}

