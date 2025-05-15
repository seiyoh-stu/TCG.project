#pragma once
#include "../GameBase.h"
class Castle : public GameBase
{
private:
    int hp = 10; // 初期値10

public:
	Castle();
	~Castle();
    // GameBase の仮想メソッドをオーバーライド
    void Initialize() override;
    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    void OnHitCollision(GameBase* hit_object) override;
    int GetHP() const { return hp; }
  
};

