#include "../include/Txt.h"

void History::Save(const vector<string>& txt, const COORD& cur){
	undo_txt_.push(txt); // ������β������ı�
	undo_cur_.push(cur); // ������β����Ĺ��λ��
}

void History::Undo(vector<string>& txt, COORD& cur){
	if(!undo_txt_.empty() && !undo_cur_.empty()){
		// �ı�����
		txt = undo_txt_.top(); // ��ȡ��һ�ε�txt
		undo_txt_.pop(); // ɾ��
		redo_txt_.push(txt); // ����
		// ������
		cur.X = undo_cur_.top().X; cur.Y = undo_cur_.top().Y; // ��ȡ��һ�εĹ��λ��
		undo_cur_.pop(); // ɾ��
		redo_cur_.push(cur); // ����
	}
}

void History::Redo(vector<string>& txt, COORD& cur){
	if(!redo_txt_.empty() && !redo_cur_.empty()){
		// �ı�����
		txt = redo_txt_.top(); // ��ȡ��һ�ε�txt
		redo_txt_.pop(); // ɾ��
		undo_txt_.push(txt); // ����
		// ������
		cur.X = redo_cur_.top().X; cur.Y = redo_cur_.top().Y; // ��ȡ��һ�εĹ��λ��
		redo_cur_.pop(); // ɾ��
		undo_cur_.push(cur); // ����
	}
}

void Txt::MoveLeft(){
	if(cur_.X == 0 && cur_.Y == 0) return;
	history_.Save(txt_, cur_); // ������ʷ����
	if(cur_.X > 0) // ��������
		cur_.X--;
	else{ // �Ƶ���һ�е�ĩβ
		cur_.Y--;
		cur_.X = static_cast<int>(txt_[cur_.Y].size()) > 0 ? 
			static_cast<int>(txt_[cur_.Y].size()) - 1 : 0;
	}
}

void Txt::MoveDown(){
	if(cur_.Y >= 26) return;
	history_.Save(txt_, cur_); // ������ʷ����
	cur_.Y++; // ����
	if(cur_.Y < static_cast<int>(txt_.size())){
		if(cur_.X > static_cast<int>(txt_[cur_.Y].size())) // ������һ��̫��Ͷ�λ����һ�ж�һ���ֵĵط�
				cur_.X = static_cast<int>(txt_[cur_.Y].size());
	}else{ // ����һ��
		txt_.insert(txt_.begin() + cur_.Y, string()); // �������
		cur_.X = 0; // ͷ
	}
}

void Txt::MoveUp(){
	if(cur_.Y == 0) return;
	history_.Save(txt_, cur_); // ������ʷ����
	if(cur_.Y == static_cast<int>(txt_.size() - 1) && 
		static_cast<int>(txt_[cur_.Y].size()) == 0) // ������ǿ���
		txt_.erase(txt_.begin() + cur_.Y); // ɾ������
	cur_.Y--;
	if(cur_.X > static_cast<int>(txt_[cur_.Y].size())) // ������һ��̫��Ͷ�λ����һ�ж�һ���ֵĵط�
		cur_.X = static_cast<int>(txt_[cur_.Y].size());
}

void Txt::MoveRight(){
	if(cur_.X == static_cast<int>(txt_[cur_.Y].size()) && 
		cur_.Y == static_cast<int>(txt_.size()) - 1) return; // �ı�ĩβ������������
	history_.Save(txt_, cur_); // ������ʷ����
	if(cur_.X < static_cast<int>(txt_[cur_.Y].size()))
		cur_.X++; // �������ƣ����Ա���һ�ж�1���֣��������ٳ�ȥ
	else{ // ��һ�п�ͷ
		cur_.Y++; cur_.X = 0;
	}	
}
