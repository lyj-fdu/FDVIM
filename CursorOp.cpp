#include"CursorOp.h"

void GotoXY(short x, short y){
	HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE); // 获得控制台句柄
	COORD pos = {x, y}; // 获得光标位置
	SetConsoleCursorPosition(h_out, pos); // 设置光标位置
}

void GetCurPos(short& x, short& y){
	HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE); // 获得控制台句柄
	CONSOLE_SCREEN_BUFFER_INFO csbi; // 屏幕信息
	GetConsoleScreenBufferInfo(h_out, &csbi); // 获取屏幕信息
	x = csbi.dwCursorPosition.X; // 读取x
	y = csbi.dwCursorPosition.Y; // 读取y
}