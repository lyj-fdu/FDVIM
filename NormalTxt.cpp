#include "NormalTxt.h"

void NormalTxt::handleInput() {
	cin.sync(); // 清空输入缓冲区
	char cmd = _getch(); // 读取字符
	if (!isascii(cmd)) // 将字符转换为键盘指令
		cmd = _getch();
	switch (cmd) {
	case ':': // 执行命令
		exeCmd();
		break;
	case 'x': // 删除光标处的字符
		delChar();
		break;
	case 'u': // 撤销操作
		undo();
		break;
	case 'r': // 重做操作
		redo();
		break;
	case 'h': // 光标左移
		moveLeft();
		break;
	case 'j': // 光标下移
		moveDown();
		break;
	case 'k': // 光标上移
		moveUp();
		break;
	case 'l': // 光标右移
		moveRight();
		break;
	case 'i': // 插入模式
		EditorScreen::text = std::make_shared<InsertTxt>(txt, cur, history);
		break;
	case '/': // 寻字模式
		searchStr();
		break;
	}
}

void NormalTxt::render() {
	// 清屏
	system("cls");
	// 底部栏目
	GotoXY(0, 27);
	cout << "______________________________________________Command______________________________________________";
	GotoXY(0, 28);
	cout << "<Normal> ";
	// 显示文本
	GotoXY(0, 0);
	if (txt.size() == 0) return;
	int len = txt.size();
	for (int i = 0; i < len - 1; i++)
		cout << txt[i] << endl;
	cout << txt[len - 1];
	// 显示光标
	GotoXY(cur.X, cur.Y);
}

void NormalTxt::readTxt(string& filename) {
	file.close(); // 关闭上一个文件
	file.open(filename.data(), ios::in); // 打开新文件，读模式
	render();
	GotoXY(9, 28); // 移动光标到"<Normal> "之后

	// 未找到文件
	if (!file.is_open()) {
		cout << "File Not Found!";
		GotoXY(cur.X, cur.Y);
		return;
	}

	// 成功打开
	cout << "Opening...";
	txt.resize(0);
	txt.shrink_to_fit(); // 初始化txt
	file.seekg(0, ios::beg); // 将文件指针指向开头
	while (!file.eof()) { // 读到文件末尾
		string line;
		getline(file, line);
		txt.push_back(line);
	}
	file.seekg(0, ios::beg); // 将文件指针指向开头

	// 获取光标位置
	cur.Y = static_cast<int>(txt.size()) - 1;
	cur.X = static_cast<int>(txt[cur.Y].size()) - 1;
	history.save(txt, cur); // 保留历史操作
}

void NormalTxt::writeTxt(string& filename) {
	render();
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << "Saving...";
	file.close(); // 关闭上一个文件
	file.open(filename.data(), ios::out); // 打开新文件，写模式
	if (txt.size() == 0) return;
	int len = txt.size();
	for (int i = 0; i < len - 1; i++)
		file << txt[i] << endl;
	file << txt[len - 1];
}

void NormalTxt::KMPPreProcess(const string& p, vector<int>& next) {
	int len = p.size(); // p长度
	next.resize(len);
	next.shrink_to_fit(); // next容量
	int i(0), j = next[0] = -1; // 初始化
	while (i < len - 1) {
		while (j > -1 && p[i] != p[j])
			j = next[j];
		i++;
		j++;
		if (p[i] == p[j]) next[i] = next[j];
		else next[i] = j;
	}
}

