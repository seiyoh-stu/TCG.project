#include "Enemy.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"

#define MAX_HP 6  // 6�Ȃ�3���Ŏ���

Enemy::Enemy() :
	enemy_x(550), // �����ʒuX���W
	enemy_y(580), // �����ʒuY���W
	size_x_(64),  // �l�p�̕�
	size_y_(64),  // �l�p�̍���
	color_(GetColor(255, 0, 0)) // �l�p�̐F (��)
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
	collision.object_type = eEnemy;
	collision.box_size = 64;
	collision.hit_object_type.push_back(eBullet);

	is_dead_ = false; // ���S�t���O������

	hp = MAX_HP;

}

void Enemy::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy::Draw(const Vector2D& screen_offset) const
{
	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color_, TRUE);

	Vector2D hp_bar = location;
	hp_bar -= Vector2D(25.0f, 60.0f);

	int color = GetColor(7, 255, 0);

	if (hp <= (MAX_HP / 2))
	{
		color = GetColor(255, static_cast<int>(255 * static_cast<float>(hp) / MAX_HP), 0);
	}
	else
	{
		color = GetColor(7 + 2 * static_cast<int>(248 * (1 - static_cast<float>(hp) / MAX_HP)), 255, 0);
	}
	DrawBoxAA(hp_bar.x, hp_bar.y, hp_bar.x + 50, hp_bar.y + 5.0f,
		0x000000, TRUE);
	DrawBoxAA(hp_bar.x, hp_bar.y, hp_bar.x + (50 * (static_cast<float>(hp) / MAX_HP)), hp_bar.y + 5.0f,
		color, TRUE);
	DrawBoxAA(hp_bar.x, hp_bar.y, hp_bar.x + 50, hp_bar.y + 5.0f,
		0x8f917f, FALSE);

}
void Enemy::Finalize()
{

}
void Enemy::OnHitCollision(GameBase* hit_object)
{

	if (hit_object->GetCollision().object_type == eBullet)
	{
		// HP�����炷
		hp--;

		// HP��0�ȉ��Ȃ�I�u�W�F�N�g���폜
		if (hp <= 0)
		{
			is_dead_ = true;

			GameBaseManager* gbmm = GameBaseManager::GetInstance();
			gbmm->DestroyGameBase(this);

			// �X�R�A���Z�i�|�����u�Ԃ̂݁j
			ScoreManager* score = ScoreManager::GetInstance();
			score->AddScore(200); // 200�_�i�K�v�ɉ����Ē����j
		}
	}
}
//bool Enemy::IsDead() const
//{
//	return is_dead_;
//}
//�ړ�����
void Enemy::Movement()
{
	//�ړ����x
	const int speed = 4;
	//�ړ���
	int move_x = 0;

	// �E�̒[�����ɒ����ƁA���̒[�����Ɉړ�����
	if (location.x >= 0)
	{
		move_x -= speed;
	}

	location.x += move_x;
} 

void Enemy::AnimeControl()
{
	// �A�j���[�V�����Ɋւ��鏈�����L�q (����͋�)
}

//void OnHitCollision(GameBase* hit_object)
//{
//
//}