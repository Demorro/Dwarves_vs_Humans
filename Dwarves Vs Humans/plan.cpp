Class GameController()
{

	Vector<Unit> player1Units;
	Vector<Unit> player2Units;

	RunGame();


}

void RunGame()
{
	CheckForVictory()
	for(int i = 0; i < player1Units.size(); i++)
	{
		player1Units[i].resetPeiceForTurn();
	}
	Player1Goes():



	CheckForVictory()
	for(int i = 0; i < player2Units.size(); i++)
	{
		player2Units[i].resetPeiceForTurn();
	}
	Player2Goes()
}

void Units::resetPeiceForTurn()
{
	hasMoved = false;
	hasAttacked = false;
}

void Player1Goes()
{
	for(int i = 0; i < player1Units.size(); i++)
	{
		if(player1Units[i].hasTakenTurn == false)
		{
			player1Units[i].takeTurn();
		}
	}
}


void Units::TakeTurn()
{

	if(hasMoved == false) && (hasAttacked == false)
	{
		GameBoard.displayMoveGird(vector2 position, int moveDistance);
		handleMoveMent(&this)
		hasMoved = true;
	}
	else if(hasMoved == true) && (hasAttacked == false)
	{
		GameBoard.displayAttackGrid(vector2 position, int attackDistance);
		handleAttacks();
	}

}

void Units::HandleMoveMent(*Unit, std::queue<HexTiles> movementTiles)
{
	bla de bla de bla movement Code
	if(mouseclick is a valid move)
	{
		gameBoard[[mouseclick.x][mouseclick.y].occupyingunit = &unit;
		unit = NULL; //I REALLY HOPE THIS WORKS, sets the occupying peice of the tile that it is on to NULL
	}
}

void Units::HandleAttacks()
{

}