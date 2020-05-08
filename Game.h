#pragma once
#include <Siv3D.hpp>
#include"Board.h"

class Game:public Board{
public:
	Game(const int& _player, const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT);
	Game(const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT);

	//�v���C���[��BLACK�܂���WHITE�ɂȂ�
	int PLAYER;
	//�^�[����
	int TURN = 0;

	//�v���C���[�̐F�����߂�
	void set_player(const int& _player);
	//�΂��N���b�N���ĂЂ�����Ԃ��v���C���[���
	void flip_stone();
	//�v���C���[����シ��
	void shift_player();
	//���߂�
	void undo_stone();
	//��l�܂�̃`�F�b�N�Ǝ菇�̃X�L�b�v���s��
	//void check_skip_turn(const int& _player);

};
