#include "StartScreen.h"


StartScreen::StartScreen(void)
{
}


StartScreen::~StartScreen(void)
{
}

bool StartScreen::update(WindowsInput input)
{
	if(input.keys[VK_SPACE] == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}