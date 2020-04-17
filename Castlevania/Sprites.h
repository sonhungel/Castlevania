#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database
						// các vị trí để xác định sprite cần thiết 
	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	CSprite();

	void Draw(float x, float y);
	void DrawStatic(float x, float y); // các function được thiết kế thêm

	void DrawFlipX(float x, float y); 
	void DrawCam(float x, float y);
	int getHeight() { return bottom - top; }
	int getwidth() { return right - left; }
	void load(std::ifstream& inFile);
	int getID() { return id; }
};

typedef CSprite* LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites* __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Add(LPSPRITE lpsprite);
	LPSPRITE Get(int id);
	void CSprites::Clear();

	static CSprites* GetInstance();
};







