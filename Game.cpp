#include"Game.h"

Game::Game(const int& _player, const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT)
	: Board(_BOARD_SIZE, _SEAT_SIZE, _PIT){
	PLAYER = _player;
}



Game::Game(const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT)
	: Board(_BOARD_SIZE, _SEAT_SIZE, _PIT) {
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