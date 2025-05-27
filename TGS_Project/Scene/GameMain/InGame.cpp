#include "InGame.h"
#include "../../Utility/InputControl.h"
#include "../../Utility/Vector2D.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Castle/Castle.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Object/Enemy/Enemy2.h"
#include "../../Object/Enemy/Enemy3.h"
#include "../../Object/Enemy/Enemy4.h"
#include "../../Object/GameObjectManager.h"
#include "DxLib.h"
#include <memory>

InGame::InGame() : bgmHandle(-1)
{
}

InGame::~InGame()
{

}

void InGame::Initialize()
{

    // 500〜1000の乱数を生成（GetRand は 0〜N の乱数を返す）(DxLibのランダム関数)
    int randomNumber = GetRand(1500);  // 0〜1500 の値
    randomNumber += 1500;              // → 1500〜3000 に調整(1500以上から出現するようになる)

    int randomNumber2 = GetRand(1500);  // 0〜1500 の値
    randomNumber2 += 1500;              // → 1500〜3000 に調整(1500以上から出現するようになる)

    int randomNumber3 = GetRand(1500);  // 0〜1500 の値
    randomNumber3 += 1500;              // → 1500〜3000 に調整(1500以上から出現するようになる)

    int randomNumber4 = GetRand(1500);  // 0〜1500 の値
    randomNumber4 += 1500;              // → 1500〜3000 に調整(1500以上から出現するようになる)

    int e_randomNumber = GetRand(3);  // 3 の値

    int e_randomNumber2 = GetRand(3);  // 0〜1 の値

    int e_randomNumber3 = GetRand(3);  // 0〜1 の値

    int e_randomNumber4 = GetRand(1);  // 0〜1 の値

    GameBaseManager* gbmm = GameBaseManager::GetInstance();
    if (player == nullptr) {
        player = gbmm->CreateGameBase<Player>(Vector2D(200, 500));
    }
    castle = gbmm->CreateGameBase<Castle>(Vector2D(100, 500));

    /*gbmm->CreateGameBase<Enemy>(Vector2D(1000, 500));
    gbmm->CreateGameBase<Enemy2>(Vector2D(1500, 500));
    gbmm->CreateGameBase<Enemy3>(Vector2D(2000, 500));
    gbmm->CreateGameBase<Enemy4>(Vector2D(2500, 500));*/

    enemy_spawn_timer = 0.0f;
    enemy_spawn_interval = 3.0f; // 3秒ごとに敵を出現


    back_image = LoadGraph("Resource/Images/Title2.png");
    scroll = 0;

    // BGMの読み込みと再生
    bgmHandle = LoadSoundMem("Resource/Sounds/InGameBGM.mp3");
    if (bgmHandle != -1)
    {
        PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ループ再生
    }
}

eSceneType InGame::Update(float delta_second)
{
    InputControl* input = InputControl::GetInstance();

    if (input->GetKeyDown(KEY_INPUT_SPACE))
        return eSceneType::eResult;

    if (input->GetKeyDown(KEY_INPUT_L)) {
        GameBaseManager* gbmm = GameBaseManager::GetInstance();
        gbmm->CreateGameBase<Bullet>(player->GetLocation());
    }

    /*enemy_spawn_timer += delta_second;
    if (enemy_spawn_timer >= enemy_spawn_interval) {
        SpawnEnemy();
        enemy_spawn_timer = 0.0f;
    }*/

    wave_timer += delta_second;
    if (wave_timer >= wave_interval) {
        StartNextWave();
        wave_timer = 0.0f;
    }

    GameBaseManager* gbmm = GameBaseManager::GetInstance();
    gbmm->Update(delta_second);


    //--------スクロール処理--------------
    float prev_scroll = scroll;
    if (player->GetLocation().x >= 640)
    {
        scroll = player->GetLocation().x - 640;

        float scroll_delta = scroll - prev_scroll;
        castle->SetScroll(scroll_delta, delta_second);

        if (scroll < 0) scroll = 0;
    }
    else
    {
        scroll = 0;
    }

    return GetNowSceneType();
}

