﻿#pragma once

#include "SceneBase.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Castle/Castle.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Object/Enemy/Enemy2.h"
#include "../../Object/Enemy/Enemy3.h"
#include "../../Object/Enemy/Enemy4.h"
#include"../../Object/Bullet/BulletAim.h"
#include "../../Utility/ScoreManager.h"
#include "../../Utility/Vector2D.h"
#include "../GameSub/TarotScene/TarotScene.h"

#include <memory> // std::unique_ptr を使用するため

class InGame : public SceneBase
{
private:
    Player* player;
    BulletAim* bullet_aim;
    Castle* castle;


    ScoreManager* score;
    //std::unique_ptr<Player> player; // Playerクラスのインスタンスをスマートポインタで管理
    //// 他のプライベートメンバ変数
    //std::unique_ptr<Enemy> enemy; // Enemyクラスのインスタンスをスマートポインタで管理


    //音源
    int bgmHandle;//BGM
    int bullet_Sound;//銃声
    int Reload_Sound;//リロード


    //画像
    int back_image;

    int bullet_Frame;
    int reload_image;
    int dansuu_image;
   /* int ticket_image;*/


    bool flip_flag; // 画面反転フラぐ
    int bullet_magazine;
    int reload;
    bool push_flg;

    bool cbullet_shot = false;

    bool a;

    bool b;


    std::vector<GameBase*> enemy_list;
    int defeated_enemies = 0;

    float enemy_spawn_timer = 0.0f;
    float enemy_spawn_interval = 3.0f; // 3秒ごとにスポーン
    void SpawnEnemy(); // ランダム敵生成用関数

    int current_wave =0;
    float wave_timer = 0.0f;
    float wave_interval = 1.0f; // 10秒ごとに次のウェーブ
    bool wave_in_progress = false;

    void StartNextWave();
    void SpawnEnemiesForWave(int wave);
    void DrawWithOffset(Vector2D& offset);

    

public:

    float  scroll = 0.0f;
   
  
    float bullet_cooldown_timer = 0.0f;
    const float bullet_cooldown_interval = 0.1f;  // 0.3秒間隔

public:
    InGame();
    virtual ~InGame();

    // 初期化処理
    virtual void Initialize() override;

    // 更新処理
    // 戻り値: 次のシーンタイプ
    virtual eSceneType Update(float delta_second) override;

    // 描画処理
    virtual void Draw() const override;

    // 終了処理
    virtual void Finalize() override;

    // 現在のシーンタイプを取得
    virtual eSceneType GetNowSceneType() const override;

    //// Playerクラスのインスタンスへのアクセス (必要であれば)
    //Player* GetPlayer() const { return player.get(); }

    //// Playerクラスのインスタンスへのアクセス (必要であれば)
    //Enemy* GetEnemy() const { return enemy.get(); }
};