#include "GoodbyeScreen.h"

void GoodbyeScreen::handleInput() {}

void GoodbyeScreen::render() {
	system("cls"); // 刷新
	Cursor::setPos(36, 12);
	cout << "Thanks for Using!";
	Cursor::setPos(36, 14);
	system("pause"); // 暂停
	exit(0);
}
