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


    // ResourceManagerから画像取得（歩き・待機）
    ResourceManager* rm = ResourceManager::GetInstance();

    // 右向きの歩き
    std::vector<int> walk_right_frames = rm->GetImages("Resource/Images/GamePlayer/Walk_Right.png", 10, 10, 1, 128, 128);//右歩き
    std::vector<int> walk_left_frames = rm->GetImages("Resource/Images/GamePlayer/Walk_Left.png", 10, 10, 1, 128, 128);  //左歩き

    // 待機画像を読み込み
    std::vector<int> idle_right_frames = rm->GetImages("Resource/Images/GamePlayer/Idle_Right.png", 6, 6, 1, 128, 128);//待機右
    std::vector<int> idle_left_frames = rm->GetImages("Resource/Images/GamePlayer/Idle_Left.png", 6, 6, 1, 128, 128);//待機左
   


    // アニメーション格納
    
    //右歩き
    for (int i = 0; i < 10; ++i) {
        walk_right_animation[i] = walk_right_frames[i];
    }

    //左歩き
    for (int i = 0; i < 10; ++i) {
        walk_left_animation[i] = walk_left_frames[9 - i];
    }


    //待機状態
    for (int i = 0; i < 6; ++i) {
        idle_right_animation[i] = idle_right_frames[i];
        idle_left_animation[i] = idle_left_frames[i];
    }

    // 初期画像は右向き待機の最初の画像
    player_image = idle_right_animation[0];


    walk_index = 0;
    idle_index = 0;
    animation_count = 0;
   

    // プレイヤーの初期位置
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

    // スクロール開始位置の判定
    if (!scroll_start && location.x >= 640) {
        scroll_start = true;
    }

    /*if (location.x > WINDOW_WIDTH / 2) {
        scroll_x = static_cast<int>(location.x - WINDOW_WIDTH / 2);
    }*/

}

void Player::Draw(const Vector2D& screen_offset) const
{
    int draw_x = static_cast<int>(location.x - scroll_x);
    int draw_y = static_cast<int>(location.y);

    DrawRotaGraph(draw_x, draw_y, 2.0f, 0.0f, player_image, TRUE);
}

void Player::Finalize()
{
    
}

void Player::OnHitCollision(GameBase* hit_object)
{
    
}

void Player::Shoot()
{
    int now = GetNowCount();

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

    //プレイヤーが歩けるY座標
    if (location.y < 390.0f)
    {
        location.y = 390.0f;
    }

    if (location.y > 580.0f)
    {
        location.y = 580.0f;
    }

}


void Player::AnimeControl()
{
    InputControl* input = InputControl::GetInstance();

    bool isMoving = CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_W)
        || (input->GetPadButtonState(PAD_INPUT_UP) == eInputState::eHeld)
        || (input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::eHeld)
        || (input->GetPadButtonState(PAD_INPUT_LEFT) == eInputState::eHeld)
        || (input->GetPadButtonState(PAD_INPUT_RIGHT) == eInputState::eHeld);

    animation_count++;

    if (isMoving) {
        if (animation_count >= 8) {
            animation_count = 0;
            walk_index++;
            if (walk_index >= 10) {
                walk_index = 0;
            }

            if (flip_flag) {
                player_image = walk_left_animation[walk_index];
            }
            else {
                player_image = walk_right_animation[walk_index];
            }
        }
    }
    else {
        if (animation_count >= 60) {
            animation_count = 0;
            idle_index++;
            if (idle_index >= 6) {
                idle_index = 0;
            }

            if (flip_flag) {
                player_image = idle_left_animation[idle_index];
            }
            else {
                player_image = idle_right_animation[idle_index];
            }
        }
    }


    if (bulletaim->GetLocation().x < location.x)
    {
        flip_flag = true;
    }
    else
    {
        flip_flag = false;
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

void Player::SetBulletAim(BulletAim* Aim)
{
    bulletaim = Aim;
}
