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
    // 位置、当たり判定など初期値を設定（必要に応じて調整）
    location = { 50, 300 };
    z_layer = 1;
    is_mobility = false;
    filp_flag = false;
    hit_flag = false;
    hit = false;

    collision.box_size = 64;


    hp = 20; // 初期化
    // サイズや当たり判定なども必要に応じてここで設定する
}

void Castle::Draw(const Vector2D& screen_offset) const
{
    //Vector2D draw_pos = location - screen_offset;

    //const int width = 200;
    //const int height = 500;
    //unsigned int color = GetColor(255, 0, 0); // 赤色

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

    if (damage_cooldown <= 0.0f && hp > 0)
    {
        hp--; // HPを1減らす
        hit = true;
        //damage_cooldown = DAMAGE_INTERVAL; // ダメージを受けたらクールタイム開始
        printf("Castle HP: %d\n", hp);
    }
}

void Castle::SetScroll(float scroll, float& delta_second)
{
    location.x -= scroll;
}