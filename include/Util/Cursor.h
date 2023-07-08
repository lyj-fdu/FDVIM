#ifndef CURSOR_H
#define CURSOR_H

#include <conio.h>
#include <Windows.h>

class Cursor {
private:
    Cursor() {}

public:
    static void setPos(short x, short y); // 移动光标
    static void getPos(short& x, short& y); // 获取光标所处坐标
};

#endif