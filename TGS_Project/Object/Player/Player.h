#pragma once

#include <vector>
#include "../../Object/Bullet/Bullet.h"
#include "../GameBase.h"

class Player : public GameBase
{
public:
    Player();
    ~Player();

    // GameBase �̉��z���\�b�h���I�[�o�[���C�h
    void Initialize() override;
    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    void OnHitCollision(GameBase* hit_object) override;

    // �v���C���[�ŗL�@�\
    void Shoot();  // �e�𐶐����鏈���i�����ŊǗ����X�g�ɓo�^����z��j

    // �e�̎擾�i�����蔻��ȂǂŎg�p�j
    const std::vector<Bullet>& GetBullets() const { return bullets; }

private:
    void Movement();
    void AnimeControl();

    int player_x;
    int player_y;
    int size_x;
    int size_y;
    unsigned int color;

    std::vector<Bullet> bullets; // �v���C���[�̒e�̃��X�g
    // ���ˈʒu�̃I�t�Z�b�g�i���ǉ������ϐ��j
    int bullet_offset_x;
    int bullet_offset_y;

    // ���ˊԊu�Ǘ��p
    int last_shot_time;
    const int kShotIntervalMs = 500; // 500ms��2��/�b
};
