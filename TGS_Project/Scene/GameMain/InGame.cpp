﻿#include "InGame.h"
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

extern Tarot* g_sharedTarot;//ーーーーーーーー追加0610

InGame::InGame() : bgmHandle(-1) ,bullet_Sound(-1) ,flip_flag(false),
 bullet_magazine(20), push_flg(true),reload(0)
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

    if (player != nullptr && bullet_aim != nullptr)
    {
        player->SetBulletAim(bullet_aim);
    }

    enemy_spawn_timer = 0.0f;
    enemy_spawn_interval = 3.0f; // 3秒ごとに敵を出現

    //gbmm->CreateGameBase<Enemy>(Vector2D(1000, 500));
    //gbmm->CreateGameBase<Enemy2>(Vector2D(1500, 500));
    //gbmm->CreateGameBase<Enemy3>(Vector2D(2000, 500));
    //gbmm->CreateGameBase<Enemy4>(Vector2D(2500, 500));

    back_image = LoadGraph("Resource/Images/Ingame.png");
    bullet_Frame = LoadGraph("Resource/Images/Frame1-preview.png");
    reload_image= LoadGraph("Resource/Images/reload.png");
    dansuu_image= LoadGraph("Resource/Images/Magazine.png");


    scroll = 0;

    // BGMの読み込みと再生
    bgmHandle = LoadSoundMem("Resource/Sounds/InGameBGM.mp3");
    if (bgmHandle != -1)
    {
        PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ループ再生
    }

    //バレット発射SE
    bullet_Sound= LoadSoundMem("Resource/Sounds/銃声6.mp3");
    ChangeVolumeSoundMem(150, bullet_Sound);
    //リロードSE
    Reload_Sound= LoadSoundMem("Resource/Sounds/リロード.mp3");
    ChangeVolumeSoundMem(200, Reload_Sound);



    score = ScoreManager::GetInstance();
 
    g_sharedTarot->SetPlayer(player);

    ticket = 0;
}



