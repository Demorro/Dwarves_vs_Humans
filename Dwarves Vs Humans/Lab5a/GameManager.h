#pragma once
#include <Windows.h>
#include "Unit.h"
#include "Archer.h"
#include <vector>
#include "HexMap.h"
#include "WindowsInput.h"
#include "BackGround.h"
#include "StartScreen.h"
#include "OrdersGrid.h"
#include <algorithm>
#include "HealthBar.h"
#include "Infantry.h"

using namespace std;

class GameManager
{
public:
	GameManager(void);
	~GameManager(void);

	//Stores the window dimensions so we can use them for all kinds of things
	RECT windowDimensions;

	StartScreen startScreen;
	BackGround backGround;
	BackGround player1Victory;
	BackGround player2Victory;
	WindowsSprite pauseScreen;

	bool player1HasWon;
	bool player2HasWon;

	bool isPaused;
	bool readyToPause;

	HexMap gameMap;
	
	vector<Unit> player1Units;
	vector<Unit> player2Units;
	vector<HealthBar> player1HealthBars;
	vector<HealthBar> player2HealthBars;

	OrdersGrid ordersGrid;

	int turnPieceCounter;
	bool isPlayer1Turn;
	bool isPlayer2Turn;

	int noOfPlayer1Units;
	int noOfPlayer2Units;

	void setupUnits();

	int testint;

	bool readyToSkip;
	bool readyToAttack;
	bool readyToMove;

	void setup(HWND ghwnd);
	void setupBoard(HWND ghwnd, WindowsInput input);
	void render(HDC bitmapHDC, HDC backHDC);
	void update(WindowsInput input, HWND hwnd);

	void movePhase(Unit &unit, WindowsInput &input,HexMap &gameMap);
	void attackPhase(Unit &unit,WindowsInput &input,HexMap &gameMap);

private:
	bool placeUnits(int player);
	bool isOnStartScreen;
};

