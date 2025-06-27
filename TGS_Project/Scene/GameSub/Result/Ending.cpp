#include"Ending.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"

Ending::Ending() : EndImageHandle(-1), End_arrow(-1), bgmHandle(-1)
{

}

Ending::~Ending()
{

}

void Ending::Initialize()
{
	EndImageHandle = LoadGraph("Resource/Images/CLEAR.png");
	End_arrow = LoadGraph("Resource/Images/AimMark.png");

	cursor_number = 0;
	cursor_x = 100;  //カーソルの初期位置

	// フォントサイズ32、太さ6、ゴシック体のフォントを作成
	fontHandle = CreateFontToHandle("ＭＳ ゴシック", 32, 6, DX_FONTTYPE_ANTIALIASING);


	// BGM 読み込みと再生
	bgmHandle = LoadSoundMem("Resource/Sounds/クリア用.mp3");
	if (bgmHandle != -1)
	{
		ChangeVolumeSoundMem(200, bgmHandle); // 音量を200に設定（0?255）
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ループ再生
	}

	//カーソル移動SE
	cursorSE = LoadSoundMem("Resource/Sounds/カーソル移動8.mp3");
	if (cursorSE != -1) {
		ChangeVolumeSoundMem(250, cursorSE);//音源の大きさ
	}

	//決定ボタン
	kakutei = LoadSoundMem("Resource/Sounds/銃声6.mp3");
	if (kakutei != -1) {
		ChangeVolumeSoundMem(300, kakutei);//音源の大きさ
	}



	if (EndImageHandle == -1 || End_arrow == -1 || bgmHandle == -1) {
		printfDx("Endシーンのリソース読み込みに失敗しました\n");
	}
}

eSceneType Ending::Update(float delta_second)
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
		case 0: return eSceneType::eTitle;
		case 1: return eSceneType::eEnd;
		}
	}

	// カーソル位置更新
	cursor_x = 60 + cursor_number * 690;

	return GetNowSceneType();
}


void Ending::Draw() const
{
	if (EndImageHandle != -1)
	{
		DrawExtendGraph(0, 0, 1280, 720, EndImageHandle, TRUE);

		// メッセージ表示
		const char* message = "すべてのウェーブを乗り越えた！";
		int text_width = GetDrawStringWidthToHandle(message, strlen(message), fontHandle);
		DrawStringToHandle((1280 - text_width) / 2, 90, message, GetColor(255, 255, 255), fontHandle);
	}

	// カーソル描画（x=100は仮、必要に応じて調整）
		// DrawExtendGraph(1000, cursor_x, 900, cursor_x + 110, Result_arrow, TRUE);
	DrawExtendGraph(cursor_x, 450, cursor_x + 100, 550, End_arrow, TRUE);

	//DrawFormatString(10, 10, GetColor(255, 255, 255), "リザルト画面です");
}

void Ending::Finalize()
{
	if (EndImageHandle != -1)
	{
		DeleteGraph(EndImageHandle);
	}
	if (End_arrow != -1)
	{
		DeleteGraph(End_arrow);
	}
	//BGM終了処理
	if (bgmHandle != -1)
	{
		StopSoundMem(bgmHandle);
		DeleteSoundMem(bgmHandle);
	}
	if (fontHandle != -1)
	{
		DeleteFontToHandle(fontHandle);
	}
}

eSceneType Ending::GetNowSceneType() const
{
	return eSceneType::eEnding;
}
