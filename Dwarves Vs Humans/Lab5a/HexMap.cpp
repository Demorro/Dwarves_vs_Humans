#include "HexMap.h"
#include <vector>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Vector2.h"
#include <iostream>
#include "HexHighlight.h"
#include <math.h>

using namespace std;

HexMap::HexMap(void)
{
	
}


HexMap::~HexMap(void)
{
}

void HexMap::setup(HWND hwnd, int mapX, int mapY, int xOffset, int yOffset)
{
	mapWidth = mapX;
	mapHeight = mapY;

	mapOffsetX = xOffset;
	mapOffsetY = yOffset;

	GetClientRect(hwnd, &windowDimensions);

	HexTile defaultHex;
	
	highlightTile.setup(0,0,"TileSheet.bmp");
	renderHighlight = false;

	unitHighlightTile.setup(0,0,"TileSheet.bmp");
	renderUnitHighlight = false;

	for(int i = 0; i < mapWidth; i++)
	{

		hexMapArray.push_back(emptyHexVector);

		for(int j = 0; j < mapHeight; j++)
		{
			if(j%2 != 0) //if this is an odd line, shift it along by half a hex to facilitate the hex effect
			{
				defaultHex.setup(((i * defaultHex.tileWidth) + (defaultHex.tileWidth/2)) + mapOffsetX, (j * (defaultHex.tileHeight - verticalStackOffset)) + mapOffsetY, "TileSheet.bmp");
				defaultHex.hexGridX = i;
				defaultHex.hexGridY = j;
				hexMapArray[i].push_back(defaultHex);

			}
			else
			{
				defaultHex.setup((i * defaultHex.tileWidth) + mapOffsetX, (j * (defaultHex.tileHeight - verticalStackOffset)) + mapOffsetY, "TileSheet.bmp");
				defaultHex.hexGridX = i;
				defaultHex.hexGridY = j;
				hexMapArray[i].push_back(defaultHex);
			}
		}
	}
}

void HexMap::Update(WindowsInput input)
{
	highlightActiveTile(input);
}

void HexMap::highlightActiveTile(WindowsInput input)
{
	HexTile defaultHex;

	int scaleX = hexMapArray[0][0].scaleFactorX;
	int scaleY = hexMapArray[0][0].scaleFactorY;

	int tileHeight = defaultHex.tileHeight;
	int tileWidth = defaultHex.tileWidth;

	int hexMouseX = input.mouseX - mapOffsetX * scaleX;
	int hexMouseY = input.mouseY - mapOffsetY * scaleY;

	bool isOddLine = false;

	//Deal with the shifted along hexes
	if(int(hexMouseY) / ((tileHeight - verticalStackOffset)*scaleY) %2 != 0)
	{
		hexMouseX += (tileWidth * (scaleX/2));
		isOddLine = true;
	}

	renderHighlight = false;
	if(isOddLine == true)
	{
		if((hexMouseY > 0) && (hexMouseX > (tileWidth * scaleX)))
		{
			if((hexMouseY < (mapHeight * (tileHeight - verticalStackOffset) * scaleY)) && (hexMouseX < ((mapWidth + 1) * tileWidth * scaleX)))
			{
				renderHighlight = true;
			
				highlightTile.y = float(((hexMouseY) / ((tileHeight - verticalStackOffset)*scaleY)) * (tileHeight - verticalStackOffset));
				highlightTile.y += mapOffsetY;
				highlightTile.x = float(((hexMouseX) / ((tileWidth)*scaleX)) * (tileWidth));
				highlightTile.x += mapOffsetX;

				//on a shifted line
				//ello = ceilf((highlightTile.x/((tileWidth) * scaleX)) * 2) - 2; the array value for x
				//ello = ceilf((highlightTile.y/((tileHeight - 8) * scaleY)) * 2) - 1; The array value for y


				if(int(hexMouseY) / ((tileHeight - verticalStackOffset)*scaleY) %2 != 0)
				{
					highlightTile.x -= (tileWidth/2);
				}
			}
		}
	}
	else if(isOddLine == false)
	{
		if((hexMouseY > 0) && (hexMouseX > 0))
		{
			if((hexMouseY < (mapHeight * (tileHeight - verticalStackOffset) * scaleY)) && (hexMouseX < (mapWidth * tileWidth * scaleX)))
			{
				renderHighlight = true;
			
				highlightTile.y = float(((hexMouseY) / ((tileHeight - verticalStackOffset)*scaleY)) * (tileHeight - verticalStackOffset));
				highlightTile.y += mapOffsetY;
				highlightTile.x = float(((hexMouseX) / ((tileWidth)*scaleX)) * (tileWidth));
				highlightTile.x += mapOffsetX;

				//on a non shifted line
				//ello = ceilf((highlightTile.x/((tileWidth) * scaleX)) * 2) - 1; the array value for x
				//ello = ceilf((highlightTile.y/((tileHeight - 8) * scaleY)) * 2) - 1; the array value for y


				if(int(hexMouseY) / ((tileHeight - verticalStackOffset)*scaleY) %2 != 0)
				{
					highlightTile.x -= (tileWidth/2);
				}
			}
		}
	}
}

