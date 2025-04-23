#include "Enemy.h"
#include"DxLib.h"

Enemy::Enemy() :
	enemy_x(550), // �����ʒuX���W
	enemy_y(350), // �����ʒuY���W
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

}

void Enemy::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy::Draw(const Vector2D& screen_offset) const
{
	DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
}
void Enemy::Finalize()
{

}
void Enemy::OnHitCollision(GameBase* hit_object)
{

}
//�ړ�����
void Enemy::Movement()
{
	//�ړ����x
	const int speed = 2;
	//�ړ���
	int move_x = 0;

	// �E�̒[�����ɒ����ƁA���̒[�����Ɉړ�����
	if (enemy_x >= 100)
	{
		move_x -= speed;
	}

	enemy_x += move_x;
} 

void Enemy::AnimeControl()
{
	// �A�j���[�V�����Ɋւ��鏈�����L�q (����͋�)
}

void OnHitCollision(GameBase* hit_object)
{

}