#include "Map.h"
#include "fstream"

CMap::CMap(int idScene)
{
	texture = new CMapTexture(idScene);
}
void CMap::LoadMap()
{

	ifstream inFile("map/map.txt");

	// If the file opened correctly then call load methods

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 24; j++)
		{
			inFile >> TileMap[i][j];
		}
}
int CMap::getTile(int x, int y)
{
	return TileMap[x][y];
}


void CMap::DrawMap()
{
	for (int i = 0; i < 5; i++)
	{
		{
			for (int j = 0; j < 24; j++) 
			{
				
				CSprites::GetInstance()->Get(getTile(i, j))->Draw(64 * j, 64 * i +40);
			}
		}
	}
}
