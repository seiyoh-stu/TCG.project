#include "Castle.h"
#include "DxLib.h"
#include "../../Object/Enemy/Enemy.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"

#define MAX_HP 10  // 6�Ȃ�3���Ŏ���

Castle::Castle()
{

}

Castle::~Castle()
{

}

void Castle::Initialize()
{
    // �ʒu�A�����蔻��ȂǏ����l��ݒ�i�K�v�ɉ����Ē����j
    location = { 50, 300 };
    z_layer = 1;
    is_mobility = false;
    filp_flag = false;
    hit_flag = false;
    hit = false;

    collision.box_size = 64;


    hp = MAX_HP;; // ������
    // �T�C�Y�ⓖ���蔻��Ȃǂ��K�v�ɉ����Ă����Őݒ肷��
}

void Castle::Draw(const Vector2D& screen_offset) const
{
    //Vector2D draw_pos = location - screen_offset;

    //const int width = 200;
    //const int height = 500;
    //unsigned int color = GetColor(255, 0, 0); // �ԐF

    //DrawBox(draw_pos.x, draw_pos.y, draw_pos.x + width, draw_pos.y + height, color, TRUE);

    //int draw_x = location.x - screen_offset.x;
    //int draw_y = location.y - screen_offset.y;
        //DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
    DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, GetColor(255,0,255), TRUE);

    //DrawBox
    //(
    //    draw_x - collision.box_size.x,
    //    draw_y - collision.box_size.y,
    //    draw_x + collision.box_size.x,
    //    draw_y + collision.box_size.y,
    //    GetColor(255,0,255), TRUE
    //);
}

void Castle::Update(float delta_second) 
{ 
    if (hit == true)
    { 
        damage_cooldown += delta_second;

        if (damage_cooldown == 1.0f)
        {
            hit = false;
        }
    }
}

void Castle::Finalize()
{

}

void Castle::OnHitCollision(GameBase* hit_object)
{

    if (hit_object->GetCollision().object_type == eEnemy)
    {
        // HP�����炷
        hp--;

        //// �X�R�A���Z�i���������u�Ԃ̂݁j
        //ScoreManager* score = ScoreManager::GetInstance();
        //score->AddScore(100); // �e1���ɂ�100�_�i�K�v�ɉ����Ē����j

        // HP��0�ȉ��Ȃ�I�u�W�F�N�g���폜
        if (hp <= 0)
        {
            is_dead_ = true;

            GameBaseManager* gbmm = GameBaseManager::GetInstance();
            gbmm->DestroyGameBase(this);
        }
    }

    //if (damage_cooldown <= 0.0f && hp > 0)
    //{
    //    hp--; // HP��1���炷
    //    hit = true;
    //    //damage_cooldown = DAMAGE_INTERVAL; // �_���[�W���󂯂���N�[���^�C���J�n
    //    printf("Castle HP: %d\n", hp);
    //}
}

void Castle::SetScroll(float scroll, float& delta_second)
{
    location.x -= scroll;
}

int Castle::GetHp() const
{
    return hp;
}