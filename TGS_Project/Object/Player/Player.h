#pragma once

#include <vector>
#include "../../Object/Bullet/Bullet.h"

class Player {
public:
    Player();
    ~Player();

    void Initialize();
    void Update();
    void Draw();
    void Finalize();

    void Shoot();

    // 弾の取得（当たり判定などで使用）
    const std::vector<Bullet>& GetBullets() const { return bullets_; }

private:
    void Movement();
    void AnimeControl();

    int pos_x_;
    int pos_y_;
    int size_x_;
    int size_y_;
    unsigned int color_;

    std::vector<Bullet> bullets_; // プレイヤーの弾のリスト

    // 発射位置のオフセット
    int bullet_offset_x_;
    int bullet_offset_y_;

    // 発射間隔管理用
    int last_shot_time_;
    const int kShotIntervalMs_ = 500; // 500msで2発/秒
};
