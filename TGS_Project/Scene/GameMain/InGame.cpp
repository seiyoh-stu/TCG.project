#include"InGame.h"
#include"../../Utility/InputControl.h"
#include "../../Utility/Vector2D.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Enemy/Enemy.h"
#include"../../Object/Enemy/Enemy2.h"
#include"../../Object/Enemy/Enemy3.h"
#include"../../Object/Enemy/Enemy4.h"
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
    gbmm->CreateGameBase<Enemy2>(Vector2D(1500, 500));            // 初期位置
    gbmm->CreateGameBase<Enemy3>(Vector2D(2000, 500));            // 初期位置
    gbmm->CreateGameBase<Enemy4>(Vector2D(2500, 500));            // 初期位置

	//バレットの照準マーク
    bullet_aim.Initialize();
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

    enemy_spawn_timer += delta_second;
    if (enemy_spawn_timer >= enemy_spawn_interval)
    {
        SpawnEnemy();
        enemy_spawn_timer = 0.0f;
    }

    wave_timer += delta_second;

    if (!wave_in_progress && wave_timer >= wave_interval)
    {
        StartNextWave(); // 新しいウェーブを開始
        wave_timer = 0.0f;
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

    bullet_aim.Update(delta_second);

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
   bullet_aim.Draw(screen_offset);

}

void InGame::SpawnEnemy()
{
    int random_e = GetRand(5); // 0〜5の範囲
    int random_f = GetRand(3); // 0〜3の範囲
    int random_x = GetRand(1); // 0か1

    float X = (random_x == 0) ? 0.0f : 640.0f;
    bool flip = (random_x == 1);

    int random_y = GetRand(3);
    float Y_t = 170.0f + (float)(random_y * 80);
    float Y_b = 170.0f + (3 * 80); // 一番下の行

    GameBaseManager* gbmm = GameBaseManager::GetInstance();

    int num = rand() % 100 + 1;

    if (num <= 100)
    {
        switch (random_e)
        {
        case 0:
            gbmm->CreateGameBase<Enemy>(Vector2D(100, Y_b));
            break;
        case 1:
            gbmm->CreateGameBase<Enemy>(Vector2D(500, Y_b));
            break;
        case 2:
            gbmm->CreateGameBase<Enemy2>(Vector2D(100, Y_t));
            break;
        case 3:
            gbmm->CreateGameBase<Enemy2>(Vector2D(500, Y_t));
            break;
        case 4:
            gbmm->CreateGameBase<Enemy3>(Vector2D(100, Y_b));
            break;
        case 5:
            gbmm->CreateGameBase<Enemy3>(Vector2D(500, Y_b));
            break;
        }
    }

    if (num <= 60)
    {
        switch (random_f)
        {
        case 0:
            gbmm->CreateGameBase<Enemy2>(Vector2D(100, Y_b));
            break;
        case 1:
            gbmm->CreateGameBase<Enemy2>(Vector2D(500, Y_t));
            break;
        case 2:
            gbmm->CreateGameBase<Enemy4>(Vector2D(100, Y_b));
            break;
        case 3:
            gbmm->CreateGameBase<Enemy4>(Vector2D(500, Y_t));
            break;
        }
    }
}

void InGame::StartNextWave()
{
    wave_in_progress = true;
    SpawnEnemiesForWave(current_wave);
    current_wave++;
}

void InGame::SpawnEnemiesForWave(int wave)
{
    GameBaseManager* gbmm = GameBaseManager::GetInstance();

    int num_enemies = 2 + wave; // ウェーブごとに増加
    for (int i = 0; i < num_enemies; ++i)
    {
        int enemy_type = GetRand(100);
        Vector2D spawn_pos(GetRand(640), 170 + (GetRand(3) * 80)); // 画面上の適当な位置にスポーン

        if (enemy_type < 40)
        {
            gbmm->CreateGameBase<Enemy>(spawn_pos); // 弱い敵
        }
        else if (enemy_type < 75)
        {
            gbmm->CreateGameBase<Enemy2>(spawn_pos); // 中程度の敵
        }
        else if (enemy_type < 90)
        {
            gbmm->CreateGameBase<Enemy3>(spawn_pos); // 強い敵
        }
        else
        {
            gbmm->CreateGameBase<Enemy4>(spawn_pos); // レア・ボス敵
        }
    }

    wave_in_progress = false;
}

void InGame::Finalize()
{
    /*player->Finalize();

    enemy->Finalize();*/
    // 入力制御インスタンスの取得
    GameBaseManager* gbmm = GameBaseManager::GetInstance();
    gbmm->Finalize();

    bullet_aim.Finalize();

}

eSceneType InGame::GetNowSceneType() const
{
    return eSceneType::eInGame;
}