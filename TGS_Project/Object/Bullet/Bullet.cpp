#include "Bullet.h"
#include "DxLib.h"
#include "../../Object/GameObjectManager.h"
#include "../../Utility/ResourceManager.h"

//������
Bullet::Bullet()
    : speed_(10), is_active_(false)
{
    location.x = 0;
    location.y = 0;
}

void Bullet::Initialize()
{
    // �f�t�H���g�̏������i�g�p���Ȃ��ꍇ�͍폜�j
    Initialize(location, 0, false);
}

void Bullet::Initialize(const Vector2D& start, const Vector2D& target,bool flip_flag)
{
    ResourceManager* rm = ResourceManager::GetInstance();

    // �ʏ�e
    bullet_image = LoadGraph("Resource/Images/tama.png");

    //�����A�j���\�V����
    std::vector<int> explosion_imgs = rm->GetImages("Resource/Images/haretu.png", 4, 4, 1, 72, 72);
    for (int i = 0; i < 4; ++i)
        explosion_frames[i] = explosion_imgs[i];

    is_exploding = false;
    explosion_index = 0;
    explosion_count = 0;

    location = start;
    target_ = target;           // �� ��Ŏg�����ߕۑ�
    speed_ = 10.0f;
    is_active_ = true;
    is_shot = false;            // �� ����t���[���ɂ��������v�Z���s������

    collision.object_type = eBullet;
    collision.box_size = 10;
    collision.hit_object_type.push_back(eEnemy);
}

void Bullet::Update(float delta_second)
{

    if (is_exploding)
    {
        AnimeControl();
        if (explosion_index >= 4) {
            GameBaseManager::GetInstance()->DestroyGameBase(this);
        }
        return;
    }


    if (!is_active_) return;

    if (!is_shot && bulletaim!= nullptr)
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
    /*AnimeControl();*/
    //GetFlipFlag(1);
    /*location.x += speed_;*/

}

void Bullet::Draw(const Vector2D& screen_offset) const
{


    //if (!is_active_) return;

    //int draw_x = location.x /*- screen_offset.x*/;      // ��p�ā@�i�o���b�g���X�N���[���ł����Ă���j
    //int draw_y = location.y /*- screen_offset.y*/;

   /* DrawBox(
        draw_x - collision.box_size.x,
        draw_y - collision.box_size.y,
        draw_x + collision.box_size.x,
        draw_y + collision.box_size.y,
        GetColor(255, 255, 0), TRUE
    );*/

    
    if (!is_active_ && !is_exploding) return;

    int draw_x = location.x;
    int draw_y = location.y;

    if (is_exploding)
    {
        DrawExtendGraph(
            draw_x - 150, draw_y - 150,   // ������W�i�摜�T�C�Y�ɉ����Ē����j
            draw_x + 150, draw_y + 150,   // �E�����W�i����72�~72�Ȃ�2�{�j
            explosion_frames[explosion_index],
            TRUE
        );
    }
    else
    {
        DrawRotaGraph(
            draw_x,                 // ���SX
            draw_y,                 // ���SY
            0.35f,                   // �g�嗦�i�K�v�Ȃ� 0.5f �Ȃǁj
            0.0f,                   // ��]�Ȃ�
            bullet_image,           // �e�摜
            TRUE                    // ���߂���
        );
    }
}

void Bullet::Finalize()
{
    // �K�v������Ή������
}

void Bullet::OnHitCollision(GameBase* hit_object)
{
    if (hit_object->GetCollision().object_type == eEnemy)
    {
        
        if (!is_exploding) 
        {
            is_exploding = true;
            is_active_ = false;
            explosion_index = 0;
            explosion_count = 0;
        }
       /* GameBaseManager::GetInstance()->DestroyGameBase(this);*/
    }
}

bool Bullet::IsActive() const
{
    return is_active_;
}

void Bullet::GetFlipFlag(bool flag)
{
   
}

void Bullet::SetBalletAim(BulletAim* Aim)
{
    bulletaim = Aim;
}



void Bullet::AnimeControl()
{
    explosion_count++;

    if (explosion_count >= 4)
    {
        explosion_count = 0;
        explosion_index++;
    }
}

