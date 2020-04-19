#include "Weapon.h"
#include"Game.h"
#include"Torch.h"

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> listObject;
	//collision logic with items
	for (UINT i=0;i<coObjects->size();i++)
	{
		LPGAMEOBJECT object = coObjects->at(i);
		listObject.push_back(object);
	}

	CollisionWithObject(dt, listObject);
}

void CWeapon::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	for (int i = 0; i < listObj.size(); i++)
	{
		if (dynamic_cast<CTorch*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == TORCH_STATE_EXSIST)
			{
				LPCOLLISIONEVENT temp = SweptAABBEx(listObj.at(i));
				if (temp->t > 0) // => có đụng độ
				{
					listObj.at(i)->SetState(TORCH_STATE_NOT_EXSIST);
					
				}
			}
		}
	}
}
