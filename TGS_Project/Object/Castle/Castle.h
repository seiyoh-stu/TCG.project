#pragma once
#include "../GameBase.h"
#include"../../Scene/GameMain/SceneManager.h"
#include <unordered_map>

class Castle : public GameBase
{
private:
    int hp; // �����l10
    bool hit;
    float damage_cooldown = 0.0f; // �N�[���^�C������
    const float DAMAGE_INTERVAL = 1.0f; // �_���[�W�Ԋu�i�b
    const int DAMAGE_AMOUNT = 10;       // 1��̃_���[�W��

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
    // GameBase �̉��z���\�b�h���I�[�o�[���C�h
    void Initialize() override;
    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    void OnHitCollision(GameBase* hit_object) override;
    int GetHP() const { return hp; }
    void SetScroll(float scroll , float& delta_second);

    /*int castle_graph;*/

    

    int GetHp() const;
    void AddHp(int add); // �ǉ�

    std::unordered_map<GameBase*, float> enemy_cooldowns;
  
};

