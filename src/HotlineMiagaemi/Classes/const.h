
#ifndef _CONST_H_
#define _CONST_H_
#include <string>

extern const int WND_WIDTH_CUTSCENE;
extern const int WND_HEIGHT_CUTSCENE;
extern const int WND_WIDTH_GAME;
extern const int WND_HEIGHT_GAME;
extern const std::string& TEXT_FONT;

enum Direction
{
	DIR_NONE = 0x00,
	DIR_UP = 0x01,
	DIR_UPRIGHT = 0x02,
	DIR_RIGHT = 0x04,
	DIR_RIGHTDOWN = 0x08,
	DIR_DOWN = 0x10,
	DIR_DOWNLEFT = 0x20,
	DIR_LEFT = 0x40,
	DIR_LEFTUP = 0x80,
};

#endif //_CONST_H_