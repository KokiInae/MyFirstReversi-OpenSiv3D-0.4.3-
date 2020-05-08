# MyFirstReversi
OpenSiv3Dで作成したリバーシです

開発発環
- OpenSiv3D(0.4.3)
- Visual Studio 2019

ファイルの説明

- Board.cpp:ボードの状態の初期化、ボードに石を置こうとした時の処理と、ボードの描画をするクラスです。
- Board.h:Board.cppのヘッダーファイル。
- Game.cpp:Boardクラスを継承したクラス。プレイヤーの色決め、手番交代、一手戻るなどの関数をBoardクラスから追加しています。
- Game.h:ゲームクラスのヘッダーファイル。
- Main.cpp:シーン間の管理、文字の描画、GUIの描画、GUIへの入力に応じた関数呼び出しなどをします。
- Reversi.exe:つくったオセロの実行ファイルです。これ単体で動作します。
- README.md:ファイルの説明や注釈を書いています。
