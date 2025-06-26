#include "Bullet.h"
#include "DxLib.h"
#include "../../Object/GameObjectManager.h"
#include "../../Utility/ResourceManager.h"

//落書き
Bullet::Bullet()
    : speed_(10), is_active_(false)
{
    location.x = 0;
    location.y = 0;
}

void Bullet::Initialize()
{
    // デフォルトの初期化（使用しない場合は削除可）
    Initialize(location, 0, false);
}

void Bullet::Initialize(const Vector2D& start, const Vector2D& target,bool flip_flag)
{
    ResourceManager* rm = ResourceManager::GetInstance();

    // 通常弾
    bullet_image = LoadGraph("Resource/Images/tama.png");

    //爆発アニメ―ション
    std::vector<int> explosion_imgs = rm->GetImages("Resource/Images/haretu.png", 4, 4, 1, 72, 72);
    for (int i = 0; i < 4; ++i)
        explosion_frames[i] = explosion_imgs[i];

    is_exploding = false;
    explosion_index = 0;
    explosion_count = 0;

    location = start;
    target_ = target;           // ← 後で使うため保存
    speed_ = 10.0f;
    is_active_ = true;
    is_shot = false;            // ← 初回フレームにだけ方向計算を行うため

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
    /*AnimeControl();*/
    //GetFlipFlag(1);
    /*location.x += speed_;*/

}

void Bullet::Draw(const Vector2D& screen_offset) const
{


    //if (!is_active_) return;

    //int draw_x = location.x /*- screen_offset.x*/;      // 代用案　（バレットがスクロールでもついてくる）
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
            draw_x - 150, draw_y - 150,   // 左上座標（画像サイズに応じて調整）
            draw_x + 150, draw_y + 150,   // 右下座標（元が72×72なら2倍）
            explosion_frames[explosion_index],
            TRUE
        );
    }
    else
    {
        DrawRotaGraph(
            draw_x,                 // 中心X
            draw_y,                 // 中心Y
            0.35f,                   // 拡大率（必要なら 0.5f など）
            0.0f,                   // 回転なし
            bullet_image,           // 弾画像
            TRUE                    // 透過あり
        );
    }
}

void Bullet::Finalize()
{
    // 必要があれば解放処理
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

