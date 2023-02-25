#include "../include/CursorOp.h"

#include <conio.h>
#include <Windows.h>

void GotoXY(short x, short y){
	HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE); // ��ÿ���̨���
	COORD pos = {x, y}; // ��ù��λ��
	SetConsoleCursorPosition(h_out, pos); // ���ù��λ��
}

void GetCurPos(short& x, short& y){
	HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE); // ��ÿ���̨���
	CONSOLE_SCREEN_BUFFER_INFO csbi; // ��Ļ��Ϣ
	GetConsoleScreenBufferInfo(h_out, &csbi); // ��ȡ��Ļ��Ϣ
	x = csbi.dwCursorPosition.X; // ��ȡx
	y = csbi.dwCursorPosition.Y; // ��ȡy
}
