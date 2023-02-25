#ifndef TXT_H
#define TXT_H

#include "CursorOp.h"

#include <Windows.h>
#include <vector>
#include <stack>
#include <string>

using std::vector;
using std::stack;
using std::string;

class History{
private:
	stack<vector<string>> undo_txt_, redo_txt_; // �������������ı�����
	stack<COORD> undo_cur_, redo_cur_; // �����������Ĺ��λ��

public:
	void Save(const vector<string>& txt, const COORD& cur); // ��������ǰ��״̬
	void Undo(vector<string>& txt, COORD& cur); // ����
	void Redo(vector<string>& txt, COORD& cur); // ����
	bool CanUndo(){return static_cast<int>(undo_cur_.size()) > 0;} // Undo�շ�
	bool CanRedo(){return static_cast<int>(redo_cur_.size()) > 0;} // Undo�շ�
};

class Txt{
protected:
	vector<string> txt_; // �ı�����
	COORD cur_; // ���λ��
	History history_; // ��ʷ����

public:
	Txt(){}
	Txt(vector<string>& txt, COORD& cur, History& history)
		:txt_(txt), cur_(cur), history_(history){}

	virtual void HandleInput() = 0; // ��������
	virtual void Render() = 0; // ���ɴ���

	void MoveLeft(); // �������
	void MoveDown(); // �������
	void MoveUp(); // �������
	void MoveRight(); // �������
};

#endif
