#pragma once
#include "../GameBase.h"
#include"../../Scene/GameMain/SceneManager.h"
class Castle : public GameBase
{
private:
    int hp; // �����l10
    bool hit;
    float damage_cooldown = 0.0f; // �N�[���^�C������
    const float DAMAGE_INTERVAL = 1.0f; // �_���[�W�Ԋu�i�b

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
    void SetScroll(float scroll , float& delta_second);

    int GetHp() const;
  
};