//Update処理
eSceneType InGame::Update(float delta_second)
{
    InputControl* input = InputControl::GetInstance();


//プレイヤーが強化しているように見せる処理ーーーーーーーーーーー
    if (InputControl::GetInstance()->GetKey(KEY_INPUT_1))
    {
        for (int i = 0; i < enemy_list.size(); i++)
        {
            // 生成されているかチェックして大丈夫だったらダメージをブースト
            if (enemy_list[i] != nullptr && enemy_list[i]->is_dead_ != true)
            {
                if (ticket > 0)
                {
                    enemy_list[i]->SetDamageBoost(1);
                    ticket--;
                }
                
            }
        }
    }

    if (input->GetKeyDown(KEY_INPUT_2))
    {
        if (ticket > 0)
        {
            bullet_magazine = 40;
            ticket--;
        }
        
    }

    if (input->GetKeyDown(KEY_INPUT_3))
    {
        if (ticket > 0)
        {
            castle->AddHp(100);
            ticket--;
        }
        
    }

   
    // Update()の中、キー入力判定で追加
// 4キーが押されたらサブショットモードON
    if (input->GetKeyDown(KEY_INPUT_4)) 
    {
        if (ticket > 0)
        {
            cbullet_shot = true;
        }
        
    }



    // 敵が全滅した時間を記録するための変数（外部 or static 変数として宣言）
    static int enemy_clear_time = -1;

    // 全敵死亡なら次のwave開始準備へ
    if (wave_in_progress && enemy_list.empty())
    {
        InputControl* input = InputControl::GetInstance();

        // 敵が全滅した時刻を初回のみ記録
        if (enemy_clear_time == -1)
        {
            enemy_clear_time = GetNowCount();  // 現在のミリ秒を取得
        }

        // Oキーが押された、または5秒（5000ミリ秒）経過したら次のwaveへ
        if (input->GetKeyDown(KEY_INPUT_O) || GetNowCount() - enemy_clear_time >= 10000)
        {
            wave_in_progress = false;  // 次のwaveを起動可能に
            enemy_clear_time = -1;     // リセットして次のwaveに備える
        }
    }
    else
    {
        // 敵がまだいる、またはwaveが進行中でないならリセット
        enemy_clear_time = -1;
    }

    if (input->GetKeyDown(KEY_INPUT_SPACE))
        return eSceneType::eResult;

    ////タロットシーン描画ーーーーーーーーーーーーーーーーーーーー
    //if (input->GetKeyDown(KEY_INPUT_P))
    //{
    //    return eSceneType::eTarot;
    //}

    if (castle->GetHp() <= 0)
    {
        return eSceneType::eResult;
    }

    // 
    b = true;

	//リロード処理----------------
    if (input->GetKeyDown(KEY_INPUT_K) || input->GetPadButtonState(PAD_INPUT_3) == eInputState::ePress)
    {
        a = true;
        bullet_magazine = 0;

        PlaySoundMem(Reload_Sound, DX_PLAYTYPE_BACK);
    }
     


    if (a == true)
    {
        reload++;
        if (reload >= 150)
        {
            bullet_magazine = 20;
            a = false;
            reload = 0;
            PlaySoundMem(Reload_Sound, DX_PLAYTYPE_BACK);
        }

    }
    //----------------------------

    // ばれっと生成
    if ((input->GetKeyDown(KEY_INPUT_L) || input->GetPadButtonState(PAD_INPUT_6) == eInputState::eHeld)
        && bullet_magazine > 0 && bullet_cooldown_timer >= bullet_cooldown_interval)
    {
        GameBaseManager* gbmm = GameBaseManager::GetInstance();

        // プレイヤー用の弾発射
        Bullet* bullet = gbmm->CreateGameBase<Bullet>(Vector2D(player->GetLocation().x, player->GetLocation().y + 50));
        bullet->SetBalletAim(bullet_aim);

        // サブショットモードがONならCBulletも同時発射
        if (cbullet_shot) {
            CBullet* cbullet = gbmm->CreateGameBase<CBullet>(Vector2D(castle->GetLocation().x, castle->GetLocation().y + 50));
            cbullet->SetBalletAim(bullet_aim);
        }

        bullet_magazine--;
        bullet_cooldown_timer = 0.0f;


        PlaySoundMem(bullet_Sound, DX_PLAYTYPE_BACK);
    }
    // タイマー加算
    bullet_cooldown_timer += delta_second;

    // たまが0になった時に強制的にreload
    if (bullet_magazine <= 0)
    {
        
        if (reload >= 150)
        {
            bullet_magazine = 20;
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

    //--------スクロール処理--------------
    float prev_scroll = scroll;



    // 左スティックの入力取得
    // VECTOR stick;
    // GetJoypadAnalogInput(&stick, 0);  // 左スティック
    float sc = static_cast<float>(input->GetJoyStickLeft().x);
    // GetJoypadAnalogInput(&stick, 0);  // 左スティック
    const int DEAD_ZONE = 200;

    float stick_x = 0.0f;
    if (abs(sc) > DEAD_ZONE) {
        stick_x = sc / 1000.0f;  // -1.0f ～ 1.0f に正規化
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

    for (int i = 0; i < enemy_list.size(); i++)
    {
        // 生成されているかチェックして大丈夫だったらダメージをブースト
        if (enemy_list[i] != nullptr)
        {
            enemy_list[i]->SetEScroll(scroll_delta);
        }
    }


    return GetNowSceneType();
}




void InGame::Draw() const
{
    DrawRotaGraph(1180 - scroll, 100, 1.5, 0.0, back_image, TRUE);

    Vector2D screen_offset(scroll, 0);

    GameBaseManager::GetInstance()->DrawWithOffset(screen_offset);

    //城のHP描画
    DrawFormatString(10, 60, GetColor(255, 255, 255), "Castle HP: %d", castle->GetHP());


    DrawGraph(870, 500, bullet_Frame, TRUE);


    //弾の残弾数表示
    //DrawFormatString(1100, 660, GetColor(255, 255, 255), "弾の残弾数: %d", bullet_magazine);
    //if (bullet_magazine == 0)
    //{
    //    // クールタイムの文
    //    DrawFormatString(1100, 660, GetColor(255, 50, 0), "リロード");
    //}

    if (a == true)  // リロード中かどうかのフラグ
    {
        DrawFormatString(1125, 670, GetColor(255, 255, 255), "リロード");
        DrawRotaGraph(1050, 675, 0.1, 0.0,reload_image, TRUE);
    }
    else
    {
        DrawFormatString(1115, 670, GetColor(255, 255, 255), "弾の残弾数: %d", bullet_magazine);
        DrawRotaGraph(1050, 675, 0.1, 0.0, dansuu_image, TRUE);
    }


    //スコア表示
    if (score != nullptr) 
    {
        DrawFormatString(10, 80, GetColor(255, 255, 255), "Score: %d", score->GetScore());
    }

    //ウェーブ表示
    DrawFormatString(10, 140, GetColor(255, 200, 0), "Wave: %d", current_wave);
    DrawFormatString(10, 160, GetColor(255, 200, 0), "Power_Up_Ticket: %d", ticket);

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
        case 0: enemy_list.push_back(gbmm->CreateGameBase<Enemy>(Vector2D(100, Y_b))); break;
        case 1: enemy_list.push_back(gbmm->CreateGameBase<Enemy>(Vector2D(580, Y_b))); break;
        case 2: enemy_list.push_back(gbmm->CreateGameBase<Enemy2>(Vector2D(100, Y_t)));  break;
        case 3: enemy_list.push_back(gbmm->CreateGameBase<Enemy2>(Vector2D(580, Y_t)));  break;
        case 4: enemy_list.push_back(gbmm->CreateGameBase<Enemy3>(Vector2D(100, Y_b))); break;
        case 5: enemy_list.push_back(gbmm->CreateGameBase<Enemy3>(Vector2D(300, Y_b)));  break;
        }
    }

    if (num <= 60)
    {
        switch (random_f)
        {
        case 0: enemy_list.push_back(gbmm->CreateGameBase<Enemy2>(Vector2D(100, Y_b))); break;
        case 1: enemy_list.push_back(gbmm->CreateGameBase<Enemy2>(Vector2D(580, Y_t))); break;
        case 2: enemy_list.push_back(gbmm->CreateGameBase<Enemy4>(Vector2D(100, Y_b))); break;
        case 3: enemy_list.push_back(gbmm->CreateGameBase<Enemy4>(Vector2D(580, Y_t))); break;
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
        ticket++;
        g_sharedTarot->SetTicket(ticket);

        //// ★ Tarotのチケットを加算し、プレイヤーを強化
        //if (tarot != nullptr) {
        //    tarot->AddTicket();
        //    int level = tarot->GetTicket();
        //    player->Player_LevelUp(level);
        //    bullet_magazine = 5 + level;
        //}

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
    case 0: num_enemies = 0; break;
    case 1: num_enemies = 1; break;  
    case 2: num_enemies = 5; break;  
    case 3: num_enemies = 10; break; 
    case 4: num_enemies = 15; break;
    case 5: num_enemies = 20; break;
    case 6: num_enemies = 25; break;
    default:
        num_enemies = 30; // wave4以降は固定で10体（例）
        break;
    }

    int e1 = GetRand(900) + 300;  // 1500〜3000のランダムなX座標

    int e2 = GetRand(900) + 300;  // 1500〜3000のランダムなX座標

    int e3 = GetRand(900) + 300;  // 1500〜3000のランダムなX座標

    int e4 = GetRand(900) + 300;  // 1500〜3000のランダムなX座標

    for (int i = 0; i < num_enemies; i++)
    {
        int enemy_type = GetRand(100);

        int randY = GetRand(200) + 450;  // Y座標を300〜500の範囲にランダム化

        int randY2 = GetRand(100) + 200;  // Y座標を300〜500の範囲にランダム化

        if (enemy_type < 40)
            enemy_list.push_back(gbmm->CreateGameBase<Enemy>(Vector2D(1260 + (i * e1), randY)));
        else if (enemy_type < 75)
            enemy_list.push_back(gbmm->CreateGameBase<Enemy2>(Vector2D(1260 + (i * e2), randY)));
        else if (enemy_type < 90)
            enemy_list.push_back(gbmm->CreateGameBase<Enemy3>(Vector2D(1260 + (i * e3), randY2)));
        else
            enemy_list.push_back(gbmm->CreateGameBase<Enemy4>(Vector2D(1260 + (i * e4), randY)));
    }
}




void InGame::Finalize()
{
    if (bgmHandle != -1)
    {
        StopSoundMem(bgmHandle);
        DeleteSoundMem(bgmHandle);
    }
    
    DeleteSoundMem(bullet_Sound);
    DeleteSoundMem(Reload_Sound);

    GameBaseManager::GetInstance()->Finalize();
}




eSceneType InGame::GetNowSceneType() const
{
    return eSceneType::eInGame;
}