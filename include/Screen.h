#ifndef SCREEN_H
#define SCREEN_H

class Screen{
public:
	virtual void HandleInput() = 0; // ��������
	virtual void Render() = 0; // ���ɴ���
};

#endif
