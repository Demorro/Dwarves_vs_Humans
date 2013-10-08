#include "HexTile.h"


HexTile::HexTile()
{
	setupSpecificVariables(-10,-10,"TileSheet.bmp");

	changeTileType();	
}



HexTile::HexTile(int xPos, int yPos, LPSTR imagePath)
{
	setupSpecificVariables(float(xPos),float(yPos),"TileSheet.bmp");
	changeTileType();		
}

void HexTile::setup(int xPos, int yPos, LPSTR imagePath)
{
	setupSpecificVariables(float(xPos),float(yPos),"TileSheet.bmp");
	changeTileType();
}

HexTile::~HexTile(void)
{
}

void HexTile::drawTrans(HDC bitmapHDC, HDC backHDC)
{
	
	HBITMAP originalBitMap;
	originalBitMap = (HBITMAP)SelectObject(bitmapHDC, bitmap);
	TransparentBlt(backHDC, int(x * scaleFactorX), int(y * scaleFactorY), width * scaleFactorX, height * scaleFactorY, bitmapHDC, sourceX, sourceY, sourceWidth, sourceHeight, TRANSPARENT_MASK);
	SelectObject(bitmapHDC,originalBitMap); 
}

void HexTile::setTerrain(terrainType newTerrain)
{
	hexTerrain = newTerrain;
	changeTileType();
	//Set the moveCost for pathfinding
	if(startTerrain == Water)
	{
		moveCost = 500; //Thus impossible to move over
		rangedAttackCost = 2;
		meleeAttackCost = 2;
	}
	else if(startTerrain == Forest)
	{
		moveCost = 4;
		rangedAttackCost = 6;
		meleeAttackCost = 2;
	}
	else
	{
		moveCost = 2;
		rangedAttackCost = 2;
		meleeAttackCost = 2;
	}

	 if(isRoad == true)
	{
		moveCost = 1;
		rangedAttackCost = 2;
		meleeAttackCost = 2;
	}
}

void HexTile::changeTileType()
{
	switch(hexTerrain)
	{
		case Water :
			sourceX = int(spriteSheetPos_Water.x);
			sourceY = int(spriteSheetPos_Water.y);
			isRoad = false;
			isTurningRoad = false;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case Grass :
			sourceX = int(spriteSheetPos_Grass.x);
			sourceY = int(spriteSheetPos_Grass.y);
			isRoad = false;
			isTurningRoad = false;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case Forest :
			sourceX = int(spriteSheetPos_Forest.x);
			sourceY = int(spriteSheetPos_Forest.y);
			isRoad = false;
			isTurningRoad = false;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case LongGrass :
			sourceX = int(spriteSheetPos_LongGrass.x);
			sourceY = int(spriteSheetPos_LongGrass.y);
			isRoad = false;
			isTurningRoad = false;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case Snow :
			sourceX = int(spriteSheetPos_Snow.x);
			sourceY = int(spriteSheetPos_Snow.y);
			isRoad = false;
			isTurningRoad = false;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		//roads from here on
		case horizontalPath :
			sourceX = int(spriteSheetPos_horizontalPath.x);
			sourceY = int(spriteSheetPos_horizontalPath.y);
			isRoad = true;
			isTurningRoad = false;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case leftDiagonalPath :
			sourceX = int(spriteSheetPos_leftDiagonalPath.x);
			sourceY = int(spriteSheetPos_leftDiagonalPath.y);
			isRoad = true;
			isTurningRoad = false;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case rightDiagonalPath :
			sourceX = int(spriteSheetPos_rightDiagonalPath.x);
			sourceY = int(spriteSheetPos_rightDiagonalPath.y);
			isRoad = true;
			isTurningRoad = false;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case horizontalToRightTopPath :
			sourceX = int(spriteSheetPos_horizontalToRightTopPath.x);
			sourceY = int(spriteSheetPos_horizontalToRightTopPath.y);
			isRoad = true;
			isTurningRoad = true;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case horizontalToRightBottomPath :
			sourceX = int(spriteSheetPos_horizontalToRightBottomPath.x);
			sourceY = int(spriteSheetPos_horizontalToRightBottomPath.y);
			isRoad = true;
			isTurningRoad = true;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case leftTopToHorizontalPath :
			sourceX = int(spriteSheetPos_leftTopToHorizontalPath.x);
			sourceY = int(spriteSheetPos_leftTopToHorizontalPath.y);
			isRoad = true;
			isTurningRoad = true;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case leftBottomToHorizontalPath :
			sourceX = int(spriteSheetPos_leftBottomToHorizontalPath.x);
			sourceY = int(spriteSheetPos_leftBottomToHorizontalPath.y);
			isRoad = true;
			isTurningRoad = true;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case leftTopToLeftBottomPath :
			sourceX = int(spriteSheetPos_leftTopToLeftBottomPath.x);
			sourceY = int(spriteSheetPos_leftTopToLeftBottomPath.y);
			isRoad = true;
			isTurningRoad = true;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case rightTopToRightBottomPath :
			sourceX = int(spriteSheetPos_rightTopToRightBottomPath.x);
			sourceY = int(spriteSheetPos_rightTopToRightBottomPath.y);
			isRoad = true;
			isTurningRoad = true;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case horizontalAndLeftDiagonalCross :
			sourceX = int(spriteSheetPos_horizontalAndLeftDiagonalCross.x);
			sourceY = int(spriteSheetPos_horizontalAndLeftDiagonalCross.y);
			isRoad = true;
			isTurningRoad = true;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case horizontalAndRightDiagonalCross :
			sourceX = int(spriteSheetPos_horizontalAndRightDiagonalCross.x);
			sourceY = int(spriteSheetPos_horizontalAndRightDiagonalCross.y);
			isRoad = true;
			isTurningRoad = true;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case leftDiagonalAndRightDiagonalCross :
			sourceX = int(spriteSheetPos_leftDiagonalAndRightDiagonalCross.x);
			sourceY = int(spriteSheetPos_leftDiagonalAndRightDiagonalCross.y);
			isRoad = true;
			isTurningRoad = true;
			isMoveGrid = false;
			isAttackGrid = false;
			break;
		case moveSelection :
			sourceX = int(spriteSheetPos_moveSelection.x);
			sourceY = int(spriteSheetPos_moveSelection.y);
			isMoveGrid = true;
			isAttackGrid = false;
			//THERE IS NO SETTING ROADS HERE IN CASE BUGS HAPPEN, REMEMBER
			break;
		case attackSelection :
			sourceX = int(spriteSheetPos_attackSelection.x);
			sourceY = int(spriteSheetPos_attackSelection.y);
			isMoveGrid = false;
			isAttackGrid = true;
			break;	
	}
}

