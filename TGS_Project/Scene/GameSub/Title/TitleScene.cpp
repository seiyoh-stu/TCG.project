#include"TitleScene.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"
#include"Time.h"

TitleScene::TitleScene() : titleImageHandle(-1)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	titleImageHandle = LoadGraph("Resource/Images/TowerDiffenceImage.png");
}

eSceneType TitleScene::Update()
{

	// 入力制御インスタンスの取得
	InputControl* input = InputControl::GetInstance();

	// SPACEキーが押されたら次のシーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eInGame;
	}

	return GetNowSceneType();
}
void TitleScene::Draw() const
{
	//DrawFormatString(10, 10, GetColor(255, 255, 255), "Title");
	
	if (titleImageHandle != -1)
	{
		DrawGraph(0, 0, titleImageHandle, TRUE);
	}
}

void TitleScene::Finalize()
{
	if (titleImageHandle != -1)
	{
		DeleteGraph(titleImageHandle); // メモリ開放
	}
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}