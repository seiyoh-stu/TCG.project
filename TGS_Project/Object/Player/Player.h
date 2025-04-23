#pragma once

#include <vector>
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

    // プレイヤー固有機能
    void Shoot();  // 弾を生成する処理（内部で管理リストに登録する想定）

    // 弾の取得（当たり判定などで使用）
    const std::vector<Bullet>& GetBullets() const { return bullets; }

private:
    void Movement();
    void AnimeControl();

    int player_x;
    int player_y;
    int size_x;
    int size_y;
    unsigned int color;

    std::vector<Bullet> bullets; // プレイヤーの弾のリスト
    // 発射位置のオフセット（←追加した変数）
    int bullet_offset_x;
    int bullet_offset_y;

    // 発射間隔管理用
    int last_shot_time;
    const int kShotIntervalMs = 500; // 500msで2発/秒
};
