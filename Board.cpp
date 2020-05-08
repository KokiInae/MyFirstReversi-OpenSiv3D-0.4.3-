#include"Board.h"

Board::Board(const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT){
	BOARD_SIZE = _BOARD_SIZE;
	SEAT_SIZE = _SEAT_SIZE;
	PIT = _PIT;
	cell_black = 2;
	cell_white = 2;
	Grid <int>temp1(BOARD_SIZE, BOARD_SIZE, NONE);
	cell = temp1;
	cell[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = WHITE;
	cell[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = BLACK;
	cell[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = BLACK;
	cell[BOARD_SIZE / 2][BOARD_SIZE / 2] = WHITE;

	cell_cache.emplace_back(cell);
	cell_color_cache.emplace_back(cell_black, cell_white);

	int a = SEAT_SIZE / BOARD_SIZE;
	int b = a / 2;
	int c = (a / 2) * 0.85;
	int x = PIT + b;
	int y = PIT + b;
	Grid<Circle>temp2(BOARD_SIZE, BOARD_SIZE);
	stones = temp2;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			Circle stone(x, y, c);
			stones[i][j] = stone;
			x += a;
		}
		x = PIT + b;
		y += a;
	}

	Rect _seat(PIT, PIT, SEAT_SIZE);
	seat = _seat;
	for (int i = SEAT_SIZE / BOARD_SIZE; i < SEAT_SIZE; i += SEAT_SIZE / BOARD_SIZE) {
		Line a(PIT + i, PIT, PIT + i, PIT + SEAT_SIZE);
		Line b(PIT, PIT + i, PIT + SEAT_SIZE, PIT + i);
		lines_tate.emplace_back(a);
		lines_yoko.emplace_back(b);
	}

}



void Board::draw(const int& _player) {
	seat.draw(Color(90, 195, 217))	//�V���F
		.drawFrame(0, 3, Color(12,12,12));	//���l
	for (int i = 0; i < lines_tate.size(); i++) {
		lines_tate[i].draw(2, Color(252, 250, 242));	//����
		lines_yoko[i].draw(2, Color(252, 250, 242));
	}


	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			if (cell[y][x] == BLACK) {
				stones[y][x].draw(Color(0, 8, 26));	//�F�P�q��
			}
			else if (cell[y][x] == WHITE) {
				stones[y][x].draw(Color(252,250,242));	//����
			}
			else {
				Array<Vec2>f = flippable_stone_list(x, y, _player);
				if (f) {
					stones[y][x].draw(Color(243, 244, 127, 180));	//���a�F
					if (stones[y][x].mouseOver()) {
						stones[y][x]
							.draw(Color(243, 244, 127))
							.drawFrame(2, 1, Palette::Orange);
					}
				}
			}
		}
	}
}



bool Board::can_put(const int& _x, const int& _y, const int& _player) {
	/*
	x: �u���΂�x���W
    y: �u���΂�y���W
    player: �΂�u�����Ƃ��Ă���v���C���[(WHITE�܂���BLACK)
	*/

	/*
	true:�֐��̐�����\���B�w�肵�����W�ƁA����ɂ���Ċl���ł���΂�
	���ׂ�player�̐F�ɂȂ����ꍇ�ɕԂ�
	false:�֐��̎��s��\���B�w�肵�����W�ɂق��̐΂�����A
	�܂��͎w�肵�����W�ɐ΂�u���Ă�����̐΂��Ƃ�Ȃ��Ƃ��ɕԂ�
	*/

	//���ɂق��̐΂�����Βu���Ȃ�
	if (cell[_y][_x] != NONE) {
		return false;
	}

	Array<Vec2>flippable = flippable_stone_list(_x, _y, _player);

	//�u�����Ƃ���łЂ�����Ԃ���΂��Ȃ��Ă��u���Ȃ�
	if (flippable.isEmpty()) {
		return false;
	}
	
	//���ۂɐ΂�u����Ȃ�΂�u����true��Ԃ�
	cell[_y][_x] = _player;
	for (const auto& i : flippable) {
		cell[(int)i.y][(int)i.x] = _player;
	}
	//�΂̏�Ԃ̗����̒ǉ�
	cell_cache.emplace_back(cell);

	//�΂̐��̍X�V
	if (_player == BLACK) {
		cell_black++;
		cell_black += flippable.size();
		cell_white -= flippable.size();
	}
	else {
		cell_white++;
		cell_white += flippable.size();
		cell_black -= flippable.size();
	}
	//�΂̐��̗����̒ǉ�
	cell_color_cache.emplace_back(cell_black, cell_white);

	return true;
}



Array<Vec2> Board::flippable_stone_list(const int& _x, const int& _y, const int& _player) {
	Array<Vec2>flippable;

	for (int tate = 1; tate >= -1; tate--) {
		for (int yoko = -1; yoko <= 1; yoko++) {
			

			int depth = 0;
			Array<Vec2>temp;
			while (true) {
				depth++;
				//����*������8�����𒼐��I�ɒT��
				int rx = _x + (yoko * depth);
				int ry = _y + (tate * depth);

				//���ׂ���W(rx,ry)���A(cell[ry][rx]�Ƃ��\����)�{�[�h�͈͓̔��Ȃ��
				if ((0 <= rx && rx < BOARD_SIZE)
					&& (0 <= ry && ry < BOARD_SIZE)) {

					const int check = cell[ry][rx];
					//�T���Ő΂̖����}�X�ɂ�����I��
					if (check == NONE)break;
					//�T���Ńv���C���[�̎��}�X�ɂ�����I��
					else if (check == _player) {
						//�T�������͈͓��Ɋl���\�Ȑ΂������
						if (temp) {
							for (const auto& i : temp) {
								flippable.emplace_back(i);	//flippable�ɒǉ�
							}
						}
						break;
					}
					//����̐΂�������΁A�l���\�Ȑ΂Ƃ��Ĉꎞ�ۑ�
					else temp.emplace_back(rx, ry);
				}

				//���ׂ���W(rx,ry)���A(cell[ry][rx]�Ƃ��\����)�{�[�h�͈̔͊O�Ȃ��
				else break;
			}
		}
	}
	return flippable;
}
