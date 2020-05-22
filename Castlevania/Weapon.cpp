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

}

