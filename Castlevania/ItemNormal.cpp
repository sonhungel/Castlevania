#include "ItemNormal.h"

void CItemNormal::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}
}

void CItemNormal::LoadItem(int _type)
{
	switch (this->type)
	{
	case eType::ITEM_KNIFE:
	{
		AddAnimation(ITEM_KNIFE_ANI_ID);
		width = 35;
		height = 21;
	}
	break;
	case eType::ITEM_WHIPUPGRADE:
	{
		AddAnimation(ITEM_WHIPUPGRADE_ANI_ID);
		width = 36;
		height = 36;
	}
	break;
	case eType::ITEM_HEARTBIG:
	{
		AddAnimation(ITEM_HEARTBIG_ANI_ID);
		width = 26;
		height = 23;
	}
	break;
	case eType::ITEM_AXE:
	{
		AddAnimation(ITEM_AXE_ANI_ID);
		width = 32;
		height = 32;
	}
	break;
	case eType::ITEM_CLOCK:
	{
		AddAnimation(ITEM_CLOCK_ANI_ID);
		width = 33;
		height = 35;
	}
	break;
	case eType::ITEM_CROSS:
	{
		AddAnimation(ITEM_CROSS_ANI_ID);
		width = 34;
		height = 34;
	}
	break;
	case eType::ITEM_II:
	{
		AddAnimation(ITEM_II_ANI_ID);
		width = 30;
		height = 30;
	}
	break;
	case eType::ITEM_III:
	{
		AddAnimation(ITEM_III_ANI_ID);
		width = 30;
		height = 30;
	}
	break;
	case eType::ITEM_HOLLYWATTER:
	{
		AddAnimation(ITEM_HOLLYWATTER_ANI_ID);
		width = 30;
		height = 35;
	}
	break;
	case eType::ITEM_BOSSBALL:
	{
		AddAnimation(ITEM_BOSSBALL_ANI_ID);
		width = 32;
		height = 34;
	}
	break;
	case eType::ITEM_BOOMERANG:
	{
		AddAnimation(ITEM_BOOMERANG_ANI_ID);
		width = 33;
		height = 33;
	}
	break;
	case eType::ITEM_VASE:
	{
		AddAnimation(ITEM_VASE_ANI_ID);
		width = 27;
		height = 34;
	}
	break;
	default:
		break;
	}
}
