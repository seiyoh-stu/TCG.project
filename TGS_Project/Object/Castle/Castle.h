#pragma once
#include "../GameBase.h"
class Castle : public GameBase
{
private:
    int hp = 10; // �����l10

public:
	Castle();
	~Castle();
    // GameBase �̉��z���\�b�h���I�[�o�[���C�h
    void Initialize() override;
    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    void OnHitCollision(GameBase* hit_object) override;
    int GetHP() const { return hp; }
  
};

