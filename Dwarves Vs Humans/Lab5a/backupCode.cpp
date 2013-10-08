/*
void HexMap::generateNewMap()
{
	srand(time(NULL));

	clearQueue(workingSet);
	cleanMap(HexTile::Grass); //sets the map to all one tile, changine this can maybe generate water based maps or something
	generateTerrainExpanse(HexTile::Forest,8,4,35,10); //Generate Forests
	generateTerrainExpanse(HexTile::Water,8,2,40,10); //Generate Lakes
	generateTerrainExpanse(HexTile::Forest,8,4,35,10); //Generate Forests
	generateTerrainExpanse(HexTile::Water,8,2,40,10); //Generate Lakes


	
	workingSet.push(hexMapArray[0][0]);
	workingSet.push(hexMapArray[mapWidth/2][0]);
	workingSet.push(hexMapArray[mapWidth - 1][0]);
	workingSet.push(hexMapArray[0][mapHeight/2]);
	workingSet.push(hexMapArray[mapWidth/2][mapHeight/2]);
	workingSet.push(hexMapArray[mapWidth - 1][mapHeight/2]);
	workingSet.push(hexMapArray[0][mapHeight - 1]);
	workingSet.push(hexMapArray[mapWidth/2][mapHeight - 1]);
	workingSet.push(hexMapArray[mapWidth - 1][mapHeight - 1]);
	*/
	
	//generationActive = true;

	/*
	while(generationActive == true)
	{
		if(workingSet.empty() == true)
		{
			break;
		}
		
		//This is basically a lee flood fill
		HexTile currentHex;
		currentHex = workingSet.front();

		//check left
		if(currentHex.hexGridX < (mapWidth - 1))
		{

			if(hexMapArray[currentHex.hexGridX + 1][currentHex.hexGridY].shouldCheckGen == true)
			{
				//Run the generation function, for now doing this to check
				hexMapArray[currentHex.hexGridX + 1][currentHex.hexGridY].setTerrain(generateTile()); //this line sets the output of generateTile() to be the tileType of the candidateTile

				//Add the candidate cell to working set
				workingSet.push(hexMapArray[currentHex.hexGridX + 1][currentHex.hexGridY]);

				//flick the toggle
				hexMapArray[currentHex.hexGridX + 1][currentHex.hexGridY].shouldCheckGen = false;
			}
		}

		//check down
		if(currentHex.hexGridY < (mapHeight - 1))
		{

			if(hexMapArray[currentHex.hexGridX][currentHex.hexGridY + 1].shouldCheckGen == true)
			{
				//Run the generation function, for now doing this to check
   				hexMapArray[currentHex.hexGridX][currentHex.hexGridY + 1].setTerrain(generateTile());

				//Add the candidate cell to working set
				workingSet.push(hexMapArray[currentHex.hexGridX][currentHex.hexGridY + 1]);

				//flick the toggle
				hexMapArray[currentHex.hexGridX][currentHex.hexGridY + 1].shouldCheckGen = false;
			}
		}

		//check right
		if(currentHex.hexGridX > 0)
		{
			if(hexMapArray[currentHex.hexGridX - 1][currentHex.hexGridY].shouldCheckGen == true)
			{
				//Run the generation function, for now doing this to check
   				hexMapArray[currentHex.hexGridX - 1][currentHex.hexGridY].setTerrain(generateTile());

				//Add the candidate cell to working set
				workingSet.push(hexMapArray[currentHex.hexGridX - 1][currentHex.hexGridY]);

				//flick the toggle
				hexMapArray[currentHex.hexGridX - 1][currentHex.hexGridY].shouldCheckGen = false;
			}
		}
		//check up
		if(currentHex.hexGridY > 0)
		{

			if(hexMapArray[currentHex.hexGridX][currentHex.hexGridY - 1].shouldCheckGen == true)
			{
				//Run the generation function, for now doing this to check
   				hexMapArray[currentHex.hexGridX][currentHex.hexGridY - 1].setTerrain(generateTile());

				//Add the candidate cell to working set
				workingSet.push(hexMapArray[currentHex.hexGridX][currentHex.hexGridY - 1]);

				//flick the toggle
				hexMapArray[currentHex.hexGridX][currentHex.hexGridY - 1].shouldCheckGen = false;
			}
		}
		
		//pop the currentCell off the workingSet
		if(workingSet.size() > 0)
		{
			workingSet.pop();
		}
	}
	
}
*/
/*
HexTile::terrainType HexMap::generateTile()
{
	
	//Second order weights, used in determining whether the next hex should be copied from the previous to generate big landscapes
	//these arnt independant, as it only checks as depending as what the previous tile was
	//ie if the previous tile was water, and a 50 is rolled the next tile will be water, but if a 80 was rolled it would generate a whole new tile using the above weights
	int secondOrderGrassWeight = 70;   //0 - 90
	int secondOrderWaterWeight = 95;   //0 - 70
	int secondOrderForestWeight = 95;  //0 - 80
	int firstOrderlongGrassWeight = 40;    //0 - 65

	int randomNum;
	randomNum = rand() % 100 + 1;

	if(workingSet.front().hexTerrain == HexTile::Grass)
	{
		if(randomNum < secondOrderGrassWeight)
		{
			return HexTile::Grass;
		}
		else
		{
			return generateNewTile();
		}
	}
	else if(workingSet.front().hexTerrain == HexTile::Water)
	{
		if(randomNum < secondOrderWaterWeight)
		{
			return HexTile::Water;
		}
		else
		{
			return generateNewTile();
		}
	}
	else if(workingSet.front().hexTerrain == HexTile::Forest)
	{
		if(randomNum < secondOrderForestWeight)
		{
			return HexTile::Forest;
		}
		else
		{
			return generateNewTile();
		}
	}
	else if(workingSet.front().hexTerrain == HexTile::longGrass)
	{
		if(randomNum < firstOrderlongGrassWeight)
		{
			return HexTile::longGrass;
		}
		else
		{
			return generateNewTile();
		}
	}
	
}

HexTile::terrainType HexMap::generateNewTile()
{
	
	//First order weights, used in generating a brand new tile when you're not copying from the previous hex
	//these all need to fit into 1-100, as they all work with one roll
	//when generating a new tile, whatever one it is under first gets made, ie, if it is 65 it would be a forest
	int firstOrderGrassWeight = 60;  // 0 - 40
	int firstOrderWaterWeight = 65;  // 41 - 60
	int firstOrderForestWeight = 85; // 61 - 85
	int firstOrderlongGrassWeight = 100;  // 86 - 100

	int randomNum;
	randomNum = rand() % 100 + 1;

	if(randomNum < firstOrderGrassWeight)
	{
		return HexTile::Grass;
	}
	else if(randomNum < firstOrderWaterWeight)
	{
		return HexTile::Water;
	}
	else if(randomNum < firstOrderForestWeight)
	{
		return HexTile::Forest;
	}
	else if(randomNum < firstOrderlongGrassWeight)
	{
		return HexTile::longGrass;
	}
	
	return HexTile::Grass;
}
*/