﻿#pragma once

#define SCREEN_WIDTH 525
#define SCREEN_HEIGHT 496	// 496

enum eType
{
	UNKNOW=0,

	// SIMON
	SIMON=1,

	// STATIC OBJ
	// BRICK
	BRICK=10,

	// TORCH

	TORCH=11,

	// CANDLE
	CANDLE=12,
	// BREAK BRICK
	BREAK_BRICK=13,

	// WEAPON

	WEAPON_KNIFE=40,
	WEAPON_AXE=41,
	WEAPON_BOOMERANG=42,
	WEAPON_HOLLYWATER=43,
	WEAPON_WHIP=44,

	//TYPE ITEM	 
	ITEM_KNIFE = 51,			// 701
	ITEM_WHIPUPGRADE = 52,		// 700
	ITEM_HEARTBIG = 53,			// 702
	ITEM_AXE = 54,				// 703
	ITEM_SMALLHEART = 55,		// 704	// đặc biệt vì có di chuyển zic zac
	ITEM_RED_MONEY = 56,		// 705	// có effect
	ITEM_YELLOW_MONEY = 57,		// 706	// có effect
	ITEM_PURPLE_MONEY = 58,		// 707	// có effect
	ITEM_CLOCK = 59,			// 709
	ITEM_CROSS = 60,			// 710
	ITEM_II = 63,				// 711
	ITEM_III = 64,				// 712
	ITEM_HOLLYWATTER = 62,		// 713
	ITEM_BOSSBALL = 61,			// 714
	ITEM_BOONGMERANG = 65,		// 715
	ITEM_VASE = 66,				// 716
	ITEM_HIDEN_MONEY = 67,		// 717
};