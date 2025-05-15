#include "Castle.h"
#include "DxLib.h"
#include "../../Object/Enemy/Enemy.h"

Castle::Castle()
{

}

Castle::~Castle()
{

}

void Castle::Initialize()
{
    // �ʒu�A�����蔻��ȂǏ����l��ݒ�i�K�v�ɉ����Ē����j
    location = { 100, 300 };
    z_layer = 1;
    is_mobility = false;
    filp_flag = false;
    hit_flag = false;

    hp = 10; // ������
    // �T�C�Y�ⓖ���蔻��Ȃǂ��K�v�ɉ����Ă����Őݒ肷��
}

void Castle::Draw(const Vector2D& screen_offset) const
{
    Vector2D draw_pos = location - screen_offset;

    const int width = 200;
    const int height = 500;
    unsigned int color = GetColor(255, 0, 0); // �ԐF

    DrawBox(draw_pos.x, draw_pos.y, draw_pos.x + width, draw_pos.y + height, color, TRUE);
}

void Castle::Update(float delta_second) 
{ 
}

void Castle::Finalize()
{

}

void Castle::OnHitCollision(GameBase* hit_object)
{
     //�G���ǂ������f�������Ȃ�iEnemy �N���X������ꍇ�j
    if (dynamic_cast<Enemy*>(hit_object)) {
        hp--;
    }

   // ���ׂĂ̓�������Ƃ肠�����u�G����̍U���v�Ɖ��肷��ꍇ�F
    if (hp > 0) {
        hp--;
        printf("Castle HP: %d\n", hp); // �R���\�[����HP�\��
    }
}
