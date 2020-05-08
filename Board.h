#pragma once
#include<Siv3D.hpp>

class Board {

public:
	const int WHITE = 0;
	const int BLACK = 1;
	const int NONE = -1;
	int BOARD_SIZE;
	int SEAT_SIZE;
	int	PIT;
	int cell_black;
	int cell_white;
	Rect seat;
	Array<Line>lines_tate;
	Array<Line>lines_yoko;

	//���W���Ƃ̐΂̏��
	Grid<int>cell;
	//���W���Ƃ̐΂̏�Ԃ̗���
	Array<Grid<int>>cell_cache;
	//�΂̐��̗���(BLACK,WHITE�̏�)
	Array<Vec2>cell_color_cache;
	//�`��Ɏg�����߂̐�(�}�`)BOARD_SIZE * BOARD_SIZE����
	Grid<Circle>stones;

	//�{�[�h�̃R���X�g���N�^
	Board(const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT);

	//�{�[�h��̐΂�`�悷��
	void draw(const int& _player);
	//�΂�u���邩�ǂ����𔻒f���A�u����Ȃ�u��
	bool can_put(const int& x,const int& y,const int& player);
	//�u����΂̐��Ƃ��̍��W�̃��X�g������
	Array<Vec2> flippable_stone_list(const int& x, const int& y, const int& player);

};
