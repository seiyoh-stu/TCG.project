#include "Enemy2.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"

#define MAX_HP 10  // 6�Ȃ�3���Ŏ���

Enemy2::Enemy2() :
	enemy2_x(600), // �����ʒuX���W
	enemy2_y(580), // �����ʒuY���W
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

	hp = MAX_HP;
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
void Enemy2::Finalize()
{

}


void Enemy2::OnHitCollision(GameBase* hit_object)
{

	if (hit_object->GetCollision().object_type == eBullet)
	{
		int damage = 1;
		if (damage_boost)
		{
			damage = 2;
		}

		hp -= damage;

		if (hp <= 0)
		{
			is_dead_ = true;
			GameBaseManager::GetInstance()->DestroyGameBase(this);
			ScoreManager::GetInstance()->AddScore(200);
		}
	}
}//�ړ�����
void Enemy2::Movement()
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

void Enemy2::AnimeControl()
{
	// �A�j���[�V�����Ɋւ��鏈�����L�q (����͋�)
}



//�O�U�P�Q
void Enemy2::SetDamageBoost(bool enable)
{
	damage_boost = enable;
}