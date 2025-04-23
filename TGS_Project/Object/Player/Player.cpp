#include "Player.h"
#include "DxLib.h"
#include "../../Utility/InputControl.h"

Player::Player()
    : player_x(300), player_y(400),
    size_x(64), size_y(64),
    color(GetColor(0, 255, 0)),
    bullet_offset_x(0), bullet_offset_y(0),
    last_shot_time(0)
{
}

Player::~Player()
{

}

void Player::Initialize()
{
    player_x = 300;
    player_y = 400;

    //バレットの生成位置
    bullet_offset_x = size_x / 2; // 中央から発射
    bullet_offset_y = 28;           // 上端から発射

    bullets.clear();
    last_shot_time = 0;
}

void Player::Update(float delta_second)
{
    Movement();
    AnimeControl();

    for (auto& bullet : bullets) {
        bullet.Update();
    }

    // 死んだ弾を削除
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const Bullet& b) { return !b.IsActive(); }),
        bullets.end());

    Shoot(); // ←ここで毎フレーム弾を撃つチェック
}

void Player::Draw(const Vector2D& screen_offset) const
{
    // プレイヤー本体
    DrawBox(player_x, player_y, player_x + size_x, player_y + size_y, color, TRUE);

    // 弾の描画
    for (const auto& bullet : bullets) {
        bullet.Draw();
    }
}

void Player::Finalize()
{
    bullets.clear();
}

void Player::OnHitCollision(GameBase* hit_object)
{

}

// 弾の発射処理
void Player::Shoot()
{
    int now = GetNowCount();
    if (InputControl::GetInstance()->GetKey(KEY_INPUT_S) &&
        now - last_shot_time >= kShotIntervalMs)
    {
        Bullet b;
        b.Initialize(player_x + bullet_offset_x, player_y + bullet_offset_y);
        bullets.push_back(b);
        last_shot_time = now;
    }
}

// プレイヤーの移動処理
void Player::Movement()
{
    // 例：矢印キーで移動（シンプルな処理）
<<<<<<< HEAD
    if (CheckHitKey(KEY_INPUT_A)) pos_x_ -= 5;
    if (CheckHitKey(KEY_INPUT_D)) pos_x_ += 5;
=======
    if (CheckHitKey(KEY_INPUT_A)) player_x -= 5;
    if (CheckHitKey(KEY_INPUT_D)) player_x += 5;
>>>>>>> seiyo
}

void Player::AnimeControl()
{
    // アニメーション制御（必要なら）
}
