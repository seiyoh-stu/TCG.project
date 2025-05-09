#include "Bullet.h"
#include "DxLib.h"
#include"../../Object/GameObjectManager.h"


Bullet::Bullet()
    : x_(0), y_(0), speed_(5), is_active_(false)
{
}

void Bullet::Initialize()
{
    collision.object_type = eBullet;
    collision.box_size = 16;
    collision.hit_object_type.push_back(eEnemy);
}

void Bullet::Update(float delta_second)
{
    //if (!is_active_) return;

    location.x += speed_; // è„ï˚å¸Ç…à⁄ìÆ
    if (location.y < 0) is_active_ = false;
}

void Bullet::Draw(const Vector2D& screen_offset) const
{
    //if (!is_active_) return;

    DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, GetColor(255, 255, 0), TRUE);
}

void Bullet::Finalize()
{

}

void Bullet::OnHitCollision(GameBase* hit_object)
{
    if (hit_object->GetCollision().object_type == eEnemy)
    {
        GameBaseManager* gbmm = GameBaseManager::GetInstance();
        gbmm->DestroyGameBase(this);
    }
}

bool Bullet::IsActive() const
{
    return is_active_;
}
