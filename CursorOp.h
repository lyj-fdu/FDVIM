#ifndef CURSOR_OP_H
#define CURSOR_OP_H

#include <conio.h>
#include <Windows.h>

void GotoXY(short x, short y); // 移动光标
void GetCurPos(short& x, short& y); // 获取光标所处坐标

#endif