void HexMap::highlightSetTile(int xGrid, int yGrid)
{

	
	
	HexTile defaultHex;

	int scaleX = hexMapArray[0][0].scaleFactorX;
	int scaleY = hexMapArray[0][0].scaleFactorY;

	int tileHeight = defaultHex.tileHeight;
	int tileWidth = defaultHex.tileWidth;

	bool isOddLine = false;

	//deal with odd lines
	if(yGrid % 2 != 0)
	{
		isOddLine = true;
	}

	renderUnitHighlight = true;
	if(isOddLine == true)
	{
			
		unitHighlightTile.y = yGrid * (tileHeight - verticalStackOffset);
		unitHighlightTile.y += mapOffsetY;
		unitHighlightTile.x = xGrid * tileWidth;
		unitHighlightTile.x += mapOffsetX;

		unitHighlightTile.x += (tileWidth/2);
	}
	else if(isOddLine == false)
	{
			
		unitHighlightTile.y = yGrid * (tileHeight - verticalStackOffset);
		unitHighlightTile.y += mapOffsetY;
		unitHighlightTile.x = xGrid * tileWidth;
		unitHighlightTile.x += mapOffsetX;
	}
	
}

void HexMap::unHighlightSetTile()
{
	renderUnitHighlight = false;
}

void HexMap::render(HDC bitMapHDC,HDC backHDC)
{

	for(int i = 0; i < mapHeight; i++)
	{
		for(int j = 0; j < mapWidth; j++)
		{
			//need to do this inverted so it draws to to bottom as opposed to left to right
			hexMapArray[j][i].drawTrans(bitMapHDC,backHDC);
		}
	}
	if(renderHighlight == true)
	{
		highlightTile.drawTrans(bitMapHDC,backHDC);
	}
	if(renderUnitHighlight == true)
	{
		unitHighlightTile.drawTrans(bitMapHDC,backHDC);
	}
}

void HexMap::generateNewMap()
{
	srand(time(NULL));

	clearQueue(workingSet);
	cleanMap(HexTile::Grass); //sets the map to all one tile, changine this can maybe generate water based maps or something
	generateTerrainExpanse(HexTile::Forest,8,4,35,10); //Generate Forests
	generateTerrainExpanse(HexTile::Forest,8,4,35,10); //Generate Forests
	generateTerrainExpanse(HexTile::Water,12,4,40,10); //Generate Lakes
	generateRoad(12);
	generateRoad(12);
	//set start terrains
	for(int i = 0; i < mapWidth; i++)
	{
		for(int j = 0; j < mapHeight; j++)
		{
			hexMapArray[i][j].startTerrain = hexMapArray[i][j].hexTerrain;
			hexMapArray[i][j].pathFindingValue = 0;
			hexMapArray[i][j].checkPathfinding = true;
		}
	}
	
}

