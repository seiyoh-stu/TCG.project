#pragma once

#include <vector>
#include "../../Object/Bullet/Bullet.h"
#include "../GameBase.h"
#include "../../Utility/Vector2D.h"

class BulletAim : public GameBase
{
public:
    BulletAim();
    ~BulletAim();

    // GameBase �̉��z���\�b�h���I�[�o�[���C�h
    void Initialize() override;                                 // ������
    void Update(float delta_second) override;                   // �X�V
    void Draw(const Vector2D& screen_offset) const override;    // �`��
    void Finalize() override;                                   // �I������

private:
    void Movement(float delta_second);// �ړ�����
    void AnimeControl();              // �A�j���[�V��������

    // �����o�ϐ� 
    Vector2D location;   // Aim �̈ʒu
    int Aim_Image;       // Aim�摜
};