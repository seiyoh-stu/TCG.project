#include "BulletAim.h"
#include "../../Utility/InputControl.h"
#include "../../Object/GameObjectManager.h"
#include "DxLib.h"

BulletAim::BulletAim()
    : location(640, 400),
    Aim_Image(-1)
{
}

BulletAim::~BulletAim()
{

}

void BulletAim::Initialize()
{
    Aim_Image = -1;  // 初期化
    Aim_Image = LoadGraph("Resource/Images/AimMark.png");  // Aim 画像
    collision.object_type = eBulletAim;


}

void BulletAim::Update(float delta_second)
{
    Movement(delta_second);


    //Aimマークを画面に出ないように

    if (location.x < 0.0f)
    {
        location.x = 0.0f;
    }

    if (location.x > 1280.0f)
    {
        location.x = 1280.0f;
    }


    if (location.y < 0.0f)
    {
        location.y = 0.0f;
    }

    if (location.y > 720.0f)
    {
        location.y = 720.0f;
    }

}

void BulletAim::Draw(const Vector2D& screen_offset) const
{
    // 画面上に Aim マークを描画
    DrawExtendGraph(
        static_cast<int>(location.x - 50),
        static_cast<int>(location.y - 50),
        static_cast<int>(location.x + 50),
        static_cast<int>(location.y + 50),
        Aim_Image,
        TRUE
    );

}

void BulletAim::Finalize()
{

}

//void BulletAim::Movement(float delta_second)
//{
//    InputControl* input = InputControl::GetInstance();
//
//    if (CheckHitKey(KEY_INPUT_K)) location.x -= 5;
//    if (CheckHitKey(KEY_INPUT_L)) location.x += 5;
//
//}
void BulletAim::Movement(float delta_second)
{
    Vector2D move = InputControl::GetInstance()->GetJoyStickRight(); // 右スティック取得

    const float AIM_SPEED = 5.0f; // 移動スピード

    location.x += move.x * AIM_SPEED;
    location.y -= move.y * AIM_SPEED; // 上下はY軸反転
}
void BulletAim::AnimeControl()
{

}