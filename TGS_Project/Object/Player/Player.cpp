#include "Player.h"
#include "DxLib.h"
#include "../../Utility/InputControl.h"

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

    //�o���b�g�̐����ʒu
    bullet_offset_x = size_x / 2; // �������甭��
    bullet_offset_y = 28;           // ��[���甭��

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

    //// ���񂾒e���폜
    //bullets.erase(
    //    std::remove_if(bullets.begin(), bullets.end(),
    //        [](const Bullet& b) { return !b.IsActive(); }),
    //    bullets.end());

    //Shoot(); // �������Ŗ��t���[���e�����`�F�b�N
}

void Player::Draw(const Vector2D& screen_offset) const
{
    // �v���C���[�{��
    //DrawBox(location.x, location.y, location.x + size_x, location.y + size_y, color, TRUE);
    DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color, TRUE);

    //// �e�̕`��
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

}

// �e�̔��ˏ���
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

// �v���C���[�̈ړ�����
void Player::Movement()
{
    // ��F���L�[�ňړ��i�V���v���ȏ����j
    if (CheckHitKey(KEY_INPUT_A)) location.x -= 5;
    if (CheckHitKey(KEY_INPUT_D)) location.x += 5;
}

void Player::AnimeControl()
{
    // �A�j���[�V��������i�K�v�Ȃ�j
}
