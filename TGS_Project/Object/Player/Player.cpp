#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../../Object/Bullet/Bullet.h"
#include "../../Object/GameObjectManager.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"

Player::Player()
    : player_x(200), player_y(580),
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


    ResourceManager* rm = ResourceManager::GetInstance();


    std::vector<int> frames = rm->GetImages("Resource/Images/GamePlayer/Walk.png", 10, 10, 1, 128, 128);

    // アニメーションフレームの格納
    for (int i = 0; i < 10; ++i) {
        animation[i] = frames[i];
    }

    player_image = animation[0];
    animation_index = 0;
    animation_count = 0;

    // 最初の画像をセット
    player_image = animation[0];

    player_x = 200;
    player_y = 580;

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

    location.x = player_x;
    location.y = player_y;

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




        DrawRotaGraph(location.x, location.y, 2.0f, 0.0f, player_image, flip_flag, FALSE);

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

        DrawRotaGraph(location.x, location.y, 2.0f, 0.0f, player_image, flip_flag, TRUE);
    }
}


void Player::Finalize()
{
    
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
    InputControl* input = InputControl::GetInstance();

    // 左移動（キーボード or コントローラー）
    if (CheckHitKey(KEY_INPUT_A) || input->GetPadButtonState(PAD_INPUT_LEFT) == eInputState::eHeld)
    {
        if (location.x >= 250)
        {
            location.x -= 5;
            flip_flag = TRUE;  // 左向き
        }
    }

    // 右移動（キーボード or コントローラー）
    if (CheckHitKey(KEY_INPUT_D) || input->GetPadButtonState(PAD_INPUT_RIGHT) == eInputState::eHeld)
    {
        if (location.x < 650)
        {
            location.x += 5;
            flip_flag = FALSE; // 右向き
        }
    }

    // 下移動（キーボード or コントローラー）
    if (CheckHitKey(KEY_INPUT_S) || input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::eHeld)
    {
        location.y += 5;
    }

    // 上移動（キーボード or コントローラー）
    if (CheckHitKey(KEY_INPUT_W) || input->GetPadButtonState(PAD_INPUT_UP) == eInputState::eHeld)
    {
        location.y -= 5;
    }

    //プレイヤーが歩ける縦軸
    if (location.y < 395.0f)
    {
        location.y = 395.0f;
    }

    if (location.y > 590.0f)
    {
        location.y = 590.0f;
    }

}


void Player::AnimeControl()
{
    bool isMoving = CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_A);

    if (isMoving) {
        animation_count++;

        if (animation_count >= 7) {  // 5フレームで切り替え（速度は調整可能）
            animation_count = 0;

            animation_index++;
            if (animation_index >= 10) {
                animation_index = 0;
            }

            player_image = animation[animation_index];
        }
    }
    else {
        // 静止時は1枚目を表示
        animation_index = 0;
        player_image = animation[animation_index];
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

void Player::Player_LevelUp(int levelup)
{
    power_level = levelup;
    bullet_damage = 10 + levelup * 5;
}
