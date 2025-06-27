#include "TitleScene.h"
#include "DxLib.h"
#include"../../../Utility/InputControl.h"

TitleScene::TitleScene() : titleImageHandle(-1), title_arrow(-1),bgmHandle(-1)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	titleImageHandle = LoadGraph("Resource/Images/Title_new.png");
	title_arrow = LoadGraph("Resource/Images/AimMark.png");
	Helpimage= LoadGraph("Resource/Images/help3.png");
	isHelpDisplayed = false;

	cursor_number = 0;
	cursor_y = 200;  //カーソルの初期位置

	// BGM 読み込みと再生
	bgmHandle = LoadSoundMem("Resource/Sounds/オープニング.mp3");
	if (bgmHandle != -1)
	{
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ループ再生
		ChangeVolumeSoundMem(180, bgmHandle);
	}

	//カーソル移動SE
	cursorSE= LoadSoundMem("Resource/Sounds/カーソル移動8.mp3");
	if (cursorSE != -1) {
		ChangeVolumeSoundMem(250, cursorSE);
	}

	//決定ボタン
	kakutei= LoadSoundMem("Resource/Sounds/銃声6.mp3");
	if (kakutei != -1) {
		ChangeVolumeSoundMem(300, kakutei);
	}
}

eSceneType TitleScene::Update(float delta_second)
{
    InputControl* input = InputControl::GetInstance();

	// === Help画面表示中は Bボタン or スペースキー 以外を無視 ===
	if (isHelpDisplayed)
	{
		if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetPadButtonState(PAD_INPUT_B) == eInputState::ePress)
		{
			PlaySoundMem(kakutei, DX_PLAYTYPE_NORMAL);
			isHelpDisplayed = false; // ヘルプを閉じる
		}

		return eSceneType::eTitle; // 他の入力は無視
	}


    // 上入力（キーボード or コントローラー）
    if (input->GetKeyDown(KEY_INPUT_UP) || input->GetPadButtonState(PAD_INPUT_UP) == eInputState::ePress)
    {
        cursor_number--;
        if (cursor_number < 0)
            cursor_number = 2; // 上からループ
		PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK);
    }

    // 下入力（キーボード or コントローラー）
    if (input->GetKeyDown(KEY_INPUT_DOWN) || input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::ePress)
    {
        cursor_number++;
        cursor_number %= 3; // 下からループ
		PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK);
    }

    // 決定（スペース or Bボタン）
    if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetPadButtonState(PAD_INPUT_B) == eInputState::ePress)
    {
		PlaySoundMem(kakutei, DX_PLAYTYPE_NORMAL);

		if (isHelpDisplayed)
		{
			isHelpDisplayed = false; // ヘルプを閉じる
			return eSceneType::eTitle;
		}

		switch (cursor_number)
		{
		case 0: return eSceneType::eInGame;
		case 1:
			isHelpDisplayed = true; // ヘルプ表示
			break;
		case 2: return eSceneType::eEnd;
		}
	}


	//ゲームクリア画面　Test用
	if (input->GetKeyDown(KEY_INPUT_E))
	{
		return eSceneType::eResult2;
	}

    // カーソル位置更新
    cursor_y = 190 + cursor_number * 150;

    return GetNowSceneType();
}


void TitleScene::Draw() const
{

	// ヘルプが有効なら最上面に描画
	if (isHelpDisplayed)
	{
		DrawExtendGraph(0, 0, 1280, 720, Helpimage, TRUE);
		return;
	}

	if (titleImageHandle != -1)
	{
		DrawExtendGraph(0, 0, 1280, 720, titleImageHandle, TRUE);

		// カーソル描画
		DrawExtendGraph(1000, cursor_y, 900, cursor_y + 110, title_arrow, TRUE);
	}

	
}

void TitleScene::Finalize()
{
	if (titleImageHandle != -1)
	{
		DeleteGraph(titleImageHandle);
	}
	if (title_arrow != -1)
	{
		DeleteGraph(title_arrow);
	}

	DeleteGraph(Helpimage);

	//BGM終了処理
	if (bgmHandle != -1)
	{
		StopSoundMem(bgmHandle);
		DeleteSoundMem(bgmHandle);
	}
	DeleteSoundMem(cursorSE);
	DeleteSoundMem(kakutei);
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
