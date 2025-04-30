#include "TitleScene.h"
#include "DxLib.h"
#include"../../../Utility/InputControl.h"

TitleScene::TitleScene() : titleImageHandle(-1), title_arrow(-1)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	titleImageHandle = LoadGraph("Resource/Images/Title2.png");
	title_arrow = LoadGraph("Resource/Images/AimMark.png");

	cursor_number = 0;
	cursor_y = 200;  //カーソルの初期位置
}

eSceneType TitleScene::Update(float delta_second)
{
    InputControl* input = InputControl::GetInstance();

    // 上入力（キーボード or コントローラー）
    if (input->GetKeyDown(KEY_INPUT_UP) || input->GetPadButtonState(PAD_INPUT_UP) == eInputState::ePress)
    {
        cursor_number--;
        if (cursor_number < 0)
            cursor_number = 2; // 上からループ
    }

    // 下入力（キーボード or コントローラー）
    if (input->GetKeyDown(KEY_INPUT_DOWN) || input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::ePress)
    {
        cursor_number++;
        cursor_number %= 3; // 下からループ
    }

    // 決定（スペース or Bボタン）
    if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetPadButtonState(PAD_INPUT_2) == eInputState::ePress)
    {
        switch (cursor_number)
        {
        case 0: return eSceneType::eInGame;
        case 1: return eSceneType::eHelp;
        case 2: return eSceneType::eEnd;
        }
    }

    // カーソル位置更新
    cursor_y = 190 + cursor_number * 150;

    return GetNowSceneType();
}


void TitleScene::Draw() const
{

	if (titleImageHandle != -1)
	{
		DrawExtendGraph(0, 0, 1280, 720, titleImageHandle, TRUE);

		// カーソル描画（x=100は仮、必要に応じて調整）
		DrawExtendGraph(1000, cursor_y, 900, cursor_y + 110, title_arrow, TRUE);
	}
	int pad = GetJoypadInputState(DX_INPUT_PAD1);

	if (pad & PAD_INPUT_1) DrawFormatString(100, 100, GetColor(255, 255, 255), "PAD_INPUT_1");
	if (pad & PAD_INPUT_2) DrawFormatString(100, 120, GetColor(255, 255, 255), "PAD_INPUT_2");
	if (pad & PAD_INPUT_3) DrawFormatString(100, 140, GetColor(255, 255, 255), "PAD_INPUT_3");
	if (pad & PAD_INPUT_4) DrawFormatString(100, 160, GetColor(255, 255, 255), "PAD_INPUT_4");
	if (pad & PAD_INPUT_DOWN) DrawFormatString(100, 180, GetColor(255, 0, 0), "PAD_INPUT_DOWN");
	if (pad & PAD_INPUT_UP) DrawFormatString(100, 180, GetColor(255, 0, 0), "PAD_INPUT_UP");
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
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
