#pragma once
#include<string>
using namespace std;

#define SPRITE_ID_FIRST_NUMBER	60000

#define SPRITE_ID_RED_BLOOD		60011
#define SPRITE_ID_YELLOW_BLOOD	60012
#define SPRITE_ID_BLANK_BLOOD	60013

class CCode
{
private:
public:
	void DrawNumber(int _max,float _x, float _y,int string=0);
	void DrawBloodBar(float _x, float _y, int _type = 0, int string = 0);
	int ConvertToInt(char C);
};

