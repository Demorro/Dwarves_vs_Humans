#pragma once
#include "windowssprite.h"
#include "WindowsInput.h"

class StartScreen :
	public WindowsSprite
{
public:
	StartScreen(void);
	~StartScreen(void);
	bool update(WindowsInput input); //if returns false then startscreen is done.
};

