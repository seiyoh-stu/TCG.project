#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../../Object/Bullet/Bullet.h"
#include "../../Object/GameObjectManager.h"
#include "DxLib.h"

Player::Player()
    : player_x(200), player_y(500),
    size_x(128), size_y(128),
    color(GetColor(0, 255, 0)),
    bullet_offset_x(0), bullet_offset_y(0),
    last_shot_time(0), scroll_end(false),
    scroll_start(false),
	flip_flag(FALSE)
{

}

Player::~Player()
{


}

void Player::Initialize()
{
    Bullet* bullet;         //Bullet呼出処理

	player_image = LoadGraph("Resource/Images/player(2).png");
    player_x = 200;
    player_y = 500;

    bullet_offset_x = size_x / 2;
    bullet_offset_y = 28;

    hp = 10;
    last_shot_time = 0;

    collision.object_type = ePlayer;
    collision.box_size = 64;
    collision.hit_object_type.push_back(eEnemy);
}

void Player::Update(float delta_second)
{
    Movement();
    Shoot();
    AnimeControl();

    if (!scroll_start && location.x >= 640) {
        scroll_start = true;
    }

    if (location.x < 24) {
        location.x = 24;
    }
    if (location.x > 2400) {
        location.x = 2400;
    }
    if (location.y < 40) {
        location.y = 40;
    }
    if (location.y >650) {
        location.y = 650;
    }

}

void Player::Draw(const Vector2D& screen_offset) const
{
    int draw_x = location.x - screen_offset.x;
	int draw_y = location.y - screen_offset.y;


    if (!flip_flag) {
        // 通常描画（右向き）
        DrawExtendGraph(
            draw_x - size_x / 2,
            draw_y - size_y / 2,
            draw_x + size_x / 2,
            draw_y + size_y / 2,
            player_image,
            TRUE
        );
    }
    else {
        // 左右反転描画（左向き）
        DrawExtendGraph(
            draw_x + size_x / 2,  // ← 左右の座標を反転させる
            draw_y - size_y / 2,
            draw_x - size_x / 2,
            draw_y + size_y / 2,
            player_image,
            TRUE
        );
    }
}

void Player::Finalize()
{
}

void Player::OnHitCollision(GameBase* hit_object)
{
    if (hit_object->GetCollision().object_type == eEnemy)
    {
        GameBaseManager* gbmm = GameBaseManager::GetInstance();
        gbmm->DestroyGameBase(this);

        DecreaseHP(1);
    }
}

void Player::Shoot()
{
    int now = GetNowCount();

    // 発射間隔制御例（省略）

    // 弾生成例（仮にGameBaseManagerで生成）
    GameBaseManager* gbm = GameBaseManager::GetInstance();

    // 弾の初期位置はプレイヤーの中心＋オフセット
    int bullet_x = location.x + (flip_flag ? -bullet_offset_x : bullet_offset_x);
    int bullet_y = location.y + bullet_offset_y;

   /* Bullet* bullet = gbm->CreateBullet();
    if (bullet)
    {
        bullet->Initialize(bullet_x, bullet_y, flip_flag);
    }*/

    last_shot_time = now;
}

void Player::Movement()
{
    Bullet* bullet;

    if (CheckHitKey(KEY_INPUT_A))
    {
        location.x -= 2;
        flip_flag = TRUE;  // 左向き
        if (flip_flag = TRUE)
        {
       //     bullet->GetFlipFlag(TRUE);
       }
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        location.x += 2;
        flip_flag = FALSE; // 右向き
    }
    if (CheckHitKey(KEY_INPUT_S)) location.y += 2;
    if (CheckHitKey(KEY_INPUT_W)) location.y -= 2;

    InputControl* input = InputControl::GetInstance();
    if (input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::ePress) location.x -= 5;
}

void Player::AnimeControl()
{
    // アニメーション制御
}

void Player::DecreaseHP(int amount)
{
    hp -= amount;
    if (hp <= 0)
    {
        hp = 0;
        GameBaseManager::GetInstance()->DestroyGameBase(this);
    }
}

int Player::GetHP() const
{
    return hp;
}

Vector2D& Player::GetLocation()
{
    return this->location;
}

