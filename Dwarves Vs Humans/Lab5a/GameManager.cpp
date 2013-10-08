#include "GameManager.h"
#include "HexTile.h"
#include "HexMap.h"
#include "WindowsInput.h"


GameManager::GameManager(void)
{
}


GameManager::~GameManager(void)
{
}

void GameManager::movePhase(Unit &unit,WindowsInput &input,HexMap &gameMap)
{

	HexTile defaultHex;

	bool finishedMove = false;

	int scaleX = gameMap.hexMapArray[0][0].scaleFactorX;
	int scaleY = gameMap.hexMapArray[0][0].scaleFactorY;

	int hexMouseX = input.mouseX - gameMap.mapOffsetX * scaleX;
	int hexMouseY = input.mouseY - gameMap.mapOffsetY * scaleY;

	int tileHeight = defaultHex.tileHeight;
	int tileWidth = defaultHex.tileWidth;

	bool isOddLine = false;

	//highlight unit
	gameMap.highlightSetTile(unit.hexGridX, unit.hexGridY);


	//Deal with the shifted along hexes
	if(int(hexMouseY) / ((tileHeight - gameMap.verticalStackOffset)*scaleY) %2 != 0)
	{
		hexMouseX += (tileWidth * (scaleX/2));
		isOddLine = true;
		//TEST CODE
		hexMouseX = ceilf((hexMouseX/((tileWidth) * scaleX)) * 2) - 2; //the array value for x, the minus 2 here is actually a mystery, but it works
		hexMouseY = ceilf((hexMouseY/((tileHeight - 8) * scaleY)) * 2); //The array value for y
	}
	else
	{
		hexMouseX = ceilf((hexMouseX/((tileWidth) * scaleX)) * 2); //the array value for x
		hexMouseY = ceilf((hexMouseY/((tileHeight - 8) * scaleY)) * 2) ; //the array value for y
	}
	//apparently you need this, damn if i know why, maybe because of the scaling up
	hexMouseX/=2;
	hexMouseY/=2;



	//ordersGrid.generateGrid(unit.hexGridX,unit.hexGridY,unit.moveValue,gameMap);
	//The actual movement code
	if(unit.hasMoved == false)
	{

		//Doing it this way lets you switch the grid of by hitting right mouse button, although it is a little tempermental
		if(input.rightButtonDown == true)
		{
			ordersGrid.eraseGrid(gameMap);
		}
		else if(input.rightButtonDown == false)
		{
			ordersGrid.generateMoveGrid(unit.hexGridX,unit.hexGridY,unit.moveValue,gameMap);
		}


		if((input.leftButtonDown == true) && (readyToMove == true))
		{
			if((hexMouseX >= 0) && (hexMouseX < gameMap.mapWidth))
			{
				if((hexMouseY >= 0) && (hexMouseY < gameMap.mapHeight))
				{
					if((gameMap.hexMapArray[hexMouseX][hexMouseY].isMoveGrid == true) && (gameMap.hexMapArray[hexMouseX][hexMouseY].isOccupied == false))
					{
						unit.hasMoved = true;
						unit.moveUnit(hexMouseX,hexMouseY,gameMap);
						//turnPieceCounter++;
						ordersGrid.eraseGrid(gameMap);
						//so we dont move 2 peices at the same time, dosent work entirely though
						input.leftButtonDown = false;
					}
				}
			}	
		}
		if(input.leftButtonDown == false)
		{
			readyToMove = true;
		}

		//Was getting errors because a keyboard constantly sends the enter signal really bloody fast, this means enter has to be lifted before anything can happen
		if(input.keys[VK_ENTER] == false)
		{
			readyToSkip = true;
		}

		//Means you can skip by pushing enter
		if((input.keys[VK_ENTER] == true) && (unit.hasMoved == false) && (readyToSkip == true))
		{
			unit.hasMoved = true;
			ordersGrid.eraseGrid(gameMap);
			//turnPieceCounter++;
			//so we dont move 2 peices at the same time, dosent work entirely though
			input.keys[VK_ENTER] = false;
			readyToSkip = false;
		}
	}
}

