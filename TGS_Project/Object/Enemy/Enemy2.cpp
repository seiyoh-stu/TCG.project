#include "Enemy2.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"
#include "../../Utility/ResourceManager.h"

#define MAX_HP 10  // 6�Ȃ�3���Ŏ���

Enemy2::Enemy2() :
	enemy2_x(600), // �����ʒuX���W
	enemy2_y(580), // �����ʒuY���W
	size2_x_(64),  // �l�p�̕�
	size2_y_(64),  // �l�p�̍���
	zonbi2_walk_index(0), animation2_count(0)
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
	collision.hit_object_type.push_back(eCastle);

	is_dead_ = false; // ���S�t���O������

	hp = MAX_HP;

	int zonbi_walk_animation[12];
	int zonbi_attack_animation[10];

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> walk_frames = rm->GetImages("Resource/Images/Enemy/Zombie_4/Walk.png", 12, 12, 1, 128, 128);
	std::vector<int> attack_frames = rm->GetImages("Resource/Images/Enemy/Zombie_4/Attack.png", 10, 10, 1, 128, 128);

	for (int i = 0; i < 12; ++i)
	{
		zonbi2_walk[i] = walk_frames[i];
	}

	for (int i = 0; i < 10; ++i)
	{
		zonbi2_attack[i] = attack_frames[i];
	}


	zonbi2_image = zonbi2_walk[0];  // �ŏ��̃A�j���t���[��

	zonbi2_walk_index = 0;
	zonbi2_attack_index = 0;
	animation2_count = 0;

	location.x = enemy2_x;
	location.y = enemy2_y;
}

void Enemy2::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy2::Draw(const Vector2D& screen_offset) const
{
	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	DrawRotaGraph(location.x, location.y, 2.0f, 0.0f, zonbi2_image, TRUE);

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

	if (hit_object->GetCollision().object_type == eCastle)
	{
		speed2 = 0;
		is_attacking2 = true;
	}
}


//�ړ�����
void Enemy2::Movement()
{
	location.x += speed2 - scroll;
}

void Enemy2::AnimeControl()
{
	animation2_count++;

	if (is_attacking2) // �U�����̏ꍇ
	{
		if (animation2_count >= 12)
		{
			animation2_count = 0;
			// �U���A�j���[�V�����t���[����1�i�߂�i5�����[�v�j
			zonbi2_attack_index = (zonbi2_attack_index + 1) % 10;
			zonbi2_image = zonbi2_attack[zonbi2_attack_index]; // ���݂̉摜���U���p�ɍX�V
		}
	}
	else // �ʏ�̕��s���
	{
		if (animation2_count >= 12)
		{
			animation2_count = 0;
			// ���s�A�j���[�V�����t���[����1�i�߂�i10�����[�v�j
			zonbi2_walk_index = (zonbi2_walk_index + 1) % 12;
			zonbi2_image = zonbi2_walk[zonbi2_walk_index]; // ���݂̉摜����s�p�ɍX�V
		}
	}
}

//�O�U�P�Q
void Enemy2::SetDamageBoost(bool enable)
{
	damage_boost = enable;
}
