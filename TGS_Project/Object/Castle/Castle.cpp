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

    

    // 位置、当たり判定など初期値を設定（必要に応じて調整）
    location = { 50, 250 };
    z_layer = 1;
    is_mobility = false;
    filp_flag = false;
    hit_flag = false;
    hit = false;

    collision.object_type = eCastle;
    collision.hit_object_type.push_back(eEnemy);

    damage_cooldown = 1.0f;

    collision.box_size = { 64, 400 };  // 幅128px, 高さ128px


    hp = 500;// 初期化

    // サイズや当たり判定なども必要に応じてここで設定する
}

void Castle::Draw(const Vector2D& screen_offset) const
{
    Vector2D offset = { -200, -450 }; // 画像の位置調整用オフセット
    Vector2D draw_pos = location - screen_offset + offset;

    if (castle_graph != -1)
    {
        DrawExtendGraph(
            draw_pos.x,
            draw_pos.y,
            draw_pos.x + 300,   // 幅128ピクセルに調整（例）
            draw_pos.y + 600,   // 高さ400ピクセルに調整（例）
            castle_graph,
            TRUE);
    }

    //// スクロールの影響を受けない描画位置（例：画面の左下に固定）
    //Vector2D fixed_screen_pos = { -200, -450 }; // 画面上の表示座標を直接指定

    //if (castle_graph != -1)
    //{
    //    DrawExtendGraph(
    //        fixed_screen_pos.x,
    //        fixed_screen_pos.y,
    //        fixed_screen_pos.x + 300,  // 幅
    //        fixed_screen_pos.y + 600,  // 高さ
    //        castle_graph,
    //        TRUE);
    //}

    // ※ デバッグ用の当たり判定表示（必要なら）
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
    //unsigned int color = GetColor(255, 0, 0); // 赤色

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
    // 各敵のクールダウン時間を進める
    for (auto& pair : enemy_cooldowns)
    {
        pair.second += delta_second;
    }
    // クールダウンを進める
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
        float& cooldown = enemy_cooldowns[hit_object];  // 敵ごとのクールダウン

        const float DAMAGE_INTERVAL = 1.0f; // 秒単位でのダメージ間隔（任意）

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
    //    hp--; // HPを1減らす
    //    hit = true;
    //    //damage_cooldown = DAMAGE_INTERVAL; // ダメージを受けたらクールタイム開始
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
