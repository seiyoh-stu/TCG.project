#include "Bullet.h"
#include "DxLib.h"
#include"../../Object/GameObjectManager.h"

Bullet::Bullet()
    : speed_(5), is_active_(false)
{
    location.x = 0;
    location.y = 0;
}

void Bullet::Initialize()
{
    // デフォルトの初期化（使用しない場合は削除可）
    Initialize(0, 0);
}

void Bullet::Initialize(int start_x, int start_y)
{
    location.x = start_x;
    location.y = start_y;
    is_active_ = true;

    collision.object_type = eBullet;
    collision.box_size = 16;
    collision.hit_object_type.push_back(eEnemy);
}

void Bullet::Update(float delta_second)
{
    location.x += speed_;

    if (location.x >4000) {  
        is_active_ = false;
        GameBaseManager::GetInstance()->DestroyGameBase(this);
    }
}

void Bullet::Draw(const Vector2D& screen_offset) const
{
    if (!is_active_) return;

    int draw_x = location.x - screen_offset.x;
    int draw_y = location.y - screen_offset.y;

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
