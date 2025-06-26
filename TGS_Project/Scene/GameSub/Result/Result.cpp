#include"Result.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"
#include "../../../Utility/ResourceManager.h"

Result::Result() : ResultImageHandle(-1), Result_arrow(-1), bgmHandle(-1)
{

}

Result::~Result()
{

}

void Result::Initialize()
{
	//ゲームオーバー画像
	ResultImageHandle = LoadGraph("Resource/Images/Gameover2.png");
	Result_arrow = LoadGraph("Resource/Images/AimMark.png");

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> mobu_frames = rm->GetImages("Resource/Images/Enemy/Zombie_1/Walk.png", 10, 10, 1, 128, 128);

	for (int i = 0; i < 10; ++i)
	{
		mobu_walk[i] = mobu_frames[i];
	}

	mobu_image = mobu_walk[0];
	mobu_walk_index = 0;
	animation_count = 0;



	mobu_x = 1140;       //初期位置
	mobu_y = 350;
	mobu_speed = 0.4f;  //ゾンビの移動速度
	mobu_flip = true;   // 最初は右向き


	cursor_number = 0;
	cursor_x = 100;  //カーソルの初期位置

	// BGM 読み込みと再生
	bgmHandle = LoadSoundMem("Resource/Sounds/オープニング.mp3");
	if (bgmHandle != -1)
	{
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ループ再生
		ChangeVolumeSoundMem(130, bgmHandle);//音源の大きさ
	}

	//カーソル移動SE
	cursorSE = LoadSoundMem("Resource/Sounds/カーソル移動8.mp3");
	ChangeVolumeSoundMem(250, cursorSE);//音源の大きさ

	//決定ボタン
	kakutei = LoadSoundMem("Resource/Sounds/銃声6.mp3");
	ChangeVolumeSoundMem(300, kakutei);//音源の大きさ


}

eSceneType Result::Update(float delta_second)
{
	//入力機能の取得
	InputControl* input = InputControl::GetInstance();

	// 左入力（キーボード or コントローラー）
	if (input->GetKeyDown(KEY_INPUT_LEFT) || input->GetPadButtonState(PAD_INPUT_UP) == eInputState::ePress)
	{
		cursor_number--;
		if (cursor_number < 0)
			cursor_number = 1; // 左からループ

		PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK);//選択SE
	}

	// 右入力（キーボード or コントローラー）
	if (input->GetKeyDown(KEY_INPUT_RIGHT) || input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::ePress)
	{
		cursor_number++;
		cursor_number %= 2; // 右からループ

		PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK);//選択SE
	}

	// 決定（スペース or Bボタン）
	if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetPadButtonState(PAD_INPUT_RTRIGGER) == eInputState::ePress)
	{
		PlaySoundMem(kakutei, DX_PLAYTYPE_NORMAL);//決定ボタンSE

		switch (cursor_number)
		{
		case 0: return eSceneType::eInGame;
		case 1: return eSceneType::eEnd;
		}
	}

	// カーソル位置更新
	cursor_x = 60 + cursor_number * 690;


	mobu_x += mobu_speed;


	// 壁に当たったら反転（左右端）
	if (mobu_x >= 1250)  // 画面右端
	{
		mobu_speed = -mobu_speed; // 左に移動
		mobu_flip = false;
	}
	else if (mobu_x <= -350)
	{
		mobu_speed = -mobu_speed; // 右に移動
		mobu_flip = true;
	}

	animation_count++;
	AnimeControl();

	return GetNowSceneType();

}


void Result::Draw() const
{
	if (ResultImageHandle != -1)
	{
		DrawExtendGraph(0, 0, 1280, 720, ResultImageHandle, TRUE);

		// カーソル描画（x=100は仮、必要に応じて調整）
		// DrawExtendGraph(1000, cursor_x, 900, cursor_x + 110, Result_arrow, TRUE);
		DrawExtendGraph(cursor_x, 450, cursor_x + 100, 550, Result_arrow, TRUE);
	}
	
	/*DrawExtendGraph(576, 296, 704, 424, mobu_image, TRUE);*/
	const float scale = 2.0f; // 2倍に拡大

	if (mobu_flip)
	{
		// 左向き（左右反転）
		DrawRotaGraph2(mobu_x + 64, mobu_y + 64, 0, 0, scale, 0.0, mobu_image, TRUE, TRUE);
	}
	else
	{
		// 右向き（そのまま）
		DrawRotaGraph2(mobu_x + 64, mobu_y + 64, 0, 0, scale, 0.0, mobu_image, TRUE, FALSE);
	}
		

	
}

void Result::Finalize()
{
	if (ResultImageHandle != -1)
	{
		DeleteGraph(ResultImageHandle);
	}
	if (Result_arrow != -1)
	{
		DeleteGraph(Result_arrow);
	}
	//BGM終了処理
	if (bgmHandle != -1)
	{
		StopSoundMem(bgmHandle);
		DeleteSoundMem(bgmHandle);
	}
	DeleteSoundMem(cursorSE);
	DeleteSoundMem(kakutei);

}

void Result::AnimeControl()
{
	if (animation_count >= 30)
	{
		animation_count = 0;
		// 歩行アニメーションフレームを1つ進める（10枚ループ）
		mobu_walk_index = (mobu_walk_index + 1) % 10;
		mobu_image = mobu_walk[mobu_walk_index]; // 現在の画像を歩行用に更新
	}
}


eSceneType Result::GetNowSceneType() const
{
	return eSceneType::eResult;
}
