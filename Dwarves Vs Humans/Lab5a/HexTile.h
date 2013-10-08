#pragma once
#include "WindowsSprite.h"
#include "Vector2.h"


using namespace std;

class HexTile : public WindowsSprite
{
public:
	static const int tileWidth = 20;
	static const int tileHeight = 22;

	//Scales x and y for the tiles, probably wont be changed through the code
	int scaleFactorX;
	int scaleFactorY;

	//Adjusting these should change the rect used on the spriteSheet
	int sourceX;
	int sourceY;

	int sourceWidth;
	int sourceHeight;

	bool isOccupied;

	//pathFindingValue for orderGrids
	int pathFindingValue;
	bool checkPathfinding;
	bool isMoveGrid;
	int moveCost;

	bool isAttackGrid;
	int rangedAttackCost;
	int meleeAttackCost;

	//gridPositions
	int hexGridX;
	int hexGridY;

	bool shouldCheckGen;

	enum terrainType
	{
		Water,
		Grass,
		Forest,
		LongGrass,
		Snow,
		horizontalPath,
		leftDiagonalPath,
		rightDiagonalPath,
		horizontalToRightTopPath,
		horizontalToRightBottomPath,
		leftTopToHorizontalPath,
		leftBottomToHorizontalPath,
		leftTopToLeftBottomPath,
		rightTopToRightBottomPath,
		horizontalAndLeftDiagonalCross,
		horizontalAndRightDiagonalCross,
		leftDiagonalAndRightDiagonalCross,
		moveSelection,
		attackSelection,
	};

	terrainType hexTerrain;
	terrainType startTerrain; //stores the startTerrain so we can toggle it back if and when its changed.

	Vector2 spriteSheetPos_Water;
	Vector2 spriteSheetPos_Grass;
	Vector2 spriteSheetPos_Forest;
	Vector2 spriteSheetPos_LongGrass;
	Vector2 spriteSheetPos_Snow;
	Vector2 spriteSheetPos_horizontalPath;
	Vector2 spriteSheetPos_leftDiagonalPath;
	Vector2 spriteSheetPos_rightDiagonalPath;
	Vector2 spriteSheetPos_horizontalToRightTopPath;
	Vector2 spriteSheetPos_horizontalToRightBottomPath;
	Vector2 spriteSheetPos_leftTopToHorizontalPath;
	Vector2 spriteSheetPos_leftBottomToHorizontalPath;
	Vector2 spriteSheetPos_leftTopToLeftBottomPath;
	Vector2 spriteSheetPos_rightTopToRightBottomPath;
	Vector2 spriteSheetPos_horizontalAndLeftDiagonalCross;
	Vector2 spriteSheetPos_horizontalAndRightDiagonalCross;
	Vector2 spriteSheetPos_leftDiagonalAndRightDiagonalCross;
	Vector2 spriteSheetPos_moveSelection;
	Vector2 spriteSheetPos_attackSelection;


	bool isRoad;
	bool isTurningRoad;

	void drawTrans(HDC bitmapHDC, HDC backHDC);
	void setup(int xPos, int yPos, LPSTR imagePath);

	void setTerrain(terrainType); //Use this to change the terrain type of a cell
		
	HexTile();
	HexTile(int xPos, int yPos, LPSTR imagePath);
	~HexTile(void);

private:
	void changeTileType();
	void setupSpecificVariables(float xPos, float yPos, LPSTR imagePath);
};

