#pragma once
#include <Siv3D.hpp>
#include"Board.h"

class Game:public Board{
public:
	Game(const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT);
	//ゲームのコンストラクタ(引数なし、こっちを使っている)
	Game();

	//プレイヤーはBLACKまたはWHITEになる
	int PLAYER;
	//ターン数
	int TURN = 0;

	//Gameクラスを初期化する
	void make_Reversi_Board(const int& _BOARD_SIZE, const int& _SEAT_SIZE, const int& _PIT);
	//プレイヤーの色を決める
	void set_player(const int& _player);
	//石をクリックしてひっくり返しプレイヤー交代
	void flip_stone();
	//プレイヤーを交代する
	void shift_player();
	//一手戻る
	void undo_stone();
	//手詰まりのチェックと手順のスキップを行う
	//void check_skip_turn(const int& _player);

};
