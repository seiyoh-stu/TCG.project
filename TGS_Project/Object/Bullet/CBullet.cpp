#include "CBullet.h"
#include "DxLib.h"
#include "../../Object/GameObjectManager.h"

//落書き
CBullet::CBullet()
    : speed_(10), is_active_(false)
{
    location.x = 0;
    location.y = 0;
}

void CBullet::Initialize()
{
    // デフォルトの初期化（使用しない場合は削除可）
    Initialize(location, 0, false);

    // 通常弾
    bullet_image = LoadGraph("Resource/Images/tama.png");
}

void CBullet::Initialize(const Vector2D& start, const Vector2D& target, bool flip_flag)
{
    /*location.x = start_x;
    location.y = start_y;*/
    //location = start;
    //Vector2D diff = target - start;

    //// 正規化
    //float length = sqrt(diff.x * diff.x + diff.y * diff.y);
    //if (length != 0)
    //{
    //    direction_.x = diff.x / length;
    //    direction_.y = diff.y / length;
    //}
    location = start;
    target_ = target;           // ← 後で使うため保存
    speed_ = 10.0f;
    is_active_ = true;
    is_shot = false;            // ← 初回フレームにだけ方向計算を行うため

    collision.object_type = eBullet;
    collision.box_size = 16;
    collision.hit_object_type.push_back(eEnemy);
}

void CBullet::Update(float delta_second)
{
    //if (bulletaim != nullptr && is_shot == false)
    //{
    //    Vector2D diff = bulletaim->GetLocation() - location;

    //    // 正規化
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
            direction_ = { 0, -1 }; // デフォルト方向：上
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

    int draw_x = location.x /*- screen_offset.x*/;      // 代用案　（バレットがスクロールでもついてくる）
    int draw_y = location.y /*- screen_offset.y*/;

   /* DrawBox(
        draw_x - collision.box_size.x,
        draw_y - collision.box_size.y,
        draw_x + collision.box_size.x,
        draw_y + collision.box_size.y,
        GetColor(255, 255, 0), TRUE
    );*/

    DrawRotaGraph(
        draw_x,                 // 中心X
        draw_y,                 // 中心Y
        0.35f,                   // 拡大率（必要なら 0.5f など）
        0.0f,                   // 回転なし
        bullet_image,           // 弾画像
        TRUE                    // 透過あり
    );
}

void CBullet::Finalize()
{
    // 必要があれば解放処理
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
