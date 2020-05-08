#include"Game.h"

Game::Game(const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT)
	: Board(_BOARD_SIZE, _SEAT_SIZE, _PIT) {
}



Game::Game()
	: Board() {
}



void Game::make_Reversi_Board(const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT) {
	BOARD_SIZE = _BOARD_SIZE;
	SEAT_SIZE = _SEAT_SIZE;
	PIT = _PIT;
	TURN = 0;
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

	Array<Line>temp_tate;
	Array<Line>temp_yoko;
	for (int i = SEAT_SIZE / BOARD_SIZE; i < SEAT_SIZE; i += SEAT_SIZE / BOARD_SIZE) {
		Line a(PIT + i, PIT, PIT + i, PIT + SEAT_SIZE);
		Line b(PIT, PIT + i, PIT + SEAT_SIZE, PIT + i);
		temp_tate.emplace_back(a);
		temp_yoko.emplace_back(b);
	}
	lines_tate = temp_tate;
	lines_yoko = temp_yoko;
}



void Game::set_player(const int& _player) {
	PLAYER = _player;
}



void Game::flip_stone() {
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			if (stones[y][x].leftClicked()) {
				if (can_put(x, y, PLAYER)) {
					shift_player();
					TURN++;
				}
			}
		}
	}
}



void Game::shift_player() {
	if (PLAYER == BLACK) {
		PLAYER = WHITE;
	}
	else if (PLAYER == WHITE) {
		PLAYER = BLACK;
	}
}



void Game::undo_stone() {
	//空のキャッシュを呼び出さないよう注意
	if (cell_cache.size() > 1) {
		cell_cache.pop_back();
		cell_color_cache.pop_back();

		cell = cell_cache.back();
		cell_black = cell_color_cache.back().x;
		cell_white = cell_color_cache.back().y;

		shift_player();
		TURN--;
	}
}



/*
void Game::check_skip_turn(const int& _player) {
	bool check = false;
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			Array<Vec2>temp = flippable_stone_list(x, y, _player);
			if (temp) {
				check = true;
			}
		}
	}
	if (check == true) {
		shift_player();
	}
}
*/