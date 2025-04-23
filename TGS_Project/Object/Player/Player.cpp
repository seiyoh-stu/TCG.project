#include "Player.h"
#include "DxLib.h"
#include "../../Utility/InputControl.h"

Player::Player()
    : pos_x_(300), pos_y_(400),
    size_x_(64), size_y_(64),
    color_(GetColor(0, 255, 0)),
    bullet_offset_x_(0), bullet_offset_y_(0),
    last_shot_time_(0)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
    pos_x_ = 300;
    pos_y_ = 400;

    //バレットの生成位置
    bullet_offset_x_ = size_x_ / 2; // 中央から発射
    bullet_offset_y_ = 28;           // 上端から発射

    bullets_.clear();
    last_shot_time_ = 0;
}

void Player::Update()
{
    Movement();
    AnimeControl();

    for (auto& bullet : bullets_) {
        bullet.Update();
    }

    // 死んだ弾を削除
    bullets_.erase(
        std::remove_if(bullets_.begin(), bullets_.end(),
            [](const Bullet& b) { return !b.IsActive(); }),
        bullets_.end());

    Shoot(); // ←ここで毎フレーム弾を撃つチェック
}

void Player::Draw()
{
    // プレイヤー本体
    DrawBox(pos_x_, pos_y_, pos_x_ + size_x_, pos_y_ + size_y_, color_, TRUE);

    // 弾の描画
    for (const auto& bullet : bullets_) {
        bullet.Draw();
    }
}

void Player::Finalize()
{
    bullets_.clear();
}

// 弾の発射処理
void Player::Shoot()
{
    int now = GetNowCount();
    if (InputControl::GetInstance()->GetKey(KEY_INPUT_S) &&
        now - last_shot_time_ >= kShotIntervalMs_)
    {
        Bullet b;
        b.Initialize(pos_x_ + bullet_offset_x_, pos_y_ + bullet_offset_y_);
        bullets_.push_back(b);
        last_shot_time_ = now;
    }
}

void Player::Movement()
{
    // 例：矢印キーで移動（シンプルな処理）
    if (CheckHitKey(KEY_INPUT_D)) pos_x_ -= 5;
    if (CheckHitKey(KEY_INPUT_A)) pos_x_ += 5;
}

void Player::AnimeControl()
{
    // アニメーション制御（必要なら）
}