void HexMap::generateTerrainExpanse(HexTile::terrainType terrain, int maxNumOfLocations, int minNumOfLocations, int maxNumOfTiles, int minNumOfTiles)
{
	HexTile currentTile;
	
	int numOfLocations = rand() % maxNumOfLocations + minNumOfLocations;

	for(int i = 0; i < numOfLocations; i++)
	{
		//get a random location for an expanse
		int currentXLoc = rand() % mapWidth;
		int currentYLoc = rand() % mapHeight;
		hexMapArray[currentXLoc][currentYLoc].setTerrain(terrain);

		int numOfTilesInExpanse = rand() % maxNumOfTiles + minNumOfTiles;
		for(int i = 0; i < numOfTilesInExpanse; i++) //fill the expanse using a random adjacent tile and the number of tiles there should be
		{
			//generate a random direction(8 directions)
			int direction = rand() % 8 + 1;
			switch(direction)
			{
				//All the if statements prevent from vector overflows on the edge of the map
				case 1: //North
					if(currentYLoc > 0)
					{
						currentYLoc--;
					}
					hexMapArray[currentXLoc][currentYLoc].setTerrain(terrain);
					break;
				case 2: //North-East
					if(currentXLoc < (mapWidth - 1))
					{
						currentXLoc++;
					}
					if(currentYLoc > 0)
					{
						currentYLoc--;
					}
					hexMapArray[currentXLoc][currentYLoc].setTerrain(terrain);
					break;
				case 3: //East
					if(currentXLoc < (mapWidth - 1))
					{
						currentXLoc++;
					}
					hexMapArray[currentXLoc][currentYLoc].setTerrain(terrain);
					break;
				case 4: //South-East
					if(currentXLoc < (mapWidth - 1))
					{
						currentXLoc++;

					}
					if(currentYLoc < (mapHeight - 1))
					{
						currentYLoc++;
					}
					hexMapArray[currentXLoc][currentYLoc].setTerrain(terrain);
					break;
				case 5: //South
					if(currentYLoc < (mapHeight - 1))
					{
						currentYLoc++;
					}
					hexMapArray[currentXLoc][currentYLoc].setTerrain(terrain);
					break;
				case 6: //South-West
					if(currentXLoc > 0)
					{
						currentXLoc--;
					}
					if(currentYLoc < (mapHeight - 1))
					{
						currentYLoc++;
					}
					hexMapArray[currentXLoc][currentYLoc].setTerrain(terrain);
					break;
				case 7: //West
					if(currentXLoc > 0)
					{
						currentXLoc--;
					}
					hexMapArray[currentXLoc][currentYLoc].setTerrain(terrain);
					break;
				case 8: //North-West
					if(currentXLoc > 0)
					{
						currentXLoc--;
					}
					if(currentYLoc > 0)
					{
						currentYLoc--;
					}
					hexMapArray[currentXLoc][currentYLoc].setTerrain(terrain);
					break;
				default:
					cout << ("Filling expanse failed in switch");

			}

		}
	}
}

