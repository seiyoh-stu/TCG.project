#include "Castle.h"
#include "DxLib.h"
#include "../../Object/Enemy/Enemy.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include <unordered_map>
#include <memory>

//#define MAX_HP 500

Castle::Castle()
{

}

Castle::~Castle()
{

}

void Castle::Initialize()
{
    castle_graph = LoadGraph("Resource/Images/tetugousi.png");

    

    // �ʒu�A�����蔻��ȂǏ����l��ݒ�i�K�v�ɉ����Ē����j
    location = { 50, 250 };
    z_layer = 1;
    is_mobility = false;
    filp_flag = false;
    hit_flag = false;
    hit = false;

    collision.object_type = eCastle;
    collision.hit_object_type.push_back(eEnemy);

    damage_cooldown = 1.0f;

    collision.box_size = { 64, 400 };  // ��128px, ����128px


    hp = 500;// ������

    // �T�C�Y�ⓖ���蔻��Ȃǂ��K�v�ɉ����Ă����Őݒ肷��
}

void Castle::Draw(const Vector2D& screen_offset) const
{
    Vector2D offset = { -200, -450 }; // �摜�̈ʒu�����p�I�t�Z�b�g
    Vector2D draw_pos = location - screen_offset + offset;

    if (castle_graph != -1)
    {
        DrawExtendGraph(
            draw_pos.x,
            draw_pos.y,
            draw_pos.x + 300,   // ��128�s�N�Z���ɒ����i��j
            draw_pos.y + 600,   // ����400�s�N�Z���ɒ����i��j
            castle_graph,
            TRUE);
    }

    //// �X�N���[���̉e�����󂯂Ȃ��`��ʒu�i��F��ʂ̍����ɌŒ�j
    //Vector2D fixed_screen_pos = { -200, -450 }; // ��ʏ�̕\�����W�𒼐ڎw��

    //if (castle_graph != -1)
    //{
    //    DrawExtendGraph(
    //        fixed_screen_pos.x,
    //        fixed_screen_pos.y,
    //        fixed_screen_pos.x + 300,  // ��
    //        fixed_screen_pos.y + 600,  // ����
    //        castle_graph,
    //        TRUE);
    //}

    // �� �f�o�b�O�p�̓����蔻��\���i�K�v�Ȃ�j
    // DrawBox(
    //     draw_pos.x - collision.box_size.x,
    //     draw_pos.y - collision.box_size.y,
    //     draw_pos.x + collision.box_size.x,
    //     draw_pos.y + collision.box_size.y,
    //     GetColor(255, 0, 255), TRUE
    // );



    //Vector2D draw_pos = location - screen_offset;

    //const int width = 200;
    //const int height = 500;
    //unsigned int color = GetColor(255, 0, 0); // �ԐF

    //DrawBox(draw_pos.x, draw_pos.y, draw_pos.x + width, draw_pos.y + height, color, TRUE);

    //int draw_x = location.x - screen_offset.x;
    //int draw_y = location.y - screen_offset.y;
        //DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
    /*DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, GetColor(255,0,255), TRUE);*/

    /*DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y,
        location.x + collision.box_size.x, location.y + collision.box_size.y,
        GetColor(255, 0, 255), TRUE);*/


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
    // �e�G�̃N�[���_�E�����Ԃ�i�߂�
    for (auto& pair : enemy_cooldowns)
    {
        pair.second += delta_second;
    }
    // �N�[���_�E����i�߂�
    if (damage_cooldown < DAMAGE_INTERVAL)
    {
        damage_cooldown += delta_second;
    }
}

void Castle::Finalize()
{

}

void Castle::OnHitCollision(GameBase* hit_object)
{

    if (hit_object->GetCollision().object_type == eEnemy)
    {
        float& cooldown = enemy_cooldowns[hit_object];  // �G���Ƃ̃N�[���_�E��

        const float DAMAGE_INTERVAL = 1.0f; // �b�P�ʂł̃_���[�W�Ԋu�i�C�Ӂj

        if (cooldown >= DAMAGE_INTERVAL)
        {
            hp -= hit_object->GetAttackPower();
            cooldown = 0.0f;

            printf("Castle HP: %d\n", hp);

            if (hp <= 0)
            {
                is_dead_ = true;
                GameBaseManager::GetInstance()->DestroyGameBase(this);
            }
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

void Castle::AddHp(int add)
{
    hp += add;
    printf("Castle HP: %d\n", hp);
}
