#include "Platform.h"
#include"Utils.h"

void CPlatform::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if ((x <= x_left && vx < 0) || (x >= x_right && vx > 0))
	{
		nx = -nx;
		vx = nx * PLATFORM_SPEED_X;
	}
	CGameObject::Update(dt);
	x += dx;

	
	//DebugOut(L"Vi tri platform : %d\n", (int) this->x);
	//DebugOut(L"dt platform : %d\n", dt);
}

void CPlatform::Render()
{
	animations[0]->Render(x, y);
}

void CPlatform::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PLATFORM_WIDTH;
	bottom = y + PLATFORM_HEIGHT;
}
