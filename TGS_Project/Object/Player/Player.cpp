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

    //�o���b�g�̐����ʒu
    bullet_offset_x = size_x / 2; // �������甭��
    bullet_offset_y = 28;           // ��[���甭��

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

    // ���񂾒e���폜
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const Bullet& b) { return !b.IsActive(); }),
        bullets.end());

    Shoot(); // �������Ŗ��t���[���e�����`�F�b�N
}

void Player::Draw(const Vector2D& screen_offset) const
{
    // �v���C���[�{��
    DrawBox(player_x, player_y, player_x + size_x, player_y + size_y, color, TRUE);

    // �e�̕`��
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

// �e�̔��ˏ���
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

// �v���C���[�̈ړ�����
void Player::Movement()
{
    // ��F���L�[�ňړ��i�V���v���ȏ����j
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
    // �A�j���[�V��������i�K�v�Ȃ�j
}
