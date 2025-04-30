#include"Help.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"

Help::Help()
{

}

Help::~Help()
{

}

void Help::Initialize()
{

}

eSceneType Help::Update(float delta_second)
{
	// 入力制御インスタンスの取得
	InputControl* input = InputControl::GetInstance();

	// SPACEキーが押されたら終了シーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eTitle;
	}

	return GetNowSceneType();
}
void Help::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "ヘルプ画面です");
}

void Help::Finalize()
{

}

eSceneType Help::GetNowSceneType() const
{
	return eSceneType::eHelp;
}