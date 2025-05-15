#include "Castle.h"
#include "DxLib.h"

Castle::Castle()
{

}

Castle::~Castle()
{

}

void Castle::Initialize()
{
    // 位置、当たり判定など初期値を設定（必要に応じて調整）
    location = { 100, 300 };
    z_layer = 1;
    is_mobility = false;
    filp_flag = false;
    hit_flag = false;

    // サイズや当たり判定なども必要に応じてここで設定する
}

void Castle::Draw(const Vector2D& screen_offset) const
{
    Vector2D draw_pos = location - screen_offset;

    const int width = 200;
    const int height = 500;
    unsigned int color = GetColor(255, 0, 0); // 赤色

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

}
