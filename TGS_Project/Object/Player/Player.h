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

    // �X�N���[���Ǘ�
    bool scroll_end;
    bool scroll_start;



    // �e�̔��ˈʒu�I�t�Z�b�g
    int bullet_offset_x;
    int bullet_offset_y;




    // �v���C���[�摜����уA�j���[�V�����Ǘ�
    int player_image;           //�v���C���[�摜
    int walk_animation[10];     // ���s�A�j���[�V����
    int idle_animation[11];     // �ҋ@�A�j���[�V����
    int walk_index;             // ���s�t���[���C���f�b�N�X
    int idle_index;             // �ҋ@�t���[���C���f�b�N�X
    int animation_count;        //�A�j���[�V��������



     // �e���ˊǗ�
    int last_shot_time;
    const int kShotIntervalMs = 500; // 500ms��2��/�b



    //�v���C���[���x���A�b�v�ϐ��[�[�[�[�ǉ�0610
    int power_level = 1;
    int bullet_damage = 10;



public:

    bool flip_flag;// ���E���]�t���O


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