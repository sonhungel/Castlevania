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
	CMapTexture *texture;
	int TileMap[200][200];
public:
	CMap(int idScene);
	int getTile(int x, int y);
	void LoadMap();
	void DrawMap();
};
#endif 