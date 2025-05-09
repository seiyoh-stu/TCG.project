#include "Enemy.h"
#include"../../Object/GameObjectManager.h"
#include"DxLib.h"

Enemy::Enemy() :
	enemy_x(550), // �����ʒuX���W
	enemy_y(500), // �����ʒuY���W
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

}
void Enemy::Finalize()
{

}
void Enemy::OnHitCollision(GameBase* hit_object)
{
	if (hit_object->GetCollision().object_type == eBullet)
	{
		GameBaseManager* gbmm = GameBaseManager::GetInstance();
		gbmm->DestroyGameBase(this);
	}
}
//�ړ�����
void Enemy::Movement()
{
	//�ړ����x
	const int speed = 2;
	//�ړ���
	int move_x = 0;

	// �E�̒[�����ɒ����ƁA���̒[�����Ɉړ�����
	if (location.x >= 100)
	{
		move_x -= speed;
	}

	location.x += move_x;
} 

void Enemy::AnimeControl()
{
	// �A�j���[�V�����Ɋւ��鏈�����L�q (����͋�)
}

void OnHitCollision(GameBase* hit_object)
{

}