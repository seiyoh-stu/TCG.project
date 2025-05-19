#pragma once
#include "../GameBase.h"

class Bullet : public GameBase
{
public:
    Bullet(); // デフォルトコンストラクタ
    void Initialize() override; // 使用しないなら削除してもOK
    void Initialize(int start_x, int start_y); // ★ 位置指定付き初期化
    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    void OnHitCollision(GameBase* hit_object) override;

    bool IsActive() const;
    int GetX() const { return location.x; }
    int GetY() const { return location.y; }
    void Deactivate() { is_active_ = false; }

private:
    int speed_;
    bool is_active_;
};

