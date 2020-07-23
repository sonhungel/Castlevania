#pragma once
#include<vector>
#include"Game.h"
#include"GameObject.h"
#include"Utils.h"
#include"Define.h"

#define GRID_ROW_MAX		1
#define GRID_COLUMN_MAX		6

#define GRID_CELL_WIDTH		265//SCREEN_WIDTH
#define GRID_CELL_HEIGHT	496//SCREEN_HEIGHT

using namespace std;

class CGrid
{
	vector<LPGAMEOBJECT> cells[GRID_ROW_MAX][GRID_COLUMN_MAX];
public:
	CGrid();
	void LoadGrid(vector<LPGAMEOBJECT> ListObj);
	void GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y);
	void Insert(LPGAMEOBJECT obj, float x, float y, float w, float h);	// thêm obj vào grid
	void PushObjectToCell(LPGAMEOBJECT obj, int grid_row, int grid_column);
	void ResetOnCamera(vector<LPGAMEOBJECT> &ListObj);

};

