#include "Grid.h"

CGrid::CGrid()
{
	//LoadGrid(ListObj);
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
	int right = (int)(cam_x + SCREEN_WIDTH) / GRID_CELL_WIDTH;

	for (int row = top; row < bottom; row++)
	{
		for (int column = left; column <= right; column++)
		{
			if (row <= GRID_ROW_MAX && row >= 0 && column <= GRID_COLUMN_MAX && column >= 0)//
			{
				for (UINT i = 0; i < cells[row][column].size(); i++)
				{
					if (cells[row][column].at(i)->blood > 0)	// Loại trừ các obj đã destroy
					{
						//if (cells[row][column].at(i)->isOnCamera == false)	// bỏ qua nếu obj đã xuất hiện trên cam
							// tránh trường hợp 1 cell grid có 2 obj xuất hiện
							// xóa đk để hiểu rõ
						{
							ListObj.push_back(cells[row][column].at(i));
							//cells[row][column].at(i)->isOnCamera = true;
						}
					}
					else
					{
						delete cells[row][column].at(i);
						cells[row][column].erase(cells[row][column].begin() + i);	// xóa những obj đã die ra khỏi Cell
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

	//obj->isOnCamera = false;

	for (int row = top; row <= bottom; row++)
		for (int column = left; column <= right; column++)
			cells[row][column].push_back(obj);
}

void CGrid::PushObjectToCell(LPGAMEOBJECT obj, int grid_row, int grid_column)
{
	if (obj == NULL)
		return;
	//obj->isOnCamera = false;
	cells[grid_row][grid_column].push_back(obj);
}

void CGrid::ResetOnCamera(vector<LPGAMEOBJECT>& ListObj)// ngừng sử dụng
{
	for (int i = 0; i < ListObj.size(); i++)
	{
		if (ListObj.at(i)->blood <= 0)
		{
			delete ListObj.at(i);
			ListObj.erase(ListObj.begin()+i);	// xóa những obj đã die ra khỏi vector object trong playscene
		}
		//else
		//	ListObj[i]->isOnCamera = false;
	}
}
