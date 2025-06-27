#include "Help.h"
#include "../../../Utility/InputControl.h"
#include "DxLib.h"

Help::Help()
{

}

Help::~Help()
{
}

void Help::Initialize()
{
    help_Image = LoadGraph("Resource/Images/Help(2).PNG");
}

eSceneType Help::Update(float delta_second)
{
    // 入力制御インスタンスの取得
    InputControl* input = InputControl::GetInstance();

    // SPACEキーが押されたら終了シーンへ遷移
    if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetPadButtonState(PAD_INPUT_B) == eInputState::ePress)
    {
        return eSceneType::eTitle;
    }

    return GetNowSceneType();
}

void Help::Draw() const
{
    DrawFormatString(10, 10, GetColor(255, 255, 255), "ヘルプ画面です(Bで戻る)");
    DrawExtendGraph(0, 0, 1280, 720, help_Image, TRUE);
}

void Help::Finalize()
{
    if(help_Image != -1)
    {
        DeleteGraph(help_Image);
    }

}

eSceneType Help::GetNowSceneType() const
{
    return eSceneType::eHelp;
}
