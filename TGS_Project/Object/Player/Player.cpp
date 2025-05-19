#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../../Object/GameObjectManager.h"
#include "DxLib.h"

Player::Player()
    : player_x(200), player_y(500),
    size_x(64), size_y(64),
    color(GetColor(0, 255, 0)),
    bullet_offset_x(0), bullet_offset_y(0),
    last_shot_time(0), scroll_end(false),
    scroll_start(false),
    flip_flag(false)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
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

}

void Player::Draw(const Vector2D& screen_offset) const
{
    int draw_x = location.x - screen_offset.x;
    int draw_y = location.y - screen_offset.y;

    DrawBox(
        draw_x - collision.box_size.x,
        draw_y - collision.box_size.y,
        draw_x + collision.box_size.x,
        draw_y + collision.box_size.y,
        color, TRUE
    );
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

    //if (InputControl::GetInstance()->GetKey(KEY_INPUT_L) &&
    //    now - last_shot_time >= kShotIntervalMs)
    //{
    //    Vector2D spawn_pos(location.x + bullet_offset_x, location.y + bullet_offset_y);
    //    GameBaseManager::GetInstance()->CreateGameBase<Bullet>(spawn_pos);
    //    last_shot_time = now;
    //}
}

void Player::Movement()
{
    if (CheckHitKey(KEY_INPUT_A)) location.x -= 2;
    if (CheckHitKey(KEY_INPUT_D)) location.x += 2;
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