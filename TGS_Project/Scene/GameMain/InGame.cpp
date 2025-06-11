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
#include "../../Object/Bullet/BulletAim.h"
#include "../../Utility/ScoreManager.h"
#include "DxLib.h"
#include <memory>

InGame::InGame() : bgmHandle(-1) , flip_flag(false),
 bullet_magazine(5), push_flg(true),reload(0)
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
    player = gbmm->CreateGameBase<Player>(Vector2D(200, 580));
    castle = gbmm->CreateGameBase<Castle>(Vector2D(100, 580));
    bullet_aim = gbmm->CreateGameBase<BulletAim>(Vector2D(100, 580));

    enemy_spawn_timer = 0.0f;
    enemy_spawn_interval = 3.0f; // 3秒ごとに敵を出現

    //gbmm->CreateGameBase<Enemy>(Vector2D(1000, 500));
    //gbmm->CreateGameBase<Enemy2>(Vector2D(1500, 500));
    //gbmm->CreateGameBase<Enemy3>(Vector2D(2000, 500));
    //gbmm->CreateGameBase<Enemy4>(Vector2D(2500, 500));

    back_image = LoadGraph("Resource/Images/Ingame.png");
    scroll = 0;

    // BGMの読み込みと再生
    bgmHandle = LoadSoundMem("Resource/Sounds/InGameBGM.mp3");
    if (bgmHandle != -1)
    {
        PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ループ再生
    }

    score = ScoreManager::GetInstance();
    tarot = new Tarot();  // インスタンス化------追加0610
    tarot->SetPlayer(player);
}



