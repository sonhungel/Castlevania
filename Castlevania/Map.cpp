#include "Map.h"
#include "fstream"
#include"Game.h"
#include"Utils.h"

CMap* CMap::__instance = NULL;

CMap* CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}

CMap::CMap()
{
	
}
void CMap::SetValueInMap(int row, int column,int index,int align)
{
	this->_column = column;
	this->_row = row;
	this->index = index;
	this->align = align;
}
void CMap::LoadMap(wstring filePathTxt)
{
	ifstream inFile;
	inFile.open(filePathTxt);
	if (inFile.fail())
	{
		DebugOut(L"[ERROR] Map::Load Map failed\n");
		inFile.close();
		return;
	}
	// If the file opened correctly then call load methods

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			inFile >> TileMap[i][j];
		}
	}
	inFile.clear();
}

int CMap::getTile(int x, int y)
{
	return TileMap[x][y];
}


void CMap::DrawMap()
{
	CSprites* sprites = CSprites::GetInstance();

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			sprites->Get(getTile(i, j)+index)->Draw(32 * j, 32 * i + align, 255);
			
		}
	}
	sprites = NULL;
}
