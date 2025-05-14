#include "Player.h"
#include "../../Utility/InputControl.h"
#include"../../Object/GameObjectManager.h"
#include "DxLib.h"


Player::Player()
    : player_x(200), player_y(500),
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
    player_x = 200;
    player_y = 500;

    //バレットの生成位置
    bullet_offset_x = size_x / 2; // 中央から発射
    bullet_offset_y = 28;           // 上端から発射

    hp = 10; //初期HP設定

    bullets.clear();
    last_shot_time = 0;

    collision.object_type = ePlayer;
    collision.box_size = 64;
    collision.hit_object_type.push_back(eEnemy);
}

void Player::Update(float delta_second)
{
    Movement();
    AnimeControl();

    //for (auto& bullet : bullets) {
    //    bullet.Update();
    //}

    //// 死んだ弾を削除
    //bullets.erase(
    //    std::remove_if(bullets.begin(), bullets.end(),
    //        [](const Bullet& b) { return !b.IsActive(); }),
    //    bullets.end());

    //Shoot(); // ←ここで毎フレーム弾を撃つチェック
}

void Player::Draw(const Vector2D& screen_offset) const
{
    // プレイヤー本体
    //DrawBox(location.x, location.y, location.x + size_x, location.y + size_y, color, TRUE);
    DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color, TRUE);

    //// 弾の描画
    //for (const auto& bullet : bullets) {
    //    bullet.Draw();
    //}
}

void Player::Finalize()
{
    bullets.clear();
}

void Player::OnHitCollision(GameBase* hit_object)
{
    if (hit_object->GetCollision().object_type == eEnemy)
    {
        GameBaseManager* gbmm = GameBaseManager::GetInstance();
        gbmm->DestroyGameBase(this);

        DecreaseHP(1); // HPを1減らす
    }
}

// 弾の発射処理
void Player::Shoot()
{
    //int now = GetNowCount();
    //if (InputControl::GetInstance()->GetKey(KEY_INPUT_S) &&
    //    now - last_shot_time >= kShotIntervalMs)
    //{
    //    Bullet b;
    //    b.Initialize(player_x + bullet_offset_x, player_y + bullet_offset_y);
    //    bullets.push_back(b);
    //    last_shot_time = now;
    //}
}

// プレイヤーの移動処理
void Player::Movement()
{
    // 例：矢印キーで移動（シンプルな処理）
    if (CheckHitKey(KEY_INPUT_A)) location.x -= 5;
    if (CheckHitKey(KEY_INPUT_D)) location.x += 5;
    if (CheckHitKey(KEY_INPUT_S)) location.y += 5;
    if (CheckHitKey(KEY_INPUT_W)) location.y -= 5;

    InputControl* input = InputControl::GetInstance();

    // 十字キーの入力に応じて移動
    if (input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::ePress)  location.x -= 5;
}

void Player::AnimeControl()
{
    // アニメーション制御（必要なら）
}

void Player::DecreaseHP(int amount)
{
    hp -= amount;

    // HPが0以下になった時の処理（死亡判定）
    if (hp <= 0)
    {
        hp = 0;
        GameBaseManager::GetInstance()->DestroyGameBase(this); // 死亡時の処理
    }
}

int Player::GetHP() const
{
    return hp;
}