void InGame::Draw() const
{
    DrawRotaGraph(1280 - scroll, 480, 2.0, 0.0, back_image, TRUE);
    Vector2D screen_offset(scroll, 0);

    GameBaseManager::GetInstance()->DrawWithOffset(screen_offset);

    // 入力制御インスタンスの取得
    GameBaseManager* gbmm = GameBaseManager::GetInstance();
    gbmm->Draw();

    if (player != nullptr)
        DrawFormatString(10, 40, GetColor(255, 255, 0), "Player HP: %d", player->GetHP());

    DrawFormatString(10, 60, GetColor(255, 128, 128), "Castle HP: %d", castle->GetHP());
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
        case 0: gbmm->CreateGameBase<Enemy>(Vector2D(100, Y_b))->SetPlayer(player); break;
        case 1: gbmm->CreateGameBase<Enemy>(Vector2D(500, Y_b))->SetPlayer(player); break;
        case 2: gbmm->CreateGameBase<Enemy2>(Vector2D(100, Y_t)); break;
        case 3: gbmm->CreateGameBase<Enemy2>(Vector2D(500, Y_t)); break;
        case 4: gbmm->CreateGameBase<Enemy3>(Vector2D(100, Y_b)); break;
        case 5: gbmm->CreateGameBase<Enemy3>(Vector2D(500, Y_b)); break;
        }
    }

    if (num <= 60)
    {
        switch (random_f)
        {
        case 0: gbmm->CreateGameBase<Enemy2>(Vector2D(100, Y_b)); break;
        case 1: gbmm->CreateGameBase<Enemy2>(Vector2D(500, Y_t)); break;
        case 2: gbmm->CreateGameBase<Enemy4>(Vector2D(100, Y_b)); break;
        case 3: gbmm->CreateGameBase<Enemy4>(Vector2D(500, Y_t)); break;
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
    /*int num_enemies = 2 + wave;
    for (int i = 0; i < num_enemies; ++i)
    {
        int enemy_type = GetRand(100);
        Vector2D spawn_pos(GetRand(640), 170 + (GetRand(3) * 80));

        if (enemy_type < 40) gbmm->CreateGameBase<Enemy>(spawn_pos);
        else if (enemy_type < 75) gbmm->CreateGameBase<Enemy2>(spawn_pos);
        else if (enemy_type < 90) gbmm->CreateGameBase<Enemy3>(spawn_pos);
        else gbmm->CreateGameBase<Enemy4>(spawn_pos);
    }*/

    int enemy_type = GetRand(100);
    Vector2D spawn_pos(1500, 500); // 画面上の適当な位置にスポーン

    if (enemy_type < 25) //(25パーセント)
    {
        gbmm->CreateGameBase<Enemy>(spawn_pos)->SetPlayer(player); // 弱い敵
    }
    else if (enemy_type < 50) //(25パーセント)
    {
        gbmm->CreateGameBase<Enemy2>(spawn_pos); // 中程度の敵
    }
    else if (enemy_type < 75) //(25パーセント)
    {
        gbmm->CreateGameBase<Enemy3>(spawn_pos); // 強い敵
    }
    else //(残りの25パーセント)
    {
        gbmm->CreateGameBase<Enemy4>(spawn_pos); // レア・ボス敵
    }

    wave_in_progress = false;
}

void InGame::Finalize()
{
    if (bgmHandle != -1)
    {
        StopSoundMem(bgmHandle);
        DeleteSoundMem(bgmHandle);
    }

    // 入力制御インスタンスの取得
    GameBaseManager* gbmm = GameBaseManager::GetInstance();
    gbmm->Finalize();

    GameBaseManager::GetInstance()->Finalize();
}

eSceneType InGame::GetNowSceneType() const
{
    return eSceneType::eInGame;
}