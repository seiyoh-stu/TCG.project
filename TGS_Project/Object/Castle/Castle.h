#pragma once
#include "../GameBase.h"
#include"../../Scene/GameMain/SceneManager.h"
class Castle : public GameBase
{
private:
    int hp; // 初期値10
    bool hit;
    float damage_cooldown = 0.0f; // クールタイム時間
    const float DAMAGE_INTERVAL = 1.0f; // ダメージ間隔（秒

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
    void SetScroll(float scroll , float& delta_second);

    int GetHp() const;
  
};

