#include "../include/NormalTxt.h"
#include "../include/InsertTxt.h"
#include "../include/EditorScreen.h"
#include "../include/GoodbyeScreen.h"
#include "../include/Editor.h"

#include <iostream>
#include <conio.h>

using std::cout;
using std::cin;
using std::endl;
using std::ios;

void NormalTxt::HandleInput(){
	cin.sync(); // ������뻺����
	char cmd = _getch(); // ��ȡ�ַ�
	if(!isascii(cmd)) // ���ַ�ת��Ϊ����ָ��
		cmd = _getch();
	switch(cmd){
	case ':': // �ļ���д
		RWTxt();
		break;
	// case 'q': // �˳�
	// 	Editor::screen_ = std::make_shared<GoodbyeScreen>();
	// 	break;
	case 'x': // ɾ����괦���ַ�
		Delete();
		break;
	case 'u': // ��������
		Undo();
		break;
	case 'r': // ��������
		Redo();
		break;
	case 'h': // �������
		MoveLeft();
		break;
	case 'j': // �������
		MoveDown();
		break;
	case 'k': // �������
		MoveUp();
		break;
	case 'l': // �������
		MoveRight();
		break;
	case 'i': // ����ģʽ
		EditorScreen::text_ = std::make_shared<InsertTxt>(txt_, cur_, history_);
		break;
	case '/': // Ѱ��ģʽ
		Search();
		break;
	}
}

void NormalTxt::Render(){
	// ����
	system("cls");
	// �ײ���Ŀ
	GotoXY(0, 27);
	cout << "����������������������������������������������Command����������������������������������������������";
	GotoXY(0, 28);
	cout << "<Normal> ";
	// ��ʾ�ı�
	GotoXY(0, 0);
	if(txt_.size() == 0) return;
	int len = txt_.size();
	for(int i = 0; i < len - 1; i++)
		cout << txt_[i] << endl;
	cout << txt_[len - 1];
	// ��ʾ���
	GotoXY(cur_.X, cur_.Y);
}

void NormalTxt::ReadTxt(string& filename){
	file_.close(); // �ر���һ���ļ�
	file_.open(filename.data(), ios::in); // �����ļ�����ģʽ
	if(!file_.is_open()){
		Render();
		GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
		cout << "File Not Found!";
		GotoXY(cur_.X, cur_.Y);
		return;
	}

	Render();
	GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
	cout << "Opening...";

	ExtractTxt(); // ��ȡ�ļ����ݵ�������
	// ��ȡ���λ��
	cur_.Y = static_cast<int>(txt_.size()) - 1;
	cur_.X = static_cast<int>(txt_[cur_.Y].size()) - 1;
	history_.Save(txt_, cur_); // ������ʷ����
}

void NormalTxt::ExtractTxt(){
	txt_.resize(0); txt_.shrink_to_fit(); // ��ʼ��txt
	if(file_.is_open()){ // �ļ���ʱ����
		file_.seekg(0, ios::beg); // ���ļ�ָ��ָ��ͷ
		while(!file_.eof()){ // �����ļ�ĩβ
			string line;
			getline(file_,line);
			txt_.push_back(line);
		}
		file_.seekg(0, ios::beg); // ���ļ�ָ��ָ��ͷ
	}
}

void NormalTxt::WriteTxt(string& filename){
	Render();
	GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
	cout << "Saving...";

	file_.close(); // �ر���һ���ļ�
	file_.open(filename.data(), ios::out); // �����ļ���дģʽ
	if(txt_.size() == 0) return;
	int len = txt_.size();
	for(int i = 0; i < len - 1; i++)
		file_ << txt_[i] << endl;
	file_ << txt_[len - 1];
}

void NormalTxt::PreProcess(const string& p, vector<int>& next){
	int len = p.size(); // p����
	next.resize(len); next.shrink_to_fit(); // next����
	int i(0), j = next[0] = -1; // ��ʼ��
	while(i < len - 1){
		while(j > -1 && p[i] != p[j])
			j = next[j];
		i++; j++;
		if(p[i] == p[j]) next[i] = next[j];
		else next[i] = j;
	}
}