void HexTile::setupSpecificVariables(float xPos, float yPos, LPSTR imagePath)
{

	bitmap = LoadABitmap(imagePath);
	if (!bitmap)
	{
		//MessageBox(NULL, "File Not Loaded",imagePath, MB_OK);
	}
		
	isRoad = false;
	isOccupied = false;

	x = xPos;
	y = yPos;
	findDimensions();

	pathFindingValue = 0;
	checkPathfinding = true;

	hexTerrain = Grass;

	shouldCheckGen = true;
	
	isMoveGrid = false;
	isAttackGrid = false;

	scaleFactorX = 2;
	scaleFactorY = 2;

	spriteSheetPos_Water.x = 1;
	spriteSheetPos_Water.y = 1;

	spriteSheetPos_Grass.x = 22;
	spriteSheetPos_Grass.y = 1;

	spriteSheetPos_Forest.x = 43;
	spriteSheetPos_Forest.y = 1;

	spriteSheetPos_LongGrass.x = 64;
	spriteSheetPos_LongGrass.y = 1;

	spriteSheetPos_Snow.x = 85;
	spriteSheetPos_Snow.y = 1;

	spriteSheetPos_horizontalPath.x = 206;
	spriteSheetPos_horizontalPath.y = 1;

	spriteSheetPos_leftDiagonalPath.x = 227;
	spriteSheetPos_leftDiagonalPath.y = 1;

	spriteSheetPos_rightDiagonalPath.x = 248;
	spriteSheetPos_rightDiagonalPath.y = 1;

	spriteSheetPos_horizontalToRightTopPath.x = 206;
	spriteSheetPos_horizontalToRightTopPath.y = 24;

	spriteSheetPos_horizontalToRightBottomPath.x = 206;
	spriteSheetPos_horizontalToRightBottomPath.y = 47;

	spriteSheetPos_leftTopToHorizontalPath.x = 206;
	spriteSheetPos_leftTopToHorizontalPath.y = 70;

	spriteSheetPos_leftBottomToHorizontalPath.x = 206;
	spriteSheetPos_leftBottomToHorizontalPath.y = 93;

	spriteSheetPos_leftTopToLeftBottomPath.x = 227;
	spriteSheetPos_leftTopToLeftBottomPath.y = 47;

	spriteSheetPos_rightTopToRightBottomPath.x = 227;
	spriteSheetPos_rightTopToRightBottomPath.y = 70;

	spriteSheetPos_horizontalAndLeftDiagonalCross.x = 248;
	spriteSheetPos_horizontalAndLeftDiagonalCross.y = 24;

	spriteSheetPos_horizontalAndRightDiagonalCross.x = 248;
	spriteSheetPos_horizontalAndRightDiagonalCross.y = 47;

	spriteSheetPos_leftDiagonalAndRightDiagonalCross.x = 248;
	spriteSheetPos_leftDiagonalAndRightDiagonalCross.y = 70;

	spriteSheetPos_moveSelection.x = 64;
	spriteSheetPos_moveSelection.y = 30;

	spriteSheetPos_attackSelection.x = 85;
	spriteSheetPos_attackSelection.y = 30;


	width = tileWidth;
	height = tileHeight;
	sourceWidth = tileWidth;
	sourceHeight = tileHeight;
}
