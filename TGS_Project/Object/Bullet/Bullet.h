#pragma once
#include "../GameBase.h"
#include "../../Object/Player/Player.h"
#include "BulletAim.h"

class Bullet : public GameBase
{
public:
    Bullet(); // デフォルトコンストラクタ
    void Initialize() override; // 使用しないなら削除してもOK
    //void Initialize(int start_x, int start_y,bool flip_flag); // ★ 位置指定付き初期化

    // ★ 新しい初期化：任意方向に撃てる
    void Initialize(const Vector2D& start_pos, const Vector2D& target_pos, bool flip_flag);

    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    void OnHitCollision(GameBase* hit_object) override;

    bool IsActive() const;
    int GetX() const { return location.x; }
    int GetY() const { return location.y; }
    void Deactivate() { is_active_ = false; }

    void GetFlipFlag(bool flag);

    void SetBalletAim(class BulletAim* Aim);

    BulletAim* bulletaim;

    Vector2D direction_;   // 単位ベクトル（進行方向）
    Vector2D target_;      // 弾のターゲット位置（BulletAimなど）
    bool is_shot = false;  // 初回方向計算フラグ

private:

    int speed_;
    bool is_active_;
    bool move_left_;  // ← 追加、左向きかどうか

    //Player* player;
};

