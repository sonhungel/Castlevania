#ifndef __MAP_H__

#define __MAP_H__

#include "Sprites.h"
#include "Textures.h"
#include "Sprites.h"
#include"MapTexture.h"

using namespace std;

class CMap
{
	
private:
	int _idScene;
	int _column;
	int _row;
	CMapTexture *texture;
	int TileMap[200][200];
	static CMap* __instance;
public:
	static CMap* GetInstance();

	CMap(int idScene=1);
	int getTile(int x, int y);
	void LoadMap();
	void DrawMap();
	void SetMap(int id);
};
#endif 