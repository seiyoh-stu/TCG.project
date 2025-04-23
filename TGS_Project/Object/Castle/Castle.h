#pragma once
#include "../GameBase.h"
class Castle : public GameBase
{


public:
	Castle();
	~Castle();
    // GameBase の仮想メソッドをオーバーライド
    void Initialize() override;
    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    //void OnHitCollision(GameBase* hit_object) override;
  
};