void NormalTxt::KMPSearch(string& pattern, COORD& cur){
	vector<int> next; PreProcess(pattern, next); // Ԥ����
	int plen = pattern.size(), ylen = static_cast<int>(txt_.size()), xlen(0);
	for(int p = cur.Y; p < ylen; p++){ // �������ҵ�ĩβ
		int q = (p == cur.Y) ? cur.X : 0, k(0); // ��ʼ��q��ֵx������ֵ0
		xlen = static_cast<int>(txt_[p].size()); // ���еĳ���
		while(q < xlen){ // q�������в���
			while(k > -1 && pattern[k] != txt_[p][q])
				k = next[k];
			q++; k++;
			if(k == plen){ // �ҵ�
				history_.Save(txt_, cur); // ������ʷ����
				cur.X = q - k; // ��λx
				cur.Y = p; // ��λy
				GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
				cout << "Found! Locate cursor to first \"" << pattern << "\"!"; // ����ҵ���Ϣ
				GotoXY(cur.X, cur.Y); // ��λ���
				Sleep(1000); // ����1��
				return;
			}
		}
	}
	// û�ҵ�
	Render();
	GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
	cout << "Not Found! Do you want to find \"" << pattern << "\" from begnning?(y/n)"; // ���û�ҵ���Ϣ
	char choice;
	cin >> choice;
	if(choice == 'y'){
		Render();
		history_.Save(txt_, cur); // ������ʷ����
		cur.X = 0; cur.Y = 0; // ��λ����ͷ
		KMPSearch(pattern, cur);
	}
}

void NormalTxt::RWTxt(){
	string op, filename;
	GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
	cout << ":";
	cin >> op;
	if(op == "q") {
		Editor::screen_ = std::make_shared<GoodbyeScreen>();
		return;
	}
	cin >> filename;
	filename = "file/" + filename;
	if(op == "open") // ��
		ReadTxt(filename);
	else if(op == "w") // д
		WriteTxt(filename); // д�ļ�
}

void NormalTxt::Delete(){
	if(cur_.X == 0 && cur_.Y == 0 && static_cast<int>(txt_.size()) == 0) return; // ��һ�п�ͷ������

	Render();
	GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
	cout << "Delete!";
	GotoXY(cur_.X, cur_.Y);

	history_.Save(txt_, cur_); // ������ʷ����

	if(cur_.X == 0 && cur_.Y == 0){ // ��һ�п�ͷ���ı�����
		if(static_cast<int>(txt_[0].size()) == 0) // ����
			txt_.erase(txt_.begin()); // ɾ������
		else // ����
			txt_[0].erase(txt_[0].begin()); // ɾ����һ����
		return;
	}
	
	if(cur_.X == 0){ // ����1��
		txt_[cur_.Y].erase(txt_[cur_.Y].begin() + cur_.X); // ɾ��
		if(static_cast<int>(txt_[cur_.Y].size()) == 0) // ����
			txt_.erase(txt_.begin() + cur_.Y); // ɾ������
		cur_.Y--; // �Ƶ���һ��
		cur_.X = static_cast<int>(txt_[cur_.Y].size()) > 0 ? 
			static_cast<int>(txt_[cur_.Y].size()) - 1 : 0; // �Ƶ�ĩβ
	}else 
		if(cur_.X < static_cast<int>(txt_[cur_.Y].size())) // ��Чɾ�������ڣ����ڸ���ĩβ֮��
			txt_[cur_.Y].erase(txt_[cur_.Y].begin() + cur_.X--); // ɾ��������
		else // �ڸ���ĩβ֮��
			cur_.X--; // ֱ������
}

void NormalTxt::Undo(){
	if(history_.CanUndo()){
		history_.Undo(txt_, cur_);

		Render();
		GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
		cout << "Undo!";
	}else{
		Render();
		GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
		cout << "No more Undo!";
	}
	GotoXY(cur_.X, cur_.Y);
}

void NormalTxt::Redo(){
	if(history_.CanRedo()){
		history_.Redo(txt_, cur_);

		Render();
		GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
		cout << "Redo!";
	}else{
		Render();
		GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
		cout << "No more Redo!";
	}
	GotoXY(cur_.X, cur_.Y);
}

void NormalTxt::Search(){
	GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
	cout << '/';
	string pattern;
	cin.sync(); // ��ն��뻺����
	std::getline(cin, pattern);
	KMPSearch(pattern, cur_);
}
