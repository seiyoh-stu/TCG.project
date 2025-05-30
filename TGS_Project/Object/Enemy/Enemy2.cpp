#include "Enemy2.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"

Enemy2::Enemy2() :
	enemy2_x(600), // �����ʒuX���W
	enemy2_y(500), // �����ʒuY���W
	size2_x_(64),  // �l�p�̕�
	size2_y_(64),  // �l�p�̍���
	color2_(GetColor(255, 255, 0)) // �l�p�̐F (��)
{

}

Enemy2::~Enemy2()
{

}

void Enemy2::Initialize()
{
	collision.object_type = eEnemy;
	collision.box_size = 64;
	collision.hit_object_type.push_back(eBullet);
}

void Enemy2::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy2::Draw(const Vector2D& screen_offset) const
{
	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color2_, TRUE);

}
void Enemy2::Finalize()
{

}
void Enemy2::OnHitCollision(GameBase* hit_object)
{
	if (hit_object->GetCollision().object_type == eBullet)
	{
		static bool check_hit = false;

		if (check_hit == false)
		{
			// �X�R�A�����Z����
			ScoreManager* score = ScoreManager::GetInstance();
			score->AddScore(50); // �G��|����100�_���Z�i�K�X�����j
			check_hit = true;
		}

		GameBaseManager* gbmm = GameBaseManager::GetInstance();
		gbmm->DestroyGameBase(this);
	}
}
//�ړ�����
void Enemy2::Movement()
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

void Enemy2::AnimeControl()
{
	// �A�j���[�V�����Ɋւ��鏈�����L�q (����͋�)
}

//void OnHitCollision(GameBase* hit_object)
//{
//
//}