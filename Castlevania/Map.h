#ifndef __MAP_H__

#define __MAP_H__

#include "Sprites.h"
#include "Textures.h"
#include "Sprites.h"
#include"Utils.h"


using namespace std;

class CMap
{
	
private:
	int _column;
	int _row;
	int index;
	int align;
	int TileMap[51][51];
	static CMap* __instance;
public:
	static CMap* GetInstance();

	CMap();
	void SetValueInMap(int row, int column,int index,int align);
	int getTile(int x, int y);
	void LoadMap(wstring filePathTxt);
	void DrawMap();
	int GetColumn() { return _column; }
};
#endif 