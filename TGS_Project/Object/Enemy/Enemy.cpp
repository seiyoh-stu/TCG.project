#include "Enemy.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"
#include "../../Utility/ResourceManager.h"

#define MAX_HP 10  // 6�Ȃ�3���Ŏ���



//0612
//bool Enemy::damage_boost = false;

Enemy::Enemy() :
	enemy_x(550), // �����ʒuX���W
	enemy_y(580), // �����ʒuY���W
	size_x_(64),  // �l�p�̕�
	size_y_(64),  // �l�p�̍���
	zonbi_walk_index(0), animation_count(0)
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
	collision.hit_object_type.push_back(eCastle);

	is_dead_ = false; // ���S�t���O������

	hp = MAX_HP;


	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> walk_frames = rm->GetImages("Resource/Images/Enemy/Zombie_1/Walk.png", 10, 10, 1, 128, 128);
	std::vector<int> attack_frames = rm->GetImages("Resource/Images/Enemy/Zombie_1/Attack.png", 5, 5, 1, 128, 128);


	for (int i = 0; i < 10; ++i) 
	{
		zonbi_walk[i] = walk_frames[i];
	}

	for (int i = 0; i < 5;++i)
	{
		zonbi_attack[i] = attack_frames[i];
	}


	zonbi_image = zonbi_walk[0];  // �ŏ��̃A�j���t���[��

	zonbi_walk_index = 0;
	zonbi_attack_index = 0;
	animation_count = 0;


	location.x = enemy_x;
	location.y = enemy_y;
}

void Enemy::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy::Draw(const Vector2D& screen_offset) const
{

	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	/*DrawRotaGraph(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, zonbi_image, TRUE);*/
	DrawRotaGraph(location.x, location.y, 2.0f, 0.0f, zonbi_image, TRUE);

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
		speed = 0;
		is_attacking = true;
	}
}




//�ړ�����
void Enemy::Movement()
{
	////�ړ����x
	//const int speed = 4;
	////�ړ���
	//int move_x = 0;

	// �E�̒[�����ɒ����ƁA���̒[�����Ɉړ�����
	//if (location.x >= 0)
	//{
	//	move_x -= speed;
	//}



	location.x += speed - scroll;
} 

void Enemy::AnimeControl()
{
	animation_count++;

	if (is_attacking) // �U�����̏ꍇ
	{
		if (animation_count >= 10)
		{
			animation_count = 0;
			// �U���A�j���[�V�����t���[����1�i�߂�i5�����[�v�j
			zonbi_attack_index = (zonbi_attack_index + 1) % 5;
			zonbi_image = zonbi_attack[zonbi_attack_index]; // ���݂̉摜���U���p�ɍX�V
		}
	}
	else // �ʏ�̕��s���
	{
		if (animation_count >= 10)
		{
			animation_count = 0;
			// ���s�A�j���[�V�����t���[����1�i�߂�i10�����[�v�j
			zonbi_walk_index = (zonbi_walk_index + 1) % 10;
			zonbi_image = zonbi_walk[zonbi_walk_index]; // ���݂̉摜����s�p�ɍX�V
		}
	}
}

void Enemy::SetDamageBoost(bool enable)
{
	damage_boost = enable;
}