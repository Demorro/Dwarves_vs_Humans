
#pragma once

#include "HexTile.h"
#include "Vector2.h"
#include <vector>
#include <windows.h>
#include <queue>
#include "WindowsInput.h"
#include "HexHighlight.h"


using namespace std;

class HexMap
{
public:

	int mapWidth;
	int mapHeight;

	int mapOffsetX;
	int mapOffsetY;

	vector<vector<HexTile>> hexMapArray;
	vector<HexTile> emptyHexVector;

	//Stores the window dimensions so we can use them for all kinds of things
	RECT windowDimensions;

	void setup(HWND hWnd, int mapX, int mapY, int offsetX, int offsetY);
	void render (HDC bitMapHDC,HDC backHDC);
	HexMap(void);
	~HexMap(void);

	void generateNewMap();
	void Update(WindowsInput input);
	void highlightActiveTile(WindowsInput input);
	
	//only one tile may be highlighted at a time, could extend it to n tiles using a vector based approach, but again, time constraints.
	void highlightSetTile(int xGrid, int yGrid);
	void unHighlightSetTile();

	static const int verticalStackOffset = 8;

private:
	//deals with overlaying the tiles so you dont see the dirt

	HexHighlight highlightTile;
	bool renderHighlight;

	HexHighlight unitHighlightTile;
	bool renderUnitHighlight;

	//All this is to do with the flood at the start
	HexTile::terrainType generateTile();
	HexTile::terrainType generateNewTile();
	queue<HexTile> workingSet;
	vector<Vector2> roadStartPoints;
	bool generationActive;
	void clearQueue(queue<HexTile> &q);

	void generateTerrainExpanse(HexTile::terrainType terrain, int maxNumOfLocations, int minNumOfLocations, int maxNumOfTiles, int minNumOfTiles);
	void generateRoad(int veerChance);
	void cleanMap(HexTile::terrainType terrain);
	void setQueueToTile(std::queue<HexTile> tilequeue, HexTile::terrainType tileType);
	void checkForRoadCrossover(int &pathDirection, Vector2 &currentPos,queue<HexTile> workingRoadQueue,bool &pathGenEnded);
	

};

