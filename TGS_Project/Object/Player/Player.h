#pragma once

#include "../../Object/Bullet/Bullet.h"
#include "../GameBase.h"

class Player : public GameBase
{
private:
    int player_x;
    int player_y;
    int size_x;
    int size_y;
    unsigned int color;
    int hp;                      // プレイヤーのHP（初期値10）

    bool scroll_end;
    bool scroll_start;

    int bullet_offset_x;
    int bullet_offset_y;

    int player_image;//プレイヤー画像
    int animation[10];  //アニメーション画像
    int animation_index = 0;  // 現在のフレーム番号
    int animation_count;//アニメーション時間

    int last_shot_time;
    const int kShotIntervalMs = 500; // 500msで2発/秒

    //プレイヤーレベルアップ変数ーーーー追加0610
    int power_level = 1;
    int bullet_damage = 10;


public:
    bool flip_flag;//反転


public:
    Player();
    ~Player();

    // GameBase の仮想メソッドをオーバーライド
    void Initialize() override;
    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    void OnHitCollision(GameBase* hit_object) override;

    void Shoot();  // 弾を発射する処理

    void DecreaseHP(int amount);  // HP減少関数
    int GetHP() const;            // HP取得関数
    Vector2D& GetLocation();

    //プレイヤーレベルアップ関数ーーーーーーー0610
    void Player_LevelUp(int levelup);
    int Get_Level() const { return power_level; }
    int GetBulletDamage() const { return bullet_damage; }


private:
    void Movement();
    void AnimeControl();
};