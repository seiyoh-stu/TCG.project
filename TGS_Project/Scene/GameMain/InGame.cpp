#include"InGame.h"
#include"../../Utility/InputControl.h"
#include "../../Utility/Vector2D.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Enemy/Enemy.h"
#include"../../Object/GameObjectManager.h"
#include"DxLib.h"
#include <memory>

InGame::InGame() 
    //player(std::make_unique<Player>()), // コンストラクタで Player のインスタンスを生成
    //enemy(std::make_unique<Enemy>()) // コンストラクタで Enemy のインスタンスを生成
{

}

InGame::~InGame()
{
    // std::unique_ptr は自動的に管理してくれるため、delete は不要
}

void InGame::Initialize()
{
    // 入力制御インスタンスの取得
    GameBaseManager * gbmm = GameBaseManager::GetInstance();
    player=gbmm->CreateGameBase<Player>(Vector2D(200,500));
    gbmm->CreateGameBase<Enemy>(Vector2D(1000,500));            // 初期位置

    //player->Initialize();
    //enemy->Initialize();
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
    // SPACEキーが押されたらリザルトシーンへ遷移
    if (input->GetKeyDown(KEY_INPUT_S))
    {
        GameBaseManager* gbmm = GameBaseManager::GetInstance();
        gbmm->CreateGameBase<Bullet>(player->GetLocation());
    }

        // 入力制御インスタンスの取得
    GameBaseManager* gbmm = GameBaseManager::GetInstance();
    gbmm->Update(delta_second);
    //player->Update(delta_second);
    //
    //enemy->Update(delta_second);


    //Collision* col = new Collision();
    //bool check_collision;

    //check_collision = col->IsCheckHitCollision(player->GetCollision(), enemy->GetCollision());

    //if (check_collision == true)
    //{
    //    player->OnHitCollision(enemy.get());
    //    enemy->OnHitCollision(player.get());
    //}

    return GetNowSceneType();
}
void InGame::Draw() const  
{  
   Vector2D screen_offset(0, 0); // スクリーンオフセットを初期化  
   DrawFormatString(10, 10, GetColor(255, 255, 255), "Bottun.Sで球発射");  
   //player->Draw(screen_offset); // 必要な引数を渡す  
   //enemy->Draw(screen_offset);  
           // 入力制御インスタンスの取得
   GameBaseManager* gbmm = GameBaseManager::GetInstance();
   gbmm->Draw();

   if (player != nullptr) 
   {
       DrawFormatString(10, 40, GetColor(255, 255, 0), "Player HP: %d", player->GetHP());
   }

}

void InGame::Finalize()
{
    /*player->Finalize();

    enemy->Finalize();*/
    // 入力制御インスタンスの取得
    GameBaseManager* gbmm = GameBaseManager::GetInstance();
    gbmm->Finalize();

}

eSceneType InGame::GetNowSceneType() const
{
    return eSceneType::eInGame;
}