void GameManager::attackPhase(Unit &unit,WindowsInput &input,HexMap &gameMap)
{
	HexTile defaultHex;

	bool finishedMove = false;

	int scaleX = gameMap.hexMapArray[0][0].scaleFactorX;
	int scaleY = gameMap.hexMapArray[0][0].scaleFactorY;

	int hexMouseX = input.mouseX - gameMap.mapOffsetX * scaleX;
	int hexMouseY = input.mouseY - gameMap.mapOffsetY * scaleY;

	int tileHeight = defaultHex.tileHeight;
	int tileWidth = defaultHex.tileWidth;

	bool isOddLine = false;

	//highlight the unit
	gameMap.highlightSetTile(unit.hexGridX, unit.hexGridY);

	//Deal with the shifted along hexes
	if(int(hexMouseY) / ((tileHeight - gameMap.verticalStackOffset)*scaleY) %2 != 0)
	{
		hexMouseX += (tileWidth * (scaleX/2));
		isOddLine = true;
		hexMouseX = ceilf((hexMouseX/((tileWidth) * scaleX)) * 2) - 2; //the array value for x, the minus 2 here is actually a mystery, but it works
		hexMouseY = ceilf((hexMouseY/((tileHeight - 8) * scaleY)) * 2); //The array value for y
	}
	else
	{
		hexMouseX = ceilf((hexMouseX/((tileWidth) * scaleX)) * 2); //the array value for x
		hexMouseY = ceilf((hexMouseY/((tileHeight - 8) * scaleY)) * 2) ; //the array value for y
	}
	//apparently you need this, damn if i know why, maybe because of the scaling up
	hexMouseX/=2;
	hexMouseY/=2;


	//ordersGrid.generateGrid(unit.hexGridX,unit.hexGridY,unit.moveValue,gameMap);
	//The actual movement code
	if(unit.hasAttacked == false)
	{

		if(input.rightButtonDown == true)
		{
			ordersGrid.eraseGrid(gameMap);
		}
		//Doing it this way lets you switch the grid of by hitting right mouse button, although it is a little tempermental
		else if(input.rightButtonDown == false)
		{
			ordersGrid.generateAttackGrid(unit.hexGridX,unit.hexGridY,unit.attackValue,gameMap,unit.attackType);
		}


		if((input.leftButtonDown == true) && (readyToAttack == true))
		{
			if((hexMouseX >= 0) && (hexMouseX < gameMap.mapWidth))
			{
				if((hexMouseY >= 0) && (hexMouseY < gameMap.mapHeight))
				{
					if((gameMap.hexMapArray[hexMouseX][hexMouseY].isAttackGrid == true) && (gameMap.hexMapArray[hexMouseX][hexMouseY].isOccupied == true))
					{
						
						if(isPlayer1Turn == true)
						{
							unit.attack(gameMap,hexMouseX,hexMouseY,player2Units);
						}
						else if(isPlayer2Turn == true)
						{
							unit.attack(gameMap,hexMouseX,hexMouseY,player1Units);
						}
						unit.hasAttacked = true;
						turnPieceCounter++;
						ordersGrid.eraseGrid(gameMap);
						//so we dont move 2 peices at the same time, dosent work entirely though
						input.leftButtonDown = false;
						
						
					}
				}
			}	
		}
		if(input.leftButtonDown == false)
		{
			readyToAttack = true;
		}

		//Was getting errors because a keyboard constantly sends the enter signal really bloody fast, this means enter has to be lifted before anything can happen
		if(input.keys[VK_ENTER] == false)
		{
			readyToSkip = true;
		}

		//Means you can skip by pushing enter
		if((input.keys[VK_ENTER] == true) && (unit.hasAttacked == false) && (readyToSkip == true))
		{
			unit.hasAttacked = true;
			turnPieceCounter++;
			ordersGrid.eraseGrid(gameMap);
			//so we dont move 2 peices at the same time, dosent work entirely though
			input.keys[VK_ENTER] = false;
			readyToSkip = false;
		}
	}
}

