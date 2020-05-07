#include "Map.h"
#include "fstream"
#include"Game.h"

CMap* CMap::__instance = NULL;

CMap* CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}

CMap::CMap(int idScene)
{
	//texture = new CMapTexture(idScene);
	_idScene = idScene; 
	
	switch (idScene)
	{
	case 1:
		_column = 48;
		_row = 9;
		break;
	case 2:
		_column = 17;
		_row = 11;
		break;
	case 3:
		_column = 34;
		_row = 12;
		break;
	case 4:
		_column = 50;
		_row = 12;
		break;
	case 5:
		_column = 48;
		_row = 12;
		break;
	case 6:
		_column = 48;
		_row = 11;
		break;
	default:
		break;
	}
	LoadMap();
}
void CMap::LoadMap()
{
	ifstream inFile;
	switch (_idScene)
	{
	case 1:
		inFile.open("map/Map1.txt");
		break;
	case 2:
		inFile.open("map/Map2.txt");
		break;
	case 3:
		inFile.open("map/Map3.txt");
		break;
	case 4:
		inFile.open("map/Map4.txt");
		break;
	case 5:
		inFile.open("map/map5.txt");
		break;
	case 6:
		inFile.open("map/Map6.txt");
		break;
	default:
		break;
	}

	// If the file opened correctly then call load methods

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			inFile >> TileMap[i][j];
		}
	}
}
void CMap::SetMap(int idScene)
{
	_idScene = idScene;
	switch (idScene)
	{
	case 1:
		_column = 48;
		_row = 9;
		break;
	case 2:
		_column = 17;
		_row = 11;
		break;
	case 3:
		_column = 34;
		_row = 12;
		break;
	case 4:
		_column = 50;
		_row = 12;
		break;
	case 5:
		_column = 48;
		_row = 12;
		break;
	case 6:
		_column = 48;
		_row = 11;
		break;
	default:
		break;
	}
	LoadMap();
}
int CMap::getTile(int x, int y)
{
	return TileMap[x][y];
}


void CMap::DrawMap()
{
	int tag = CGame::GetInstance()->GetIDCurrentScene();
	int index;// hệ số phân định id sprite
	int align;// hệ số căn chỉnh
	switch (tag)
	{
	case 1:
		index = 0;
		align = 75;
		break;
	case 2:
		index = 1000;
		align = 10;
		break;
	case 3:
		index = 2000;
		align = 75;
		break;
	case 4:
		index = 3000;
		align = 75;
		break;
	case 5:
		index = 4000;
		align = 75;
		break;
	case 6:
		index = 5000;
		align = 75;
		break;
	default:
		break;
	}
	CSprites* sprites = CSprites::GetInstance();

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			sprites->Get(getTile(i, j)+index)->Draw(32 * j, 32 * i + align, 255);
		}
	}
	
}
