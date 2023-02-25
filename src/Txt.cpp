#include "../include/Txt.h"

void History::Save(const vector<string>& txt, const COORD& cur){
	undo_txt_.push(txt); // 保留这次操作的文本
	undo_cur_.push(cur); // 保留这次操作的光标位置
}

void History::Undo(vector<string>& txt, COORD& cur){
	if(!undo_txt_.empty() && !undo_cur_.empty()){
		// 文本操作
		txt = undo_txt_.top(); // 获取上一次的txt
		undo_txt_.pop(); // 删除
		redo_txt_.push(txt); // 插入
		// 光标操作
		cur.X = undo_cur_.top().X; cur.Y = undo_cur_.top().Y; // 获取上一次的光标位置
		undo_cur_.pop(); // 删除
		redo_cur_.push(cur); // 插入
	}
}

void History::Redo(vector<string>& txt, COORD& cur){
	if(!redo_txt_.empty() && !redo_cur_.empty()){
		// 文本操作
		txt = redo_txt_.top(); // 获取上一次的txt
		redo_txt_.pop(); // 删除
		undo_txt_.push(txt); // 插入
		// 光标操作
		cur.X = redo_cur_.top().X; cur.Y = redo_cur_.top().Y; // 获取上一次的光标位置
		redo_cur_.pop(); // 删除
		undo_cur_.push(cur); // 插入
	}
}

void Txt::MoveLeft(){
	if(cur_.X == 0 && cur_.Y == 0) return;
	history_.Save(txt_, cur_); // 保留历史操作
	if(cur_.X > 0) // 本行左移
		cur_.X--;
	else{ // 移到上一行的末尾
		cur_.Y--;
		cur_.X = static_cast<int>(txt_[cur_.Y].size()) > 0 ? 
			static_cast<int>(txt_[cur_.Y].size()) - 1 : 0;
	}
}

void Txt::MoveDown(){
	if(cur_.Y >= 26) return;
	history_.Save(txt_, cur_); // 保留历史操作
	cur_.Y++; // 下移
	if(cur_.Y < static_cast<int>(txt_.size())){
		if(cur_.X > static_cast<int>(txt_[cur_.Y].size())) // 超过这一行太多就定位到这一行多一个字的地方
				cur_.X = static_cast<int>(txt_[cur_.Y].size());
	}else{ // 另起一行
		txt_.insert(txt_.begin() + cur_.Y, string()); // 插入空行
		cur_.X = 0; // 头
	}
}

void Txt::MoveUp(){
	if(cur_.Y == 0) return;
	history_.Save(txt_, cur_); // 保留历史操作
	if(cur_.Y == static_cast<int>(txt_.size() - 1) && 
		static_cast<int>(txt_[cur_.Y].size()) == 0) // 最底下是空行
		txt_.erase(txt_.begin() + cur_.Y); // 删除空行
	cur_.Y--;
	if(cur_.X > static_cast<int>(txt_[cur_.Y].size())) // 超过这一行太多就定位到这一行多一个字的地方
		cur_.X = static_cast<int>(txt_[cur_.Y].size());
}

void Txt::MoveRight(){
	if(cur_.X == static_cast<int>(txt_[cur_.Y].size()) && 
		cur_.Y == static_cast<int>(txt_.size()) - 1) return; // 文本末尾，不能再右移
	history_.Save(txt_, cur_); // 保留历史操作
	if(cur_.X < static_cast<int>(txt_[cur_.Y].size()))
		cur_.X++; // 本行右移，可以比这一行多1个字，但不能再出去
	else{ // 下一行开头
		cur_.Y++; cur_.X = 0;
	}	
}