void GameManager::update(WindowsInput input, HWND hwnd)
{

	if(isOnStartScreen == true)
	{
		isOnStartScreen = startScreen.update(input);
		if(isOnStartScreen == false) //will only trigger if start screen has just changed
		{
			setupBoard(hwnd,input);
		}
	}
	else if(isOnStartScreen == false)
	{
		//Was getting errors because a keyboard constantly sends the enter signal really bloody fast, this means enter has to be lifted before anything can happen
		if(input.keys[VK_P] == false)
		{
			readyToPause = true;
		}

		if((input.keys[VK_P] == true) && (isPaused == false) && (readyToPause == true))
		{
			isPaused = true;
			readyToPause = false;
			input.keys[VK_P] = false;
		}
		else if((input.keys[VK_P] == true) && (isPaused == true) && (readyToPause == true))
		{
			isPaused = false;
			readyToPause = false;
			input.keys[VK_P] = false;
		}


		if(isPaused == false)
		{
			if((input.keys[VK_SPACE]) && (player1HasWon == false) && (player2HasWon == false))
			{

				player1HasWon = false;
				player2HasWon = false;
				gameMap.generateNewMap();
				placeUnits(1);
				placeUnits(2);
				turnPieceCounter = 0;
				for(int i = 0; i < int(player1Units.size()); i++)
				{
					player1Units[i].hasMoved = false;
					player1Units[i].hasAttacked = false;
				}
				for(int i = 0; i < int(player2Units.size()); i++)
				{
					player2Units[i].hasMoved = false;
					player1Units[i].hasAttacked = false;
				}
				isPlayer1Turn = true;
				isPlayer2Turn = false;
			}

			//check for victory
			if(int(player1Units.size()) <= 0)
			{
				player2HasWon = true;
			}
			if(int(player2Units.size()) <= 0)
			{
				player1HasWon = true;
			}

			if((player1HasWon == false) && (player2HasWon == false))
			{
				backGround.update(0.2f);
				gameMap.Update(input);

				//update health bars
				for(int i = 0; i < int(player1Units.size()); i++)
				{
					player1HealthBars[i].update(player1Units[i].x + player1Units[i].xOffset/2, player1Units[i].y + player1HealthBars[i].yOffset, player1Units[i].healthValue);
					//Check if units is dead
					if(player1Units[i].healthValue <= 0)
					{
						gameMap.hexMapArray[player1Units[i].hexGridX][player1Units[i].hexGridY].isOccupied = false;
						player1Units.erase(player1Units.begin() + i);
						readyToMove = false;
					}
				}

				//update health bars
				for(int i = 0; i < int(player2Units.size()); i++)
				{
					player2HealthBars[i].update(player2Units[i].x + player2Units[i].xOffset/2, player2Units[i].y + player2HealthBars[i].yOffset, player2Units[i].healthValue);
					//Check if units is dead
					if(player2Units[i].healthValue <= 0)
					{
						gameMap.hexMapArray[player2Units[i].hexGridX][player2Units[i].hexGridY].isOccupied = false;
						player2Units.erase(player2Units.begin() + i);
						readyToMove = false;
					}
				}

				if((turnPieceCounter < int(player1Units.size())) && (isPlayer1Turn == true))
				{
					testint = player1Units[0].healthValue;

					if((player1Units[turnPieceCounter].hasMoved == false) && (isPlayer1Turn == true) && (player1Units[turnPieceCounter].hasAttacked == false))
					{
						movePhase(player1Units[turnPieceCounter],input,gameMap);
						readyToAttack = false;
						input.leftButtonDown = false;
					}
					else if((player1Units[turnPieceCounter].hasMoved == true) && (isPlayer1Turn == true) && (player1Units[turnPieceCounter].hasAttacked == false))
					{
						attackPhase(player1Units[turnPieceCounter],input,gameMap);
						readyToMove = false;
						input.leftButtonDown = false;
					}
					//check if player1isDone
					if(turnPieceCounter >= int(player1Units.size()))
					{
						isPlayer1Turn = false;
						isPlayer2Turn = true;
 						turnPieceCounter = 0;
						//reset player2s peices, should really be a function but im short on time
						for(int i = 0; i < int(player2Units.size()); i++)
						{
							player2Units[i].hasMoved = false;
							player2Units[i].hasAttacked = false;
							readyToSkip = false;	//just in case
					
							//There was a problem with skipping, and this seems counter intuitive, but when player 2 starts, windowsinput seems to set everything back to false again, including enter, setting it to true here makes it work right. Trust me.
							input.keys[VK_ENTER] = true;

							readyToAttack = false;
							//readyToMove = false;
							input.leftButtonDown = false;
						}
					}
				}
				if((turnPieceCounter < int(player2Units.size())) && (isPlayer2Turn == true))
				{
					if((player2Units[turnPieceCounter].hasMoved == false) && (isPlayer2Turn == true) && (player2Units[turnPieceCounter].hasAttacked == false))
					{
						movePhase(player2Units[turnPieceCounter],input,gameMap);
						readyToAttack = false;
						input.leftButtonDown = false;
					}
					else if((player2Units[turnPieceCounter].hasMoved == true) && (isPlayer2Turn == true) && (player2Units[turnPieceCounter].hasAttacked == false))
					{
						attackPhase(player2Units[turnPieceCounter],input,gameMap);
						readyToMove = false;
						input.leftButtonDown = false;
					}
					//check if player2isDone
					if(turnPieceCounter >= int(player2Units.size()))
					{

						isPlayer1Turn = true;
						isPlayer2Turn = false;
						turnPieceCounter = 0;

						//reset player1s peices, should really be a function but im short on time
						for(int i = 0; i < int(player1Units.size()); i++)
						{
							player1Units[i].hasMoved = false;
							player1Units[i].hasAttacked = false;
							readyToSkip = false;	//just in case

							//see above, although it dosent actually seem to be needed here, but it dosent hurt, could stop bugs in the future ... or make em.
							input.keys[VK_ENTER] = true;
							readyToAttack = false;
							readyToMove = false;
							input.leftButtonDown = false;
						}
					}
				}
			}
		}
	}
}

