#pragma once
#include "../GameBase.h"

class Bullet : public GameBase
{
public:
    Bullet(); // デフォルトコンストラクタ
    void Initialize() override;
    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    bool IsActive() const;
    int GetX() const { return x_; }
    int GetY() const { return y_; }
    void Deactivate() { is_active_ = false; }
    void OnHitCollision(GameBase* hit_object) override;


private:
    int x_;
    int y_;
    int speed_;
    bool is_active_;
};
