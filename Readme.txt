作品説明

本作品はOpenGL、SDL、その他標準ライブラリを使用した3D迷路脱出ゲームである。
ステージの左下からスタートする。
ステージ中央部分のどこかにある鍵を入手してステージ右上の出口にたどり着くとステージクリア。
補助機能として「足跡機能」が実装されているが、オプション画面から機能のオンとオフを切り替えることができる。
迷路はステージを選択する度にランダムに作成される。



操作方法

タイトル画面
上下の矢印キーでステージのレベル、オプション画面を選択
Enterキーで決定

オプション画面
左右の矢印キーでオン、オフを選択
Enterキーで決定

ゲーム画面
上下の矢印キーで前進、後退
左右の矢印キーで視点を左右に90度回転
鍵の取得、ゴールの開放は触れることで可能
Pキーでポーズ画面に移動

ポーズ画面
左右の矢印キーで続行、中断を選択
Enterキーで決定

リザルト画面
Enterキーでタイトル画面に移動

全ての画面
Escキーでゲーム終了



使用ライブラリ

freeglut-3.6.0		glut.h

SDL2-2.30.9		SDL.h

SDL2_mixer-2.8.0	SDL_mixer.h

C言語標準ライブラリ	stdlib.h 
			math.h
			time.h

C++標準ライブラリ	vector
			random
			chrono
			string
			cstring



使用素材

効果音：効果音ラボ
アスファルトの上を走る1.mp3(wav形式へと変換)
https://soundeffect-lab.info/sound/search.php?s=%E3%82%A2%E3%82%B9%E3%83%95%E3%82%A1%E3%83%AB%E3%83%88%E3%81%AE%E4%B8%8A%E3%82%92%E8%B5%B0%E3%82%8B1
鞘を持つ.mp3(wav形式へと変換)
https://soundeffect-lab.info/sound/search.php?s=%E9%9E%98%E3%82%92%E6%8C%81%E3%81%A4
門を開ける.mp3(wav形式へと変換)
https://soundeffect-lab.info/sound/search.php?s=%E9%96%80%E3%82%92%E9%96%8B%E3%81%91%E3%82%8B

BGM：FREE BGM  DOVA-SYNDROME
真相究明.mp3
https://dova-s.jp/bgm/play19810.html
迷宮未発表　make_me_happy.mp3
https://dova-s.jp/bgm/play9218.html
ビクトリートンカツ.mp3
https://dova-s.jp/bgm/play11358.html