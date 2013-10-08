#pragma once
#include <vector>
#include "WindowsSprite.h"
#include "WindowsInput.h"
#include "Cell.h"
using namespace std;

class GameBoard
{
public:

	static const int boardWidth = 40;
	static const int boardHeight = 27;


	/*struct cell{
		WindowsSprite cellSprite;
		int xGridPos;
		int yGridPos;
		int pathFindingValue;
		bool isStart;
		bool isEnd;
		bool isWall;
		bool isTraceBack;
		bool hasChanged;
	};
	*/
	Cell boardValues[boardWidth][boardHeight];

	Cell currentStartCell;
	Cell currentEndCell;

	Cell defaultCell;
	
	bool imagesLoaded;

	static const int tilesNumber = 25;
	HBITMAP emptyTile,
		  wallTile,
		  startTile,
		  endTile,
		  traceBackTile,
		  oneTile,
		  twoTile,
		  threeTile,
		  fourTile,
		  fiveTile,
		  sixTile,
		  sevenTile,
		  eightTile,
		  nineTile,
		  tenTile,
		  elevenTile,
		  twelveTile,
		  thirteenTile,
		  fourteenTile,
		  fifteenTile,
		  sixteenTile,
		  seventeenTile,
		  eighteenTile,
		  nineteenTile,
		  twentyTile,
		  twentyOneTile,
		  twentyTwoTile,
		  twentyThreeTile,
		  twentyFourTile,
		  twentyFiveTile,
		  plusTile;
	
	void getBoardImages(LPSTR emptyTilePath,
					   LPSTR wallTilePath,
					   LPSTR startTilePath,
					   LPSTR endTilePath,
					   LPSTR traceBackTilePath,
					   LPSTR oneTilePath,
					   LPSTR twoTilePath,
					   LPSTR threeTilePath,
					   LPSTR fourTilePath,
					   LPSTR fiveTilePath,
					   LPSTR sixTilePath,
					   LPSTR sevenTilePath,
					   LPSTR eightTilePath,
					   LPSTR nineTilePath,
					   LPSTR tenTilePath,
					   LPSTR elevenTilePath,
					   LPSTR twelveTilePath,
					   LPSTR thirteenTilePath,
					   LPSTR fourteenTilePath,
					   LPSTR fifteenTilePath,
					   LPSTR sixteenTilePath,
					   LPSTR seventeenTilePath,
					   LPSTR eighteenTilePath,
					   LPSTR nineTeenTilePath,
					   LPSTR twentyTilePath,
					   LPSTR twentyOneTilePath,
					   LPSTR twentyTwoTilePath,
					   LPSTR twentyThreeTilePath,
					   LPSTR twentyFourTilePath,
					   LPSTR twentyFiveTilePath,
					   LPSTR plusTilePath);

	void handleClicks(WindowsInput input);
	void setupBoard();
	void renderBoard(HDC bitMapHDC,HDC backHDC);
	void updateBoard();
	void changePathFindingValue(int newValue, int xPos, int yPos);
	void setStart(int xPos, int yPos);
	void setEnd(int xPos, int yPos);
	void drawWall(int xPos, int yPos);
	void eraseWall(int xPos, int yPos);
	void setTraceBack(int xPos, int yPos);
	void reset();
	HBITMAP LoadABitmap(LPSTR);
	GameBoard(void);
	~GameBoard(void);


};

