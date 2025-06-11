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
    std::vector<int> walk_frames = rm->GetImages("Resource/Images/GamePlayer/Walk.png", 10, 10, 1, 128, 128);//歩き
    std::vector<int> idle_frames = rm->GetImages("Resource/Images/GamePlayer/Idle.png", 6, 6, 1, 128, 128);//待機


    // アニメーション格納
    for (int i = 0; i < 10; ++i) {
        walk_animation[i] = walk_frames[i];
    }
    for (int i = 0; i < 6; ++i) {
        idle_animation[i] = idle_frames[i];
    }


    // 初期表示画像を設定
    player_image = idle_animation[0];
    walk_index = 0;
    idle_index = 0;
    animation_count = 0;
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
}

void Player::Draw(const Vector2D& screen_offset) const
{
    if (!flip_flag) {
        
        DrawRotaGraph(location.x, location.y, 2.0f, 0.0f, player_image, flip_flag, FALSE);

    }
    else {

        DrawRotaGraph(location.x, location.y, 2.0f, 0.0f, player_image, flip_flag, TRUE);
    }
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
    InputControl* input = InputControl::GetInstance();


    //ここのキー・ボタンを押すと歩きアニメーションを行う
    bool isMoving = CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_W)
        ||(input->GetPadButtonState(PAD_INPUT_UP) == eInputState::eHeld) || (input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::eHeld)
        ||(input->GetPadButtonState(PAD_INPUT_LEFT) == eInputState::eHeld) || (input->GetPadButtonState(PAD_INPUT_RIGHT) == eInputState::eHeld);
                  

    animation_count++;


    //歩き状態のアニメーション
    if (isMoving) {
        if (animation_count >= 8) {//ここで調整できる
            animation_count = 0;

            walk_index++;
            if (walk_index >= 10) {//歩き画像の枚数
                walk_index = 0;
            }

            player_image = walk_animation[walk_index];
        }
    }
    //待機状態のアニメーション
    else {
        if (animation_count >= 60) {//ここで調整できる
            animation_count = 0;

            idle_index++;
            if (idle_index >= 6) {//歩き画像の枚数
                idle_index = 0;
            }

            player_image = idle_animation[idle_index];
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

void Player::Player_LevelUp(int levelup)
{
    power_level = levelup;
    bullet_damage = 10 + levelup * 5;
}
