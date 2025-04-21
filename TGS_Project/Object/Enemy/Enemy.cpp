#include "Enemy.h"
#include"DxLib.h"

Enemy::Enemy() :
	pos_x_(550), // �����ʒuX���W
	pos_y_(350), // �����ʒuY���W
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

void Enemy::Update()
{
	Movement();
	AnimeControl();

}

void Enemy::Draw()
{
	DrawBox(pos_x_, pos_y_, pos_x_ + size_x_, pos_y_ + size_y_, color_, TRUE);
}
void Enemy::Finalize()
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
	if (pos_x_ >= 100)
	{
		move_x -= speed;
	}

	pos_x_ += move_x;
} 

void Enemy::AnimeControl()
{
	// �A�j���[�V�����Ɋւ��鏈�����L�q (����͋�)
}