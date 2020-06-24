#include "Code.h"
#include"Sprites.h"
#include"Simon.h"


void CCode::DrawNumber(int _max, float _x, float _y, int _string)
{
	string str = to_string(_string);	// cần chỉnh sửa

	for (int i = 0; i < (_max - str.size()); i++)
	{
		CSprites::GetInstance()->Get(SPRITE_ID_FIRST_NUMBER)->Draw(_x, _y);
		_x += 15;
	}
	for (int i = 0; i < str.size(); i++)
	{
		CSprites::GetInstance()->Get(SPRITE_ID_FIRST_NUMBER + ConvertToInt(str[i]))->Draw(_x, _y);
		_x += 15;
	}
}

void CCode::DrawBloodBar(float _x, float _y, int _type , int string )
{
	CSprites* sprites = CSprites::GetInstance();
	CSprite *sprite1 = sprites->Get(SPRITE_ID_BLANK_BLOOD);
	CSprite* sprite2 = NULL;

	if (_type == 0)	// blood Simon
	{
		sprite2 = sprites->Get(SPRITE_ID_RED_BLOOD);
	}
	else // blood Enemy Boss
	{
		sprite2 = sprites->Get(SPRITE_ID_YELLOW_BLOOD);
	}

	for (int i = 0; i < string; i++)
	{
		sprite2->Draw(_x, _y);
		_x += 11;
	}
	for (int i = 0; i < MAX_BLOOD-string; i++)
	{
		sprite1->Draw(_x, _y);
		_x += 11;
	}
	sprites = NULL;
	sprite1 = NULL;
	sprite2 = NULL;
}

int CCode::ConvertToInt(char C)
{
	return C-'0';
}
