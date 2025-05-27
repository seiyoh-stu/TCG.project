#include "Enemy4.h"
#include"../../Object/GameObjectManager.h"
#include"DxLib.h"

Enemy4::Enemy4() :
	//enemy4_x(700), // �����ʒuX���W
	//enemy4_y(500), // �����ʒuY���W
	size4_x_(64),  // �l�p�̕�
	size4_y_(64),  // �l�p�̍���
	color4_(GetColor(255, 0, 0)) // �l�p�̐F (��)
{

}

Enemy4::~Enemy4()
{

}

void Enemy4::Initialize()
{
	collision.object_type = eEnemy;
	collision.box_size = 64;
	collision.hit_object_type.push_back(eBullet);
}

void Enemy4::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy4::Draw(const Vector2D& screen_offset) const
{
	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color4_, TRUE);

}
void Enemy4::Finalize()
{

}
void Enemy4::OnHitCollision(GameBase* hit_object)
{
	if (hit_object->GetCollision().object_type == eBullet)
	{
		GameBaseManager* gbmm = GameBaseManager::GetInstance();
		gbmm->DestroyGameBase(this);
	}
}
//�ړ�����
void Enemy4::Movement()
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

void Enemy4::AnimeControl()
{
	// �A�j���[�V�����Ɋւ��鏈�����L�q (����͋�)
}

//void OnHitCollision(GameBase* hit_object)
//{
//
//}