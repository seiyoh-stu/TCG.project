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

    // スクロール管理
    bool scroll_end;
    bool scroll_start;



    // 弾の発射位置オフセット
    int bullet_offset_x;
    int bullet_offset_y;




    // プレイヤー画像およびアニメーション管理
    int player_image;           //プレイヤー画像
    int walk_animation[10];     // 歩行アニメーション
    int idle_animation[11];     // 待機アニメーション
    int walk_index;             // 歩行フレームインデックス
    int idle_index;             // 待機フレームインデックス
    int animation_count;        //アニメーション時間



     // 弾発射管理
    int last_shot_time;
    const int kShotIntervalMs = 500; // 500msで2発/秒



    //プレイヤーレベルアップ変数ーーーー追加0610
    int power_level = 1;
    int bullet_damage = 10;



public:

    bool flip_flag;// 左右反転フラグ


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