#include "Portal.h"


CPortal::CPortal(int scene_id ):CGameObject()
{
	this->scene_id = scene_id;

	this->blood = 1;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + PORTAL_WIDTH;
	bottom = y + PORTAL_HEIGHT;
}