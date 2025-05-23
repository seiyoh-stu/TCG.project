#pragma once

#include "../../Object/Bullet/Bullet.h"
#include "../GameBase.h"

class Player : public GameBase
{
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

private:
    void Movement();
    void AnimeControl();

    int player_x;
    int player_y;
    int size_x;
    int size_y;
    unsigned int color;
    int hp;                      // プレイヤーのHP（初期値10）

    int flip_flag;
    bool scroll_end;
    bool scroll_start;

    int bullet_offset_x;
    int bullet_offset_y;

    int player_image;

    int last_shot_time;
    const int kShotIntervalMs = 500; // 500msで2発/秒
};