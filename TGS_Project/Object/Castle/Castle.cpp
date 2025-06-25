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

    //// HP割合から色を決定（緑→黄→赤）
    //float hp_ratio = (float)hp / 500.0f;  // 最大HPが500の場合
    //int r, g, b;

    //if (hp_ratio > 0.5f) {
    //    // 緑〜黄（安全ゾーン）
    //    r = (int)(255 * (1.0f - hp_ratio) * 2); // 0〜255
    //    g = 255;
    //}
    //else {
    //    // 黄〜赤（危険ゾーン）
    //    r = 255;
    //    g = (int)(255 * hp_ratio * 2); // 255〜0
    //}
    //b = 0;

    //unsigned int hpColor = GetColor(r, g, b);

    //// 文字列作成
    //char hpText[64];
    //sprintf_s(hpText, sizeof(hpText), "フェンスのHP: %d", hp);

    // 描画（フォントハンドルを使うならこちらを使う）
    // DrawStringToHandle(20, 20, hpText, hpColor, fontHandle);

    // フォントハンドル未使用の場合はこちら
    //DrawFormatString(20, 20, hpColor, hpText);


    // === HPバー描画 ===

// HPバーの表示位置とサイズ
    const int bar_x = 20;
    const int bar_y = 30;
    const int bar_width = 1230;
    const int bar_height = 30;

    // HP割合（最大HPは500として計算）
    float hp_ratio = (float)hp / 500.0f;
    if (hp_ratio < 0.0f) hp_ratio = 0.0f;
    if (hp_ratio > 1.0f) hp_ratio = 1.0f;

    // 背景（灰色）
    DrawBox(bar_x, bar_y, bar_x + bar_width, bar_y + bar_height, GetColor(100, 100, 100), TRUE);

    // 現在HPバー（色は割合に応じて緑→赤）
    int r, g;
    if (hp_ratio > 0.5f) {
        r = (int)(255 * (1.0f - hp_ratio) * 2);
        g = 255;
    }
    else {
        r = 255;
        g = (int)(255 * hp_ratio * 2);
    }
    unsigned int bar_color = GetColor(r, g, 0);

    // 実際のHPバー描画
    int current_bar_width = (int)(bar_width * hp_ratio);
    DrawBox(bar_x, bar_y, bar_x + current_bar_width, bar_y + bar_height, bar_color, TRUE);

    // HP数値表示（オプション）
    char hpText[64];
    sprintf_s(hpText, sizeof(hpText), "フェンスのHP: %d / 500", hp);
    DrawFormatString(bar_x, bar_y - 20, GetColor(255, 255, 255), hpText);





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
