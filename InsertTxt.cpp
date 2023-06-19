#include "InsertTxt.h"

enum Dir {Up = 72, Down = 80, Left = 75, Right = 77, ESC = 27};

void InsertTxt::handleInput() {
	cin.sync(); // 清空输入缓冲区
	char cmd = _getch(); // 读取字符
	if (!isascii(cmd)) // 将字符转换为键盘指令
		cmd = _getch();
	switch (cmd) {
	// case Left: // 光标左移
	// 	moveLeft();
	// 	break;
	// case Down: // 光标下移
	// 	moveDown();
	// 	break;
	// case Up: // 光标上移
	// 	moveUp();
	// 	break;
	// case Right: // 光标右移
	// 	moveRight();
	// 	break;
	case ESC: // 普通模式
		EditorScreen::text = std::make_shared<NormalTxt>(txt, cur, history);
		break;
	default: // 输入字符
		insert(cmd);
		break;
	}
}

void InsertTxt::render() {
	// 清屏
	system("cls");
	// 底部栏目
	GotoXY(0, 28);
	cout << "<Insert>";
	// 显示文本
	if (txt.size() == 0) return;
	GotoXY(0, 0);
	if (txt.size() == 0) return;
	int len = txt.size();
	for (int i = 0; i < len - 1; i++)
		cout << txt[i] << endl;
	cout << txt[len - 1];
	// 显示光标
	GotoXY(cur.X, cur.Y);
}

void InsertTxt::insert(char& cmd) {
	if (!isprint(cmd)) return;
	if (cur.Y < static_cast<int>(txt.size()) &&
	    cur.X <= static_cast<int>(txt[cur.Y].size())) { // 在某一现有的行插入
		history.save(txt, cur); // 保留历史操作
		txt[cur.Y].insert(txt[cur.Y].begin() + cur.X++, cmd); // 插入并更新x

		render();
		GotoXY(9, 28); // 移动光标到"<Normal> "之后
		cout << "Insert!";
		GotoXY(cur.X, cur.Y);
	}
}
