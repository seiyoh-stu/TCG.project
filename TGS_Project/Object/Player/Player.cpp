#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../../Object/Bullet/Bullet.h"
#include "../../Object/GameObjectManager.h"
#include "DxLib.h"

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
    Bullet* bullet;         //Bullet�ďo����

    //�v���C���[�摜�ǂݍ���
    animation[0] = LoadGraph("Resource/Images/Run1.png");
    animation[1] = LoadGraph("Resource/Images/Run2.png");
    player_image = animation[0];


    player_x = 200;
    player_y = 580;

    bullet_offset_x = size_x / 2;
    bullet_offset_y = 28;

    //�v���C���[HP
    hp = 10;

    //�V���b�g�^�C��
    last_shot_time = 0;

    //�R���W����
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
        // �ʏ�`��i�E�����j
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
        // ���E���]�`��i�������j
        //DrawExtendGraph(
        //    draw_x + size_x / 2,  // �� ���E�̍��W�𔽓]������
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

    // ���ˊԊu�����i�ȗ��j

    // �e������i����GameBaseManager�Ő����j
    GameBaseManager* gbm = GameBaseManager::GetInstance();

    // �e�̏����ʒu�̓v���C���[�̒��S�{�I�t�Z�b�g
    int bullet_x = location.x + (flip_flag ? -bullet_offset_x : bullet_offset_x);
    int bullet_y = location.y + bullet_offset_y;

    last_shot_time = now;
}

void Player::Movement()
{
    InputControl* input = InputControl::GetInstance();

    // ���ړ��i�L�[�{�[�h or �R���g���[���[�j
    if (CheckHitKey(KEY_INPUT_A) || input->GetPadButtonState(PAD_INPUT_LEFT) == eInputState::eHeld)
    {
        if (location.x >= 250)
        {
            location.x -= 5;
            flip_flag = TRUE;  // ������
        }
    }

    // �E�ړ��i�L�[�{�[�h or �R���g���[���[�j
    if (CheckHitKey(KEY_INPUT_D) || input->GetPadButtonState(PAD_INPUT_RIGHT) == eInputState::eHeld)
    {
        if (location.x < 650)
        {
            location.x += 5;
            flip_flag = FALSE; // �E����
        }
    }

    // ���ړ��i�L�[�{�[�h or �R���g���[���[�j
    if (CheckHitKey(KEY_INPUT_S) || input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::eHeld)
    {
        location.y += 5;
    }

    // ��ړ��i�L�[�{�[�h or �R���g���[���[�j
    if (CheckHitKey(KEY_INPUT_W) || input->GetPadButtonState(PAD_INPUT_UP) == eInputState::eHeld)
    {
        location.y -= 5;
    }
}


void Player::AnimeControl()
{
    if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_A)) {


        //�t���[���J�E���g�����Z����
        animation_count++;

        //60�t���[���ڂɒB������
        if (animation_count >= 40)
        {
            //�J�E���g�̃��Z�b�g
            animation_count = 0;

            //�摜�̐؂�ւ�
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

void Player::Player_LevelUp(int levelup)
{
    power_level = levelup;
    bullet_damage = 10 + levelup * 5;
}
