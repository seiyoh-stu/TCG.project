#include"Result.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"

Result::Result()
{

}

Result::~Result()
{

}

void Result::Initialize()
{

}

eSceneType Result::Update(float delta_second)
{
	//入力機能の取得
	InputControl* input = InputControl::GetInstance();

	//SPACEキーで院ゲーム画面に移動する
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eEnd;
	}

	return GetNowSceneType();
}
void Result::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "リザルト画面です");
}

void Result::Finalize()
{

}

eSceneType Result::GetNowSceneType() const
{
	return eSceneType::eResult;
}
