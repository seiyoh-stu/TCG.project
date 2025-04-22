#include "Bullet.h"
#include "DxLib.h"

Bullet::Bullet()
    : x_(0), y_(0), speed_(5), is_active_(false)
{
}

void Bullet::Initialize(int x, int y)
{
    x_ = x;
    y_ = y;
    is_active_ = true;
}

void Bullet::Update()
{
    if (!is_active_) return;

    x_ += speed_; // ã•ûŒü‚ÉˆÚ“®
    if (y_ < 0) is_active_ = false;
}

void Bullet::Draw() const
{
    if (!is_active_) return;

    DrawBox(x_ - 16, y_ - 16, x_ + 16, y_ + 16, GetColor(255, 255, 0), TRUE);
}

bool Bullet::IsActive() const
{
    return is_active_;
}
