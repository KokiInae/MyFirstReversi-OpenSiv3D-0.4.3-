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

	//座標ごとの石の状態
	Grid<int>cell;
	//座標ごとの石の状態の履歴
	Array<Grid<int>>cell_cache;
	//石の数の履歴(BLACK,WHITEの順)
	Array<Vec2>cell_color_cache;
	//描画に使うための石(図形)BOARD_SIZE * BOARD_SIZE個ある
	Grid<Circle>stones;

	//ボードのコンストラクタ
	Board(const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT);

	//ボード上の石を描画する
	void draw(const int& _player);
	//石を置けるかどうかを判断し、置けるなら置く
	bool can_put(const int& x,const int& y,const int& player);
	//置ける石の数とその座標のリストを持つ
	Array<Vec2> flippable_stone_list(const int& x, const int& y, const int& player);

};
