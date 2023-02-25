#include "../include/NormalTxt.h"
#include "../include/InsertTxt.h"
#include "../include/EditorScreen.h"

#include <iostream>
#include <conio.h>

using std::cout;
using std::endl;
using std::cin;

enum Dir {Up = 72, Down = 80, Left = 75, Right = 77, ESC = 27};

void InsertTxt::HandleInput(){
	cin.sync(); // ������뻺����
	char cmd = _getch(); // ��ȡ�ַ�
	if(!isascii(cmd)) // ���ַ�ת��Ϊ����ָ��
		cmd = _getch();
	switch(cmd){
	case Left: // �������
		MoveLeft();
		break;
	case Down: // �������
		MoveDown();
		break;
	case Up: // �������
		MoveUp();
		break;
	case Right: // �������
		MoveRight();
		break;
	case ESC: // ��ͨģʽ
		EditorScreen::text_ = std::make_shared<NormalTxt>(txt_, cur_, history_);
		break;
	default: // �����ַ�
		Insert(cmd);
		break;
	}
}

void InsertTxt::Render(){
	// ����
	system("cls");
	// �ײ���Ŀ
	GotoXY(0, 28);
	cout << "<Insert>";
	// ��ʾ�ı�
	if(txt_.size() == 0) return;
	GotoXY(0, 0);
	if(txt_.size() == 0) return;
	int len = txt_.size();
	for(int i = 0; i < len - 1; i++)
		cout << txt_[i] << endl;
	cout << txt_[len - 1];
	// ��ʾ���
	GotoXY(cur_.X, cur_.Y);
}

void InsertTxt::Insert(char& cmd){
	if(isprint(cmd)){
		if(cur_.Y < static_cast<int>(txt_.size()) && 
			cur_.X <= static_cast<int>(txt_[cur_.Y].size())){ // ��ĳһ���е��в���
			history_.Save(txt_, cur_); // ������ʷ����
			txt_[cur_.Y].insert(txt_[cur_.Y].begin() + cur_.X++, cmd); // ���벢����x

			Render();
			GotoXY(9, 28); // �ƶ���굽"<Normal> "֮��
			cout << "Insert!";
			GotoXY(cur_.X, cur_.Y);
		}
	}
}
