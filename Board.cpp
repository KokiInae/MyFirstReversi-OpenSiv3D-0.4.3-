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
	seat.draw(Color(90, 195, 217))	//新橋色
		.drawFrame(0, 3, Color(12,12,12));	//紺鼠
	for (int i = 0; i < lines_tate.size(); i++) {
		lines_tate[i].draw(2, Color(252, 250, 242));	//白練
		lines_yoko[i].draw(2, Color(252, 250, 242));
	}


	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			if (cell[y][x] == BLACK) {
				stones[y][x].draw(Color(0, 8, 26));	//檳榔子黒
			}
			else if (cell[y][x] == WHITE) {
				stones[y][x].draw(Color(252,250,242));	//白練
			}
			else {
				Array<Vec2>f = flippable_stone_list(x, y, _player);
				if (f) {
					stones[y][x].draw(Color(243, 244, 127, 180));	//承和色
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
	x: 置く石のx座標
    y: 置く石のy座標
    player: 石を置こうとしているプレイヤー(WHITEまたはBLACK)
	*/

	/*
	true:関数の成功を表す。指定した座標と、それによって獲得できる石が
	すべてplayerの色になった場合に返す
	false:関数の失敗を表す。指定した座標にほかの石がある、
	または指定した座標に石を置いても相手の石をとれないときに返す
	*/

	//既にほかの石があれば置けない
	if (cell[_y][_x] != NONE) {
		return false;
	}

	Array<Vec2>flippable = flippable_stone_list(_x, _y, _player);

	//置いたところでひっくり返せる石がなくても置けない
	if (flippable.isEmpty()) {
		return false;
	}
	
	//実際に石を置けるなら石を置いてtrueを返す
	cell[_y][_x] = _player;
	for (const auto& i : flippable) {
		cell[(int)i.y][(int)i.x] = _player;
	}
	//石の状態の履歴の追加
	cell_cache.emplace_back(cell);

	//石の数の更新
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
	//石の数の履歴の追加
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
				//方向*高さで8方向を直線的に探索
				int rx = _x + (yoko * depth);
				int ry = _y + (tate * depth);

				//調べる座標(rx,ry)が、(cell[ry][rx]とも表せる)ボードの範囲内ならば
				if ((0 <= rx && rx < BOARD_SIZE)
					&& (0 <= ry && ry < BOARD_SIZE)) {

					const int check = cell[ry][rx];
					//探索で石の無いマスについたら終了
					if (check == NONE)break;
					//探索でプレイヤーの持つマスについたら終了
					else if (check == _player) {
						//探索した範囲内に獲得可能な石があれば
						if (temp) {
							for (const auto& i : temp) {
								flippable.emplace_back(i);	//flippableに追加
							}
						}
						break;
					}
					//相手の石が見つかれば、獲得可能な石として一時保存
					else temp.emplace_back(rx, ry);
				}

				//調べる座標(rx,ry)が、(cell[ry][rx]とも表せる)ボードの範囲外ならば
				else break;
			}
		}
	}
	return flippable;
}
