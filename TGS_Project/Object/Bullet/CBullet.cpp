#include "CBullet.h"
#include "DxLib.h"
#include "../../Object/GameObjectManager.h"

//������
CBullet::CBullet()
    : speed_(10), is_active_(false)
{
    location.x = 0;
    location.y = 0;
}

void CBullet::Initialize()
{
    // �f�t�H���g�̏������i�g�p���Ȃ��ꍇ�͍폜�j
    Initialize(location, 0, false);

    // �ʏ�e
    bullet_image = LoadGraph("Resource/Images/tama.png");
}

void CBullet::Initialize(const Vector2D& start, const Vector2D& target, bool flip_flag)
{
    /*location.x = start_x;
    location.y = start_y;*/
    //location = start;
    //Vector2D diff = target - start;

    //// ���K��
    //float length = sqrt(diff.x * diff.x + diff.y * diff.y);
    //if (length != 0)
    //{
    //    direction_.x = diff.x / length;
    //    direction_.y = diff.y / length;
    //}
    location = start;
    target_ = target;           // �� ��Ŏg�����ߕۑ�
    speed_ = 10.0f;
    is_active_ = true;
    is_shot = false;            // �� ����t���[���ɂ��������v�Z���s������

    collision.object_type = eBullet;
    collision.box_size = 16;
    collision.hit_object_type.push_back(eEnemy);
}

void CBullet::Update(float delta_second)
{
    //if (bulletaim != nullptr && is_shot == false)
    //{
    //    Vector2D diff = bulletaim->GetLocation() - location;

    //    // ���K��
    //    float length = sqrt(diff.x * diff.x + diff.y * diff.y);
    //    if (length != 0)
    //    {
    //        direction_.x = diff.x / length;
    //        direction_.y = diff.y / length;
    //    }
    //    is_shot = true;

    //}
    if (!is_active_) return;

    if (!is_shot && bulletaim != nullptr)
    {
        Vector2D diff = bulletaim->GetLocation() - location;
        float length = sqrt(diff.x * diff.x + diff.y * diff.y);
        if (length != 0)
        {
            direction_.x = diff.x / length;
            direction_.y = diff.y / length;
        }
        else
        {
            direction_ = { 0, -1 }; // �f�t�H���g�����F��
        }

        is_shot = true;
    }


    location.x += direction_.x * speed_;
    location.y += direction_.y * speed_;

    if (location.x > 4000 || location.x < 0 || location.y < 0 || location.y > 3000) {
        is_active_ = false;
        GameBaseManager::GetInstance()->DestroyGameBase(this);
    }

    //GetFlipFlag(1);
    /*location.x += speed_;*/

}

void CBullet::Draw(const Vector2D& screen_offset) const
{
    if (!is_active_) return;

    int draw_x = location.x /*- screen_offset.x*/;      // ��p�ā@�i�o���b�g���X�N���[���ł����Ă���j
    int draw_y = location.y /*- screen_offset.y*/;

   /* DrawBox(
        draw_x - collision.box_size.x,
        draw_y - collision.box_size.y,
        draw_x + collision.box_size.x,
        draw_y + collision.box_size.y,
        GetColor(255, 255, 0), TRUE
    );*/

    DrawRotaGraph(
        draw_x,                 // ���SX
        draw_y,                 // ���SY
        0.35f,                   // �g�嗦�i�K�v�Ȃ� 0.5f �Ȃǁj
        0.0f,                   // ��]�Ȃ�
        bullet_image,           // �e�摜
        TRUE                    // ���߂���
    );
}

void CBullet::Finalize()
{
    // �K�v������Ή������
}

void CBullet::OnHitCollision(GameBase* hit_object)
{
    if (hit_object->GetCollision().object_type == eEnemy)
    {
        GameBaseManager::GetInstance()->DestroyGameBase(this);
    }
}

bool CBullet::IsActive() const
{
    return is_active_;
}

void CBullet::GetFlipFlag(bool flag)
{
    /*if (flag==TRUE)
    {
        speed_ = -10;
    }
    else
    {
        speed_ = 10;
    }*/
}

void CBullet::SetBalletAim(BulletAim* Aim)
{
    bulletaim = Aim;
}
