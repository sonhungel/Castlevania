#include "Sprites.h"
#include "Game.h"
#include"Utils.h"
#include "fstream"
#include "Textures.h"

using namespace std;
CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;

	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;

	this->texture = tex;
}
CSprite::CSprite()
{
	this->id = 0;

	this->left = 0;
	this->top = 0;
	this->right = 0;
	this->bottom = 0;

	this->texture = NULL;
}
CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y)
{
	CGame* game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom);
}
void CSprite::DrawCam(float x, float y)
{
	CGame* game = CGame::GetInstance();
	game->DrawFlipX(x, y, texture, left, top, right, bottom);
}

void CSprite::DrawFlipX(float x, float y) {
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;

	D3DXVECTOR2 top_left = D3DXVECTOR2(x, y);

	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= getwidth();

	this->DrawCam(x , y);

	spriteHandler->SetTransform(&oldMt);
}
void CSprite::load(std::ifstream& inFile)
{
	string temp;
	int idTexture;

	inFile >> temp >> id;
	inFile >> temp >> left;
	inFile >> temp >> top;
	inFile >> temp >> right;
	inFile >> temp >> bottom;
	inFile >> temp >> idTexture;
	CTextures* textures = CTextures::GetInstance();
	texture = textures->Get(idTexture);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d \n", id, left, top, right, bottom);
}

void CSprites::Add(LPSPRITE lpsprite)
{
	sprites[lpsprite->getID()] = lpsprite;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}

