#pragma once

#include <vector>
#include "../../Object/Bullet/Bullet.h"

class Player {
public:
    Player();
    ~Player();

    void Initialize();
    void Update();
    void Draw();
    void Finalize();

    void Shoot();

    // �e�̎擾�i�����蔻��ȂǂŎg�p�j
    const std::vector<Bullet>& GetBullets() const { return bullets_; }

private:
    void Movement();
    void AnimeControl();

    int pos_x_;
    int pos_y_;
    int size_x_;
    int size_y_;
    unsigned int color_;

    std::vector<Bullet> bullets_; // �v���C���[�̒e�̃��X�g

    // ���ˈʒu�̃I�t�Z�b�g
    int bullet_offset_x_;
    int bullet_offset_y_;

    // ���ˊԊu�Ǘ��p
    int last_shot_time_;
    const int kShotIntervalMs_ = 500; // 500ms��2��/�b
};
