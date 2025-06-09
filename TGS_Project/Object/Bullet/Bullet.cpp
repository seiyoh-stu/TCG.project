#include "Bullet.h"
#include "DxLib.h"
#include"../../Object/GameObjectManager.h"


Bullet::Bullet()
    : speed_(10), is_active_(false)
{
    location.x = 0;
    location.y = 0;
}

void Bullet::Initialize()
{
    // デフォルトの初期化（使用しない場合は削除可）
    Initialize(0, 0,false);
}

void Bullet::Initialize(const Vector2D& start, const Vector2D& target,bool flip_flag)
{
    /*location.x = start_x;
    location.y = start_y;*/
    location = start;
    Vector2D diff = target - start;

    // 正規化
    float length = sqrt(diff.x * diff.x + diff.y * diff.y);
    if (length != 0)
    {
        direction_.x = diff.x / length;
        direction_.y = diff.y / length;
    }

    speed_ = 10.0f;
    is_active_ = true;

    collision.object_type = eBullet;
    collision.box_size = 16;
    collision.hit_object_type.push_back(eEnemy);
}

void Bullet::Update(float delta_second)
{

    location.x += direction_.x * speed_;
    location.y += direction_.y * speed_;

    if (location.x > 4000 || location.x < 0 || location.y < 0 || location.y > 3000) {
        is_active_ = false;
        GameBaseManager::GetInstance()->DestroyGameBase(this);
    }

    //GetFlipFlag(1);
    location.x += speed_;

}

void Bullet::Draw(const Vector2D& screen_offset) const
{
    if (!is_active_) return;

    int draw_x = location.x /*- screen_offset.x*/;      // 代用案　（バレットがスクロールでもついてくる）
    int draw_y = location.y /*- screen_offset.y*/;

    DrawBox(
        draw_x - collision.box_size.x,
        draw_y - collision.box_size.y,
        draw_x + collision.box_size.x,
        draw_y + collision.box_size.y,
        GetColor(255, 255, 0), TRUE
    );
}

void Bullet::Finalize()
{
    // 必要があれば解放処理
}

void Bullet::OnHitCollision(GameBase* hit_object)
{
    if (hit_object->GetCollision().object_type == eEnemy)
    {
        GameBaseManager::GetInstance()->DestroyGameBase(this);
    }
}

bool Bullet::IsActive() const
{
    return is_active_;
}

void Bullet::GetFlipFlag(bool flag)
{
    if (flag==TRUE) 
    {
        speed_ = -10;
    }
    else
    {
        speed_ = 10;
    }
}
