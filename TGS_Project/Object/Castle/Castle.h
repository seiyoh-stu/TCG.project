#pragma once
#include "../GameBase.h"
#include"../../Scene/GameMain/SceneManager.h"
#include <unordered_map>

class Castle : public GameBase
{
private:
    int hp; // 初期値10
    bool hit;
    float damage_cooldown = 0.0f; // クールタイム時間
    const float DAMAGE_INTERVAL = 1.0f; // ダメージ間隔（秒
    const int DAMAGE_AMOUNT = 10;       // 1回のダメージ量

    int castle_graph = -1;

    int damage_sound_handle = -1;

    int dead_sound_handle = -1;

    bool pending_destroy = false;
    float destroy_timer = 0.0f;

    bool pending_finalize = false;
    float finalize_timer = 0.0f;
    

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

    /*int castle_graph;*/

    

    int GetHp() const;
    void AddHp(int add); // 追加

    std::unordered_map<GameBase*, float> enemy_cooldowns;
  
};