void HexMap::generateRoad(int veerChance)
{
	bool pathGenEnded;
	std::queue<HexTile> pathList;

	//pick an edge
	int edge = rand() % 2 + 1;
	int startPoint = 0;
	int pathDirection = 0; //6 directions, 0 = NE, 1 = E, 2 = SE, 3 = SW, 4 = W, 5 = NW
	bool regenPathStart = false;
	Vector2 currentPos;

	//Find the start
	if(edge == 1) //left edge
	{
		//pick a random point along the edge and set it to the relevent path
		do
		{
			startPoint = rand() % mapHeight;
			for(int i = 0; i < int(roadStartPoints.size()); i++)
			{
				if(roadStartPoints[i].y == startPoint)
				{
					regenPathStart = true;
				}
				else
				{
					regenPathStart = false;
				}
			}
		} while(regenPathStart == true);
		hexMapArray[0][startPoint].setTerrain(HexTile::horizontalPath);
		currentPos.x = 0;
		currentPos.y = float(startPoint);
		pathDirection = 1;
		roadStartPoints.push_back(Vector2());
		roadStartPoints.back().x = currentPos.x;
		roadStartPoints.back().y = currentPos.y;
	}
	/*
	else if(edge == 2) //top edge
	{
		//pick a random point along the edge and set it to the relevent path
		do
		{
			startPoint = rand() % mapWidth;
			for(int i = 0; i < roadStartPoints.size(); i++)
			{
				if(roadStartPoints[i].x == startPoint)
				{
					regenPathStart = true;
				}
				else
				{
					regenPathStart = false;
				}
			}
		} while(regenPathStart == true);
		hexMapArray[startPoint][0].setTerrain(HexTile::rightDiagonalPath);
		currentPos.x = startPoint;
		currentPos.y = 0;
		pathDirection = 3;
		roadStartPoints.push_back(Vector2());
		roadStartPoints.back().x = currentPos.x;
		roadStartPoints.back().y = currentPos.y;
		
	}
	*/
	else if(edge == 2) //right edge
	{
		//pick a random point along the edge and set it to the relevent path
		do
		{
			startPoint = rand() % mapHeight;
			for(int i = 0; i < int(roadStartPoints.size()); i++)
			{
				if(roadStartPoints[i].y == startPoint)
				{
					regenPathStart = true;
				}
				else
				{
					regenPathStart = false;
				}
			}
		} while(regenPathStart == true);
		hexMapArray[mapWidth - 1][startPoint].setTerrain(HexTile::horizontalPath);
		currentPos.x = float(mapWidth - 1);
		currentPos.y = float(startPoint);
		pathDirection = 4;
		roadStartPoints.push_back(Vector2());
		roadStartPoints.back().x = currentPos.x;
		roadStartPoints.back().y = currentPos.y;
	}
	/*
	else if(edge == 4) //bottom edge
	{
		//pick a random point along the edge and set it to the relevent path
		do
		{
			startPoint = rand() % mapWidth;
			for(int i = 0; i < roadStartPoints.size(); i++)
			{
				if(roadStartPoints[i].x == startPoint)
				{
					regenPathStart = true;
				}
				else
				{
					regenPathStart = false;
				}
			}
		} while(regenPathStart == true);
		hexMapArray[startPoint][mapHeight - 1].setTerrain(HexTile::leftDiagonalPath);
		currentPos.x = startPoint;
		currentPos.y = mapHeight - 1;
		pathDirection = 5;
		roadStartPoints.push_back(Vector2());
		roadStartPoints.back().x = currentPos.x;
		roadStartPoints.back().y = currentPos.y;
	}
	*/

	pathGenEnded = false;


	while(pathGenEnded == false)
	{
		pathList.push(hexMapArray[int(currentPos.x)][int(currentPos.y)]);
		int randomVeerNum;
		randomVeerNum = rand() % 100 + 1;

		if(randomVeerNum < veerChance) //should veer off this time
		{
			if(rand()% 2 == 1)
			{
				pathDirection++;
				if(pathDirection == 1)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::leftBottomToHorizontalPath);
				}
				else if(pathDirection == 2)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::horizontalToRightBottomPath);
				}
				else if(pathDirection == 3)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::leftTopToLeftBottomPath);
				}
				else if(pathDirection == 4)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::horizontalToRightTopPath);
				}
				else if(pathDirection == 5)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::leftTopToHorizontalPath);
				}
				else if(pathDirection == 6)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::rightTopToRightBottomPath);
				}
			}
			else
			{
				pathDirection--;
				if(pathDirection == -1)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::leftTopToLeftBottomPath);
				}
				else if(pathDirection == 0)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::horizontalToRightTopPath);
				}
				else if(pathDirection == 1)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::leftTopToHorizontalPath);
				}
				else if(pathDirection == 2)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::rightTopToRightBottomPath);
				}
				else if(pathDirection == 3)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::leftBottomToHorizontalPath);
				}
				else if(pathDirection == 4)
				{
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::horizontalToRightBottomPath);
				}
			}

			if(pathDirection >= 6)
			{
				pathDirection = 0;
			}
			else if(pathDirection <= -1)
			{
				pathDirection = 5;
			}
		}

		//Check if the path has ended going left
		if((currentPos.x <= 0) && ((pathDirection == 5) || (pathDirection == 4) || (pathDirection == 3)))
		{
			pathGenEnded = true;
			break;
		}
		//and right
		if((currentPos.x >= (mapWidth - 1)) && ((pathDirection == 1) || (pathDirection == 0) || (pathDirection == 2)))
		{
			pathGenEnded = true;
			break;
		}
		//and up
		if((currentPos.y <= 0) && ((pathDirection == 5) || (pathDirection == 0)))
		{
			pathGenEnded = true;
			break;
		}
		//and down
		if((currentPos.y >= (mapHeight - 1)) && ((pathDirection == 3) || (pathDirection == 2)))
		{
			pathGenEnded = true;
			break;
		}

		if((currentPos.x <= (mapWidth - 1)) && (currentPos.x >= 0))
		{
			if((currentPos.y <= (mapHeight - 1)) && (currentPos.y >= 0))
			{
				checkForRoadCrossover(pathDirection,currentPos,pathList,pathGenEnded);
				if(pathDirection == 0) //North East
				{
					if(int(currentPos.y) % 2 != 0) //if we are on a shifted over line
					{
						currentPos.x++;
						currentPos.y--;
						hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::rightDiagonalPath);
					}
					else
					{
						currentPos.y--;
						hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::rightDiagonalPath);
					}
				}
				else if(pathDirection == 1) //East
				{
					currentPos.x++;
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::horizontalPath);
				}
				else if(pathDirection == 2) //South East
				{
					if(int(currentPos.y) % 2 != 0) //if we are on a shifted over line
					{
						currentPos.x++;
						currentPos.y++;
						hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::leftDiagonalPath);
					}
					else
					{
						currentPos.y++;
						hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::leftDiagonalPath);
					}
				}
				else if(pathDirection == 3) //South West
				{
					if(int(currentPos.y) % 2 != 0) //if we are on a shifted over line
					{
						currentPos.y++;
						hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::rightDiagonalPath);
					}
					else
					{
						currentPos.x--;
						currentPos.y++;
						hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::rightDiagonalPath);
					}
				}
				else if(pathDirection == 4) //West
				{
					currentPos.x--;
					hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::horizontalPath);
				}
				else if(pathDirection == 5) //North West
				{
					if(int(currentPos.y) % 2 != 0) //if we are on a shifted over line
					{
						currentPos.y--;
						hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::leftDiagonalPath);
					}
					else
					{
						currentPos.x--;
						currentPos.y--;
						hexMapArray[int(currentPos.x)][int(currentPos.y)].setTerrain(HexTile::leftDiagonalPath);
					}
				}
			}
		}
	}
}