//Update処理
eSceneType InGame::Update(float delta_second)
{
    InputControl* input = InputControl::GetInstance();

    // 全敵死亡なら次のwave開始準備へ
    if (wave_in_progress && enemy_list.empty())
    {
        InputControl* input = InputControl::GetInstance();

        if (input->GetKeyDown(KEY_INPUT_O))
        {
            wave_in_progress = false;  // 次のwaveを起動可能にーーーーーーーーーーー
        }
    }

    if (input->GetKeyDown(KEY_INPUT_SPACE))
        return eSceneType::eResult;

    //タロットシーン描画ーーーーーーーーーーーーーーーーーーーー
    if (input->GetKeyDown(KEY_INPUT_P))
    {
        return eSceneType::eTarot;
    }

    if (castle->GetHp() <= 0)
    {
        return eSceneType::eResult;
    }

    // 
    b = true;

	//リロード処理----------------
    if (input->GetKeyDown(KEY_INPUT_K))
    {
        a = true;
        bullet_magazine = 0;
    }
     
    if (a == true)
    {
        reload++;
        if (reload >= 150)
        {
            bullet_magazine = 5;
            a = false;
            reload = 0;
            
        }

    }
    //----------------------------

    // ばれっと生成
    if (input->GetKeyDown(KEY_INPUT_L) || input->GetPadButtonState(PAD_INPUT_6) == eInputState::ePress){

        if ((bullet_magazine > 0))
        {
            GameBaseManager* gbmm = GameBaseManager::GetInstance();
            Bullet* bullet;
            bullet = gbmm->CreateGameBase<Bullet>(player->GetLocation());
            bullet->SetBalletAim(bullet_aim);
            /*if (player->flip_flag == TRUE)
            {
                bullet->GetFlipFlag(TRUE);

            }
            else
            {
                bullet->GetFlipFlag(FALSE);
            }*/

            bullet_magazine--;//弾が減る

        }

    }

    // たまが0になった時に強制的にreload
    if (bullet_magazine <= 0)
    {
        
        if (reload >= 150)
        {
            bullet_magazine = 5;
            reload = 0;
        }
        reload++;
    }

    wave_timer += delta_second;

    if (!wave_in_progress && wave_timer >= wave_interval)
    {
        StartNextWave();
    }

    if (CheckHitKey(KEY_INPUT_B))
    {
        wave_in_progress = false;
    }

    enemy_list.erase(
        std::remove_if(enemy_list.begin(), enemy_list.end(),
            [](GameBase* e)
            {
                return e && e->IsDead();
            }),
        enemy_list.end()
    );

    GameBaseManager* gbmm = GameBaseManager::GetInstance();
    gbmm->Update(delta_second);


    ////--------スクロール処理--------------
    //float prev_scroll = scroll;

    //// 右にスクロール
    //if (player->GetLocation().x >= 640 && CheckHitKey(KEY_INPUT_D) || player->GetLocation().x >= 640 && input->GetPadButtonState(PAD_INPUT_9) == eInputState::eHeld)
    //{
    //    scroll += 5.0f;
    //    
    //}

    //// 左にスクロール
    //if (player->GetLocation().x < 250 && CheckHitKey(KEY_INPUT_A)|| player->GetLocation().x < 250 && input->GetPadButtonState(PAD_INPUT_9) == eInputState::eHeld)
    //{
    //    scroll -= 5.0f;
    //    
    //}

    //if (scroll < 0) 
    //{
    //    scroll = 0;  // 左壁
    //}
    //if (scroll >1200)
    //{
    //    scroll = 1200;  //右壁
    //} 

    //--------スクロール処理--------------
    float prev_scroll = scroll;



    // 左スティックの入力取得
    // VECTOR stick;
    // GetJoypadAnalogInput(&stick, 0);  // 左スティック
    float a = static_cast<float>(input->GetJoyStickLeft().x);
    // GetJoypadAnalogInput(&stick, 0);  // 左スティック
    const int DEAD_ZONE = 200;

    float stick_x = 0.0f;
    if (abs(a) > DEAD_ZONE) {
        stick_x = a / 1000.0f;  // -1.0f ～ 1.0f に正規化
    }

    // 右にスクロール（スティック or キーボード）
    if ((player->GetLocation().x >= 640 && CheckHitKey(KEY_INPUT_D)) ||
        (player->GetLocation().x >= 640 && stick_x > 0.2f))
    {
        scroll += 5.0f;
    }

    // 左にスクロール（スティック or キーボード）
    if ((player->GetLocation().x < 250 && CheckHitKey(KEY_INPUT_A)) ||
        (player->GetLocation().x < 250 && stick_x < -0.2f))
    {
        scroll -= 5.0f;
    }

    // スクロール制限
    if (scroll < 0)
    {
        scroll = 0;
    }
    if (scroll > 1200)
    {
        scroll = 1200;
    }

    // スクロール差分に応じて城の位置を調整
    float scroll_delta = scroll - prev_scroll;
    castle->SetScroll(scroll_delta, delta_second);

    

    return GetNowSceneType();
}




void InGame::Draw() const
{
   /* DrawRotaGraph(1280 - scroll, 480, 1.0, 0.0, back_image, TRUE);*/
    DrawRotaGraph(1180 - scroll, 100, 1.5, 0.0, back_image, TRUE);
    Vector2D screen_offset(scroll, 0);

    GameBaseManager::GetInstance()->DrawWithOffset(screen_offset);

    //城のHP描画
    DrawFormatString(10, 60, GetColor(255, 128, 128), "Castle HP: %d", castle->GetHP());

    //弾の残弾数表示
    DrawFormatString(10, 100, GetColor(255, 128, 128), "弾の残弾数: %d", bullet_magazine);
    if (bullet_magazine == 0)
    {
        // クールタイムの文
        DrawFormatString(10, 120, GetColor(255, 128, 128), "reloadnow");
    }


    //スコア表示
    if (score != nullptr) 
    {
        DrawFormatString(10, 80, GetColor(255, 128, 128), "Score: %d", score->GetScore());
    }

    //ウェーブ表示
    DrawFormatString(10, 140, GetColor(255, 255, 0), "Wave: %d", current_wave);
}




