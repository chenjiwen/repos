#ifndef __MISC_H__
#define __MISC_H__
#pragma once

#include "common.h"

typedef enum
{
	DIR_LEFT,
	DIR_UP,
	DIR_RIGHT,
	DIR_BOT
}DirT;

typedef enum
{
	WHITE,
	GRAY,
	BLACK
}PuzNodeColor;

typedef struct
{
	int x_p;
	int y_p;
}PosT;


const int puzzle_array_size = 8;
typedef struct
{
	PosT path;
	int  val;
	PuzNodeColor color;
}PuzzleTable;




#endif // !__MISC_H__


