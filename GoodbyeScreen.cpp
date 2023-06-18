#include "GoodbyeScreen.h"

void GoodbyeScreen::handleInput() {}

void GoodbyeScreen::render() {
	system("cls"); // 刷新
	GotoXY(36, 12);
	cout << "Thanks for Using!";
	GotoXY(36, 14);
	system("pause"); // 暂停
	exit(0);
}
