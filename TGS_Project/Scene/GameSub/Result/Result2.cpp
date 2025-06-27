#include"Result2.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"

Result2::Result2() : ResultImageHandle(-1), Result_arrow(-1), bgmHandle(-1)
{

}

Result2::~Result2()
{

}

void Result2::Initialize()
{
	ResultImageHandle = LoadGraph("Resource/Images/CLEAR.png");
	Result_arrow = LoadGraph("Resource/Images/AimMark.png");

	cursor_number = 0;
	cursor_x = 100;  //カーソルの初期位置

	// BGM 読み込みと再生
	bgmHandle = LoadSoundMem("Resource/Sounds/Title.mp3");
	if (bgmHandle != -1)
	{
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ループ再生
		ChangeVolumeSoundMem(200, bgmHandle);
	}
	//カーソル移動SE
	cursorSE = LoadSoundMem("Resource/Sounds/カーソル移動8.mp3");
	ChangeVolumeSoundMem(250, cursorSE);//音源の大きさ

	//決定ボタン
	kakutei = LoadSoundMem("Resource/Sounds/銃声6.mp3");
	ChangeVolumeSoundMem(300, kakutei);//音源の大きさ

}

eSceneType Result2::Update(float delta_second)
{
	//入力機能の取得
	InputControl* input = InputControl::GetInstance();

	// 左入力（キーボード or コントローラー）
	if (input->GetKeyDown(KEY_INPUT_LEFT) || input->GetPadButtonState(PAD_INPUT_RIGHT) == eInputState::ePress)
	{
		cursor_number--;
		if (cursor_number < 0)
			cursor_number = 1; // 左からループ

		PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK);//選択SE

	}

	// 右入力（キーボード or コントローラー）
	if (input->GetKeyDown(KEY_INPUT_RIGHT) || input->GetPadButtonState(PAD_INPUT_LEFT) == eInputState::ePress)
	{
		cursor_number++;
		cursor_number %= 2; // 右からループ

		PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK);//選択SE

	}

	// 決定（スペース or Bボタン）
	if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetPadButtonState(PAD_INPUT_B) == eInputState::ePress)
	{
		PlaySoundMem(kakutei, DX_PLAYTYPE_NORMAL);//決定ボタンSE

		switch (cursor_number)
		{
		case 0: return eSceneType::eTitle;
		case 1: return eSceneType::eEnd;
		}
	}

	// カーソル位置更新
	cursor_x = 60 + cursor_number * 690;

	return GetNowSceneType();
}


void Result2::Draw() const
{
	if (ResultImageHandle != -1)
	{
		DrawExtendGraph(0, 0, 1280, 720, ResultImageHandle, TRUE);

		// カーソル描画（x=100は仮、必要に応じて調整）
		// DrawExtendGraph(1000, cursor_x, 900, cursor_x + 110, Result_arrow, TRUE);
		DrawExtendGraph(cursor_x, 450, cursor_x + 100, 550, Result_arrow, TRUE);
	}

	//DrawFormatString(10, 10, GetColor(255, 255, 255), "リザルト画面です");
}

void Result2::Finalize()
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

eSceneType Result2::GetNowSceneType() const
{
	return eSceneType::eResult2;
}