void InGame::SpawnEnemy()
{
    int random_e = GetRand(5);
    int random_f = GetRand(3);
    int random_x = GetRand(1);

    float X = (random_x == 0) ? 0.0f : 640.0f;
    bool flip = (random_x == 1);

    int random_y = GetRand(3);
    float Y_t = 170.0f + (float)(random_y * 80);
    float Y_b = 170.0f + (3 * 80);

    GameBaseManager* gbmm = GameBaseManager::GetInstance();

    int num = rand() % 100 + 1;

    if (num <= 100)
    {
        switch (random_e)
        {
        case 0: gbmm->CreateGameBase<Enemy>(Vector2D(100, Y_b)); break;
        case 1: gbmm->CreateGameBase<Enemy>(Vector2D(580, Y_b)); break;
        case 2: gbmm->CreateGameBase<Enemy2>(Vector2D(100, Y_t)); break;
        case 3: gbmm->CreateGameBase<Enemy2>(Vector2D(580, Y_t)); break;
        case 4: gbmm->CreateGameBase<Enemy3>(Vector2D(100, Y_b)); break;
        case 5: gbmm->CreateGameBase<Enemy3>(Vector2D(300, Y_b)); break;
        }
    }

    if (num <= 60)
    {
        switch (random_f)
        {
        case 0: gbmm->CreateGameBase<Enemy2>(Vector2D(100, Y_b)); break;
        case 1: gbmm->CreateGameBase<Enemy2>(Vector2D(580, Y_t)); break;
        case 2: gbmm->CreateGameBase<Enemy4>(Vector2D(100, Y_b)); break;
        case 3: gbmm->CreateGameBase<Enemy4>(Vector2D(580, Y_t)); break;
        }
    }
}




//ウェーブの1,2,3を切り替える関数
void InGame::StartNextWave()
{
    if (wave_in_progress == false)
    {
        defeated_enemies = 0;
        wave_timer = 0.0f;
        wave_in_progress = true;
        SpawnEnemiesForWave(current_wave);
        current_wave++;

        // ★ Tarotのチケットを加算し、プレイヤーを強化
        if (tarot != nullptr) {
            tarot->AddTicket();
            int level = tarot->GetTicket();
            player->Player_LevelUp(level);
            bullet_magazine = 5 + level;
        }

    }
}




//ウェーブ関数
void InGame::SpawnEnemiesForWave(int wave)
{
    GameBaseManager* gbmm = GameBaseManager::GetInstance();

    int num_enemies = 0;

    // Waveごとに敵の数を変える
    switch (wave)
    {
    case 1: num_enemies = 3; break;  // wave1: 敵2体
    case 2: num_enemies = 7; break;  // wave2: 敵4体
    case 3: num_enemies = 10; break;  // wave3: 敵8体
    default:
        num_enemies = 15; // wave4以降は固定で10体（例）
        break;
    }

    int e1 = GetRand(1000) + 500;  // 1500〜3000のランダムなX座標

    int e2 = GetRand(1000) + 500;  // 1500〜3000のランダムなX座標

    int e3 = GetRand(1000) + 500;  // 1500〜3000のランダムなX座標

    int e4 = GetRand(1000) + 500;  // 1500〜3000のランダムなX座標

    for (int i = 0; i < num_enemies; i++)
    {
        int enemy_type = GetRand(100);

        if (enemy_type < 40)
            enemy_list.push_back(gbmm->CreateGameBase<Enemy>(Vector2D(1260 + (i * e1), 580)));
        else if (enemy_type < 75)
            enemy_list.push_back(gbmm->CreateGameBase<Enemy2>(Vector2D(1260 + (i * e2), 580)));
        else if (enemy_type < 90)
            enemy_list.push_back(gbmm->CreateGameBase<Enemy3>(Vector2D(1260 + (i * e3), 300)));
        else
            enemy_list.push_back(gbmm->CreateGameBase<Enemy4>(Vector2D(1260 + (i * e4), 580)));
    }
}




void InGame::Finalize()
{
    if (bgmHandle != -1)
    {
        StopSoundMem(bgmHandle);
        DeleteSoundMem(bgmHandle);
    }

    GameBaseManager::GetInstance()->Finalize();
}




eSceneType InGame::GetNowSceneType() const
{
    return eSceneType::eInGame;
}