void GameManager::setup(HWND hwnd)
{
	isOnStartScreen = true;
	readyToSkip = true;
	readyToPause = true;
	pauseScreen.setup(225,205,1,1,"PauseScreen.bmp");
	isPaused = false;
	startScreen.setup(0,0,0,0,"SplashScreen.bmp");
	player1Victory.setup(0,0,1,1,"Player1Victory.bmp",hwnd);
	player2Victory.setup(0,0,1,1,"Player2Victory.bmp",hwnd);
}

void GameManager::setupBoard(HWND hwnd, WindowsInput input)
{
	int xOffset = 5;
	int yOffset = 8;

	int mapWidth = 30;
	int mapHeight = 24;

	turnPieceCounter = 0;
	isPlayer1Turn = true;
	isPlayer2Turn = false;

	player1HasWon = false;
	player2HasWon = false;

	HexTile defaultHex;

	GetClientRect(hwnd, &windowDimensions);

	gameMap.setup(hwnd,mapWidth,mapHeight,xOffset,yOffset);

	backGround.setup(0,-150,2,2,"CloudScape.bmp",hwnd);
	int tileWidth = gameMap.hexMapArray[0][0].tileWidth;
	int tileHeight = gameMap.hexMapArray[0][0].tileHeight;
	
	gameMap.generateNewMap();
	setupUnits();

}

