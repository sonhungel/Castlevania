#include "Grid.h"

CGrid::CGrid(vector<LPGAMEOBJECT> ListObj)
{
	LoadGrid(ListObj);
}

void CGrid::LoadGrid(vector<LPGAMEOBJECT> ListObj)
{
	float l, t, r, b;
	for (UINT i = 0; i < ListObj.size(); i++)
	{
		ListObj.at(i)->GetBoundingBox(l, t, r, b);
		Insert(ListObj.at(i), l, t, r-l, b-t);
	}
}

void CGrid::GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y)
{
	ListObj.clear();

	int top = (int)(cam_y ) / GRID_CELL_HEIGHT;
	int bottom = (int)(cam_y + SCREEN_HEIGHT ) / GRID_CELL_HEIGHT;


	int left = (int)(cam_x ) / GRID_CELL_WIDTH;
	int right = (int)(cam_x + SCREEN_HEIGHT ) / GRID_CELL_WIDTH;

	for (int row = top; row <= bottom+1; row++)
	{
		for (int column = left; column <= right+1; column++)
		{
			if (row <= GRID_ROW_MAX && row >= 0 && column <= GRID_COLUMN_MAX && column >= 0)
			{
				for (UINT i = 0; i < cells[row][column].size(); i++)
				{
				
					if (cells[row][column].at(i)->blood > 0)	// Loại trừ các obj đã destroy
					{
						if (cells[row][column].at(i)->isOnCamera == false)	// bỏ qua nếu obj đã xuất hiện trên cam
							// tránh trường hợp 1 cell grid có 2 obj xuất hiện
							// xóa đk để hiểu rõ
						{
							ListObj.push_back(cells[row][column].at(i));
							cells[row][column].at(i)->isOnCamera = true;
						}
					}
				}
			}
		}
	}
}

void CGrid::Insert(LPGAMEOBJECT obj, float x, float y, float w, float h)
{
	int top = (int)(y) / GRID_CELL_HEIGHT;
	int bottom = (int)(y + h) / GRID_CELL_HEIGHT;

	int left = (int)(x) / GRID_CELL_WIDTH;
	int right = (int)(x + w) / GRID_CELL_WIDTH;

	obj->isOnCamera = false;

	for (int row = top; row <= bottom; row++)
		for (int column = left; column <= right; column++)
			cells[row][column].push_back(obj);
}

void CGrid::ResetOnCamera(vector<LPGAMEOBJECT>& ListObj)
{
	for (int i = 0; i < ListObj.size(); i++)
		ListObj[i]->isOnCamera = false;
}
