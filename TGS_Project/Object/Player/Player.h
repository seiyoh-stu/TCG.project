#pragma once

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

    void Shoot();  // �e�𔭎˂��鏈��

    void DecreaseHP(int amount);  // HP�����֐�
    int GetHP() const;            // HP�擾�֐�
    Vector2D& GetLocation();

private:
    void Movement();
    void AnimeControl();

    int player_x;
    int player_y;
    int size_x;
    int size_y;
    unsigned int color;
    int hp;                      // �v���C���[��HP�i�����l10�j

    int flip_flag;
    bool scroll_end;
    bool scroll_start;

    int bullet_offset_x;
    int bullet_offset_y;

    int player_image;

    int last_shot_time;
    const int kShotIntervalMs = 500; // 500ms��2��/�b
};