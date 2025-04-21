#include"End.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"

End::End()
{

}

End::~End()
{

}

void End::Initialize()
{

}

eSceneType End::Update()
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
void End::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "エンド画面です");
}

void End::Finalize()
{

}

eSceneType End::GetNowSceneType() const
{
	return eSceneType::eInGame;
}
