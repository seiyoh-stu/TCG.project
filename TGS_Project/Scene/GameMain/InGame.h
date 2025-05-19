#pragma once

#include "SceneBase.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Castle/Castle.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Object/Enemy/Enemy2.h"
#include "../../Object/Enemy/Enemy3.h"
#include "../../Object/Enemy/Enemy4.h"
#include "../../Utility/Vector2D.h"
#include <memory> // std::unique_ptr を使用するため

class InGame : public SceneBase
{
private:
    Player* player;
    Castle* castle;
    //std::unique_ptr<Player> player; // Playerクラスのインスタンスをスマートポインタで管理
    //// 他のプライベートメンバ変数
    //std::unique_ptr<Enemy> enemy; // Enemyクラスのインスタンスをスマートポインタで管理

    float enemy_spawn_timer = 0.0f;
    float enemy_spawn_interval = 3.0f; // 3秒ごとにスポーン
    void SpawnEnemy(); // ランダム敵生成用関数

    int current_wave = 1;
    float wave_timer = 0.0f;
    float wave_interval = 10.0f; // 10秒ごとに次のウェーブ
    bool wave_in_progress = false;

    void StartNextWave();
    void SpawnEnemiesForWave(int wave);
    void DrawWithOffset(Vector2D& offset);

public:

    int  scroll = 0.0f;
   

    int back_image;

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