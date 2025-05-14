#include "Enemy3.h"
#include"../../Object/GameObjectManager.h"
#include"DxLib.h"

Enemy3::Enemy3() :
	enemy3_x(650), // �����ʒuX���W
	enemy3_y(500), // �����ʒuY���W
	size3_x_(64),  // �l�p�̕�
	size3_y_(64),  // �l�p�̍���
	color3_(GetColor(255, 0, 0)) // �l�p�̐F (��)
{

}

Enemy3::~Enemy3()
{

}

void Enemy3::Initialize()
{
	collision.object_type = eEnemy;
	collision.box_size = 64;
	collision.hit_object_type.push_back(eBullet);
}

void Enemy3::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy3::Draw(const Vector2D& screen_offset) const
{
	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color3_, TRUE);

}
void Enemy3::Finalize()
{

}
void Enemy3::OnHitCollision(GameBase* hit_object)
{
	if (hit_object->GetCollision().object_type == eBullet)
	{
		GameBaseManager* gbmm = GameBaseManager::GetInstance();
		gbmm->DestroyGameBase(this);
	}
}
//�ړ�����
void Enemy3::Movement()
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

void Enemy3::AnimeControl()
{
	// �A�j���[�V�����Ɋւ��鏈�����L�q (����͋�)
}

//void OnHitCollision(GameBase* hit_object)
//{
//
//}