void HexMap::checkForRoadCrossover(int &pathDirection, Vector2 &currentPos, queue<HexTile> workingRoadQueue,bool &pathGenEnded)
{
	if(pathDirection == 0) //North East
	{
		if(int(currentPos.y) % 2 != 0) //if we are on a shifted over line
		{
			if(hexMapArray[int(currentPos.x + 1)][int(currentPos.y - 1)].isRoad == true)
			{
				pathGenEnded = true;
				setQueueToTile(workingRoadQueue,HexTile::Grass);
				//Just to make sure it dosent keep going
				pathDirection = -2;
			}
		}
		else
		{
			if(hexMapArray[int(currentPos.x)][int(currentPos.y - 1)].isRoad == true)
			{
				pathGenEnded = true;
				setQueueToTile(workingRoadQueue,HexTile::Grass);
				//Just to make sure it dosent keep going
				pathDirection = -2;
			}
		}
	}
	else if(pathDirection == 1) //East
	{
		if(hexMapArray[int(currentPos.x + 1)][int(currentPos.y)].isRoad == true)
		{
			pathGenEnded = true;
			setQueueToTile(workingRoadQueue,HexTile::Grass);
			//Just to make sure it dosent keep going
			pathDirection = -2;
		}
	}
	else if(pathDirection == 2) //South East
	{
		if(int(currentPos.y) % 2 != 0) //if we are on a shifted over line
		{
			if(hexMapArray[int(currentPos.x + 1)][int(currentPos.y + 1)].isRoad == true)
			{
				pathGenEnded = true;
				setQueueToTile(workingRoadQueue,HexTile::Grass);
				//Just to make sure it dosent keep going
				pathDirection = -2;
			}
		}
		else
		{
			if(hexMapArray[int(currentPos.x)][int(currentPos.y + 1)].isRoad == true)
			{
				pathGenEnded = true;
				setQueueToTile(workingRoadQueue,HexTile::Grass);
				//Just to make sure it dosent keep going
				pathDirection = -2;
			}
		}
	}
	else if(pathDirection == 3) //South West
	{
		if(int(currentPos.y) % 2 != 0) //if we are on a shifted over line
		{
			if(hexMapArray[int(currentPos.x)][int(currentPos.y + 1)].isRoad == true)
			{
				pathGenEnded = true;
				setQueueToTile(workingRoadQueue,HexTile::Grass);
				//Just to make sure it dosent keep going
				pathDirection = -2;
			}
		}
		else
		{
			if(hexMapArray[int(currentPos.x - 1)][int(currentPos.y + 1)].isRoad == true)
			{
				pathGenEnded = true;
				setQueueToTile(workingRoadQueue,HexTile::Grass);
				//Just to make sure it dosent keep going
				pathDirection = -2;
			}
		}
	}
	else if(pathDirection == 4) //West
	{
		if(hexMapArray[int(currentPos.x - 1)][int(currentPos.y)].isRoad == true)
		{
			pathGenEnded = true;
			setQueueToTile(workingRoadQueue,HexTile::Grass);
			//Just to make sure it dosent keep going
			pathDirection = -2;
		}
	}
	else if(pathDirection == 5) //North West
	{
		if(int(currentPos.y) % 2 != 0) //if we are on a shifted over line
		{
			if(hexMapArray[int(currentPos.x)][int(currentPos.y - 1)].isRoad == true)
			{
				pathGenEnded = true;
				setQueueToTile(workingRoadQueue,HexTile::Grass);
				//Just to make sure it dosent keep going
				pathDirection = -2;
			}
		}
		else
		{
			if(hexMapArray[int(currentPos.x - 1)][int(currentPos.y - 1)].isRoad == true)
			{
				pathGenEnded = true;
				setQueueToTile(workingRoadQueue,HexTile::Grass);
				//Just to make sure it dosent keep going
				pathDirection = -2;
			}
		}
	}
}
void HexMap::setQueueToTile(std::queue<HexTile> tileQueue, HexTile::terrainType tileType)
{
	int size = tileQueue.size();
	for(int i = 0; i < size; i++)
	{
		hexMapArray[tileQueue.front().hexGridX][tileQueue.front().hexGridY].setTerrain(tileType);
		tileQueue.pop();
	}
}
void HexMap::cleanMap(HexTile::terrainType terrain)
{
	for(int i = 0; i < mapWidth; i++)
	{
		for(int j = 0; j < mapHeight; j++)
		{
			hexMapArray[i][j].setTerrain(terrain);
			hexMapArray[i][j].isRoad = false;
			hexMapArray[i][j].isTurningRoad = false;
			hexMapArray[i][j].isOccupied = false;

		}
	}
}

void HexMap::clearQueue(queue<HexTile> &q )
{
   std::queue<HexTile> empty;
   std::swap( q, empty );
}