void NormalTxt::KMPSearch(string& pattern, COORD& cur) {
	vector<int> next;
	KMPPreProcess(pattern, next); // 预处理
	int plen = pattern.size(), ylen = static_cast<int>(txt.size()), xlen(0);
	for (int p = cur.Y; p < ylen; p++) { // 从这行找到末尾
		int q = (p == cur.Y) ? cur.X : 0, k(0); // 起始行q赋值x，否则赋值0
		xlen = static_cast<int>(txt[p].size()); // 本行的长度
		while (q < xlen) { // q遍历本行查找
			while (k > -1 && pattern[k] != txt[p][q])
				k = next[k];
			q++;
			k++;
			if (k == plen) { // 找到
				history.save(txt, cur); // 保留历史操作
				cur.X = q - k; // 定位x
				cur.Y = p; // 定位y
				GotoXY(9, 28); // 移动光标到"<Normal> "之后
				cout << "Found! Locate cursor to first \"" << pattern << "\"!"; // 输出找到信息
				GotoXY(cur.X, cur.Y); // 定位光标
				Sleep(1000); // 休眠1秒
				return;
			}
		}
	}
	// 没找到
	render();
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << "Not Found! Do you want to find \"" << pattern << "\" from begnning?(y/n)"; // 输出没找到信息
	char choice;
	cin >> choice;
	if (choice == 'y') {
		render();
		history.save(txt, cur); // 保留历史操作
		cur.X = 0;
		cur.Y = 0; // 定位至开头
		KMPSearch(pattern, cur);
	}
}

void NormalTxt::exeCmd() {
	string op, filename;
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << ":";
	cin >> op;
	if (op == "q")
		Editor::screen = std::make_shared<GoodbyeScreen>();
	if (op == "open") { // 读
		cin >> filename;
		filename = "assets/" + filename;
		readTxt(filename);
	} else if (op == "w") { // 写
		cin >> filename;
		filename = "assets/" + filename;
		writeTxt(filename);
	}
}

void NormalTxt::delChar() {
	if (cur.X == 0 && cur.Y == 0 && static_cast<int>(txt.size()) == 0) return; // 第一行开头且无字

	render();
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << "delete!";
	GotoXY(cur.X, cur.Y);

	history.save(txt, cur); // 保留历史操作

	if (cur.X == 0 && cur.Y == 0) { // 第一行开头且文本有字
		if (static_cast<int>(txt[0].size()) == 0) // 空行
			txt.erase(txt.begin()); // 删除空行
		else // 有字
			txt[0].erase(txt[0].begin()); // 删除第一个字
		return;
	}

	if (cur.X == 0) { // 仅有1字
		txt[cur.Y].erase(txt[cur.Y].begin() + cur.X); // 删除
		if (static_cast<int>(txt[cur.Y].size()) == 0) // 空行
			txt.erase(txt.begin() + cur.Y); // 删除空行
		cur.Y--; // 移到上一行
		cur.X = static_cast<int>(txt[cur.Y].size()) > 0 ?
		        static_cast<int>(txt[cur.Y].size()) - 1 : 0; // 移到末尾
	} else if (cur.X < static_cast<int>(txt[cur.Y].size())) // 有效删除区域内，不在该行末尾之外
		txt[cur.Y].erase(txt[cur.Y].begin() + cur.X--); // 删除并左移
	else // 在该行末尾之外
		cur.X--; // 直接左移
}

void NormalTxt::undo() {
	if (history.canUndo()) {
		history.undo(txt, cur);

		render();
		GotoXY(9, 28); // 移动光标到"<Normal> "之后
		cout << "undo!";
	} else {
		render();
		GotoXY(9, 28); // 移动光标到"<Normal> "之后
		cout << "No more undo!";
	}
	GotoXY(cur.X, cur.Y);
}

void NormalTxt::redo() {
	if (history.canRedo()) {
		history.redo(txt, cur);

		render();
		GotoXY(9, 28); // 移动光标到"<Normal> "之后
		cout << "redo!";
	} else {
		render();
		GotoXY(9, 28); // 移动光标到"<Normal> "之后
		cout << "No more redo!";
	}
	GotoXY(cur.X, cur.Y);
}

void NormalTxt::searchStr() {
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << '/';
	string pattern;
	cin.sync(); // 清空读入缓冲区
	std::getline(cin, pattern);
	KMPSearch(pattern, cur);
}
