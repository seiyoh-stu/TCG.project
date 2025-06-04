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
    scroll_start(false), animation_count(0),
    flip_flag(FALSE)
{

}

Player::~Player()
{


}

void Player::Initialize()
{
    Bullet* bullet;         //Bullet呼出処理

    //プレイヤー画像読み込み
    animation[0] = LoadGraph("Resource/Images/Run1.png");
    animation[1] = LoadGraph("Resource/Images/Run2.png");
    player_image = animation[0];


    player_x = 200;
    player_y = 500;

    bullet_offset_x = size_x / 2;
    bullet_offset_y = 28;

    //プレイヤーHP
    hp = 10;

    //ショットタイム
    last_shot_time = 0;

    //コリジョン
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
}

void Player::Draw(const Vector2D& screen_offset) const
{
    /*int draw_x = location.x - screen_offset.x;
    int draw_y = location.y - screen_offset.y;*/


    if (!flip_flag) {
        // 通常描画（右向き）
        /*DrawExtendGraph(
            draw_x - size_x / 2,
            draw_y - size_y / 2,
            draw_x + size_x / 2,
            draw_y + size_y / 2,
            player_image,
            TRUE
        );*/

        DrawRotaGraph(location.x, location.y, 0.5f, 0.0f, player_image, flip_flag, FALSE);
    }
    else {
        // 左右反転描画（左向き）
        //DrawExtendGraph(
        //    draw_x + size_x / 2,  // ← 左右の座標を反転させる
        //    draw_y - size_y / 2,
        //    draw_x - size_x / 2,
        //    draw_y + size_y / 2,
        //    player_image,
        //    TRUE
        //);

        DrawRotaGraph(location.x, location.y, 0.5f, 0.0f, player_image, flip_flag, TRUE);

    }
    //DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, GetColor(100, 0, 255), TRUE);
}

void Player::Finalize()
{
    DeleteGraph(animation[0]);
    DeleteGraph(animation[1]);
}

void Player::OnHitCollision(GameBase* hit_object)
{
    /*if (hit_object->GetCollision().object_type == eEnemy)
    {
        GameBaseManager* gbmm = GameBaseManager::GetInstance();
        gbmm->DestroyGameBase(this);

        DecreaseHP(1);
    }*/
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

    last_shot_time = now;
}

void Player::Movement()
{
    Bullet* bullet;

    //player移動

    //左に移動
    if (CheckHitKey(KEY_INPUT_A))
    {
        location.x -= 1;
        flip_flag = TRUE;  // 左向き
        if (flip_flag== TRUE)
        {
            //     bullet->GetFlipFlag(TRUE);
        }
    }
    //右に移動
    if (CheckHitKey(KEY_INPUT_D))
    {
        if (location.x < 650)
        {
            location.x += 1;
            flip_flag = FALSE; // 右向き

        }
    }

    if (CheckHitKey(KEY_INPUT_S)) location.y += 1;
    if (CheckHitKey(KEY_INPUT_W)) location.y -= 1;

    InputControl* input = InputControl::GetInstance();
    if (input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::ePress) location.x -= 1;
}

void Player::AnimeControl()
{
    if (CheckHitKey(KEY_INPUT_D)|| CheckHitKey(KEY_INPUT_A)) {
        

        //フレームカウントを加算する
        animation_count++;

        //60フレーム目に達したら
        if (animation_count >= 40)
        {
            //カウントのリセット
            animation_count = 0;

            //画像の切り替え
            if (player_image == animation[0])
            {
                player_image = animation[1];
            }
            else
            {
                player_image = animation[0];
            }
        }
    }
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

