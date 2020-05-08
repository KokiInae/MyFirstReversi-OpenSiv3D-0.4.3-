
# include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include"Board.h"
#include"Game.h"


void Main()
{
	// ウィンドウサイズを変更（シーンのサイズも同時に変更、こっちが本命）
	Window::Resize(1000, 700);
	// ウィンドウを手動リサイズ可能にする
	Window::SetStyle(WindowStyle::Sizable);
	//背景色設定
	Scene::SetBackground(Color(243, 244, 127));	//承和色

	const int WHITE = 0;
	const int BLACK = 1;
	//盤面のサイズ
	int BOARD_SIZE = 8;
	//シートのサイズ
	const int SEAT_SIZE = 600;
	//シートの基準点(左上)
	const int PIT = 50;

	//Boardクラスを継承したGameクラスの作成
	Game game;

	double temp_board_size = 8;
	int adjust_BOARD_SIZE;
	String adj;

	int SCENE = 0;
	const int TITLE = 0;
	const int PLAYGAME = 1;
	//indexでラジオボタンを識別する
	size_t index0 = 0;
	//選択肢を選ぶと選んでいる選択肢がひとつ目かnつ目かの状態が変わる?
	const Array<String>options = { U"黒が先行", U"白が先行" };
	const Array<int>colors = { BLACK,WHITE };
	const Font fonttitle(130);
	const Font subtitle(40);
	const Font score(70);
	const Font turn(50);
	const Font small(21);
	const Rect small_rect = small(U"盤の一辺の大きさ").region(30, 365);

	while (System::Update())
	{
		//switch文で分岐処理
		switch (SCENE) {
		case 0:
			fonttitle(U"リバーシ").drawBase(20, 180, Color(90, 195, 217));
			subtitle(U"(一人二役)").drawBase(600, 180, Color(90, 195, 217));

			SimpleGUI::RadioButtons(index0, options, Vec2(30, 280));

			small_rect.draw(Palette::White);
			small(U"盤の一辺の大きさ").draw(Vec2(30, 365), Palette::Black);
			SimpleGUI::Slider(adj, temp_board_size, 4.0, 30.0, Vec2(30, 395), 35, 350);
			//double型からint型にキャスト
			adjust_BOARD_SIZE = temp_board_size;
			//adjustが奇数なら-1引いて偶数になるように
			if (adjust_BOARD_SIZE % 2 != 0) {
				adjust_BOARD_SIZE--;
			}
			adj = Format(adjust_BOARD_SIZE);

			if (SimpleGUI::Button(U"プレイ！", Vec2(20, 500))) {
				//盤面の初期化
				game.make_Reversi_Board(adjust_BOARD_SIZE, SEAT_SIZE, PIT);
				//プレイヤーの色決め
				game.set_player(colors[index0]);

				SCENE = PLAYGAME;
			}

			break;

		case 1:
			Rect rect1 = score(U"黒:", game.cell_black, U"枚").region(730, 440);
			Rect rect2 = score(U"白:", game.cell_white, U"枚").region(730, 555);
			rect1.draw(Color(90, 195, 217));
			rect2.draw(Color(90, 195, 217));
			score(U"黒:", game.cell_black, U"枚").draw(730, 440, Color(12, 12, 12));
			score(U"白:", game.cell_white, U"枚").draw(730, 555, Color(252, 250, 242));
			if (game.PLAYER == BLACK) {
				turn(game.TURN + 1, U"手目:黒").draw(730, 30, Color(90, 195, 217));
			}
			else {
				turn(game.TURN + 1, U"手目:白").draw(730, 30, Color(90, 195, 217));
			}
			if (SimpleGUI::Button(U"一手戻る", Vec2(730, 180))) {
				game.undo_stone();
			}
			if (SimpleGUI::Button(U"スキップ", Vec2(730, 230))) {
				game.shift_player();
			}
			if (SimpleGUI::Button(U"タイトルに戻る", Vec2(48, 2))) {
				SCENE = TITLE;
			}
			
			game.draw(game.PLAYER);
			game.flip_stone();

			break;
		}
	}
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D ユーザコミュニティ Slack への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
