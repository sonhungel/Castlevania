#pragma once
#include<vector>
#include"Game.h"
#include"GameObject.h"
#include"Utils.h"
#include"Define.h"

#define GRID_ROW_MAX		2
#define GRID_COLUMN_MAX		7

#define GRID_CELL_WIDTH		265//SCREEN_WIDTH
#define GRID_CELL_HEIGHT	256//SCREEN_HEIGHT

using namespace std;

class CGrid
{
	vector<LPGAMEOBJECT> cells[GRID_ROW_MAX][GRID_COLUMN_MAX];
public:
	CGrid(vector<LPGAMEOBJECT> ListObj);
	void LoadGrid(vector<LPGAMEOBJECT> ListObj);
	void GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y);
	void Insert(LPGAMEOBJECT obj, float x, float y, float w, float h);	// thêm obj vào grid
	void ResetOnCamera(vector<LPGAMEOBJECT> &ListObj);

};

