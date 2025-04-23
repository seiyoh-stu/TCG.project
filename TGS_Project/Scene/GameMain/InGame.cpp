#include"InGame.h"
#include"../../Utility/InputControl.h"
#include "../../Utility/Vector2D.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Enemy/Enemy.h"
#include"DxLib.h"
#include <memory>

InGame::InGame() :
    player(std::make_unique<Player>()), // コンストラクタで Player のインスタンスを生成
    enemy(std::make_unique<Enemy>()) // コンストラクタで Enemy のインスタンスを生成
{

}

InGame::~InGame()
{
    // std::unique_ptr は自動的に管理してくれるため、delete は不要
}

void InGame::Initialize()
{
    player->Initialize();
    enemy->Initialize();
}

eSceneType InGame::Update(float delta_second)
{
    // 入力制御インスタンスの取得
    InputControl* input = InputControl::GetInstance();

    // SPACEキーが押されたらリザルトシーンへ遷移
    if (input->GetKeyDown(KEY_INPUT_SPACE))
    {
        return eSceneType::eResult;
    }

    player->Update(delta_second);
    
    enemy->Update(delta_second);

    return GetNowSceneType();
}
void InGame::Draw() const  
{  
   Vector2D screen_offset(0, 0); // スクリーンオフセットを初期化  
   DrawFormatString(10, 10, GetColor(255, 255, 255), "Bottun.Sで球発射");  
   player->Draw(screen_offset); // 必要な引数を渡す  
   enemy->Draw(screen_offset);  
}

void InGame::Finalize()
{
    player->Finalize();

    enemy->Finalize();
}

eSceneType InGame::GetNowSceneType() const
{
    return eSceneType::eInGame;
}