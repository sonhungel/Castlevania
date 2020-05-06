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
	texture = new CMapTexture(idScene);
	_idScene = idScene; 
	_row = 6;
	switch (idScene)
	{
	case 1:
		_column = 24;
		break;
	case 2:
		_column = 8;
	case 3:
		_column = 16;
	case 4:
		_column = 24;
	case 5:
		_column = 24;
	case 6:
		_column = 88;
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
		inFile.open("map/map1.txt");
		break;
	case 2:
		inFile.open("map/map2.txt");
		break;
	case 3:
		inFile.open("map/map3.txt");
		break;
	case 4:
		inFile.open("map/map45.txt");
		break;
	case 5:
		inFile.open("map/map45.txt");
		break;
	case 6:
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
	case 0:
		_column = 24;
		_row = 6;
		break;
	case 1:
		_column = 88;
		_row = 12;
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
	CGame* game = CGame::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);
	
	for (int i = (int)(cam_y) / 64; i < (int)(cam_y + 560) / 64 + 3; i++)
	{
		for (int j = (int)(cam_x) / 64; j < (int)(cam_x + 560) / 64 + 3; j++)
		{
			if (!(i < 0 || j >= _column))
				sprites->Get(getTile(i, j))->Draw(64 * j, 64 * i ,255);
		}
	}
	

}
