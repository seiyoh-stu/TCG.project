#pragma once

#include "../../Object/Bullet/Bullet.h"
#include "../GameBase.h"

class Player : public GameBase
{
private:
    int player_x;
    int player_y;
    int size_x;
    int size_y;
    unsigned int color;
    int hp;                      // �v���C���[��HP�i�����l10�j

    bool scroll_end;
    bool scroll_start;

    int bullet_offset_x;
    int bullet_offset_y;

    int player_image;//�v���C���[�摜
    int animation[10];  //�A�j���[�V�����摜
    int animation_index = 0;  // ���݂̃t���[���ԍ�
    int animation_count;//�A�j���[�V��������

    int last_shot_time;
    const int kShotIntervalMs = 500; // 500ms��2��/�b

    //�v���C���[���x���A�b�v�ϐ��[�[�[�[�ǉ�0610
    int power_level = 1;
    int bullet_damage = 10;


public:
    bool flip_flag;//���]


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

    //�v���C���[���x���A�b�v�֐��[�[�[�[�[�[�[0610
    void Player_LevelUp(int levelup);
    int Get_Level() const { return power_level; }
    int GetBulletDamage() const { return bullet_damage; }


private:
    void Movement();
    void AnimeControl();
};