bool GameManager::placeUnits(int player)
{
	HexTile defaultTile;
	int tileWidth = defaultTile.tileWidth;
	int tileHeight = defaultTile.tileHeight;

	if((player < 1) || (player > 2))
	{
		//return false;
	}
	if(player == 1)
	{
		for(int i = 0; i < int(player1Units.size()); i++)
		{
			for(int j = 0; j < gameMap.mapWidth; j++)
			{
				for(int k = 0; k < gameMap.mapHeight; k++)
				{
					if((gameMap.hexMapArray[j][k].hexTerrain == HexTile::Grass) || (gameMap.hexMapArray[j][k].hexTerrain == HexTile::Forest))
					{
						if(gameMap.hexMapArray[j][k].isOccupied == false)
						{	
							player1Units[i].hasMoved = false;
							player1Units[i].healthValue = 100;
							player1Units[i].moveUnit(j,k,gameMap);
							j = gameMap.mapWidth;
							k = gameMap.mapHeight;
						}
					}
				}
			}
		}
	}
	else if(player == 2)
	{
		for(int i = 0; i < int(player2Units.size()); i++)
		{
			for(int j = gameMap.mapWidth - 1; j > 0; j--)
			{
				for(int k = gameMap.mapHeight - 1; k > 0; k--)
				{
					if((gameMap.hexMapArray[j][k].hexTerrain == HexTile::Grass) || (gameMap.hexMapArray[j][k].hexTerrain == HexTile::Forest))
					{
						if(gameMap.hexMapArray[j][k].isOccupied == false)
						{	
							player2Units[i].hasMoved = false;
							player2Units[i].moveUnit(j,k,gameMap);
							player2Units[i].healthValue = 100;
							j = 0;
							k = 0;
						}
					}
				}
			}
		}
	}

	if((player1Units.size() < noOfPlayer1Units) || (player2Units.size() < noOfPlayer2Units))
	{
		setupUnits();
	}

	return true;
}

void GameManager::setupUnits()
{
	HexTile defaultTile;

	int tileHeight = defaultTile.tileHeight;
	int tileWidth = defaultTile.tileWidth;

	player1Units.clear();
	player2Units.clear();

	Archer player1Archer;
	Archer player2Archer;
	Infantry player1Infantry;
	Infantry player2Infantry;
	player1Archer.setup(0,0,tileWidth,tileHeight,Unit::Dwarf,"TileSheet.bmp");
	player2Archer.setup(0,0,tileWidth,tileHeight,Unit::Human,"TileSheet.bmp");
	player1Infantry.setup(0,0,tileWidth,tileHeight,Unit::Dwarf,"TileSheet.bmp");
	player2Infantry.setup(0,0,tileWidth,tileHeight,Unit::Human,"TileSheet.bmp");
	player1Units.push_back(player1Archer);
	player1Units.push_back(player1Archer);
	player1Units.push_back(player1Archer);
	player1Units.push_back(player1Infantry);
	player1Units.push_back(player1Infantry);
	player2Units.push_back(player2Archer);
	player2Units.push_back(player2Archer);
	player2Units.push_back(player2Archer);
	player2Units.push_back(player2Infantry);
	player2Units.push_back(player2Infantry);


	noOfPlayer1Units = player1Units.size();
	noOfPlayer2Units = player2Units.size();

	HealthBar tempHealthBar;
	tempHealthBar.setup(0,0,120,5,12,4,"TileSheet.bmp");
	//generate the health bars
	for(int i = 0; i < int(player1Units.size()); i++)
	{
		player1HealthBars.push_back(tempHealthBar);
	}
	for(int i = 0; i < int(player2Units.size()); i++)
	{
		player2HealthBars.push_back(tempHealthBar);
	}
	placeUnits(1);
	placeUnits(2);
}

void GameManager::render(HDC bitmapHDC, HDC backHDC)
{
	if(isOnStartScreen == true)
	{
		startScreen.draw(bitmapHDC,backHDC);
	}
	else if(isOnStartScreen == false)
	{

		if(player1HasWon == true)
		{
			player1Victory.draw(bitmapHDC,backHDC);
		}
		else if(player2HasWon == true)
		{
			player2Victory.draw(bitmapHDC,backHDC);
		}
		else
		{
			backGround.drawTrans(bitmapHDC,backHDC);
			gameMap.render(bitmapHDC,backHDC);
			for(int i = 0; i < int(player1Units.size()); i++)
			{
				player1Units[i].render(bitmapHDC, backHDC);
				player1HealthBars[i].drawTrans(bitmapHDC, backHDC);
			}
			for(int i = 0; i < int(player2Units.size()); i++)
			{
				player2Units[i].render(bitmapHDC, backHDC);
				player2HealthBars[i].drawTrans(bitmapHDC, backHDC);
			}
		}
		if(isPaused == true)
		{
			pauseScreen.draw(bitmapHDC,backHDC);
		}
	}
}

