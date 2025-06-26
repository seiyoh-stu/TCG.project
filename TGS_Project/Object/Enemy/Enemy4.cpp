#include "Enemy4.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"
#include "../../Utility/ResourceManager.h"

#define MAX_HP 50

Enemy4::Enemy4() :
	enemy4_x(700), // �����ʒuX���W
	enemy4_y(580), // �����ʒuY���W
	size4_x_(64),  // �l�p�̕�
	size4_y_(64),  // �l�p�̍���
	zonbi4_walk_index(0), animation4_count(0)
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
	collision.hit_object_type.push_back(eCastle);

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> walk4_frames = rm->GetImages("Resource/Images/Enemy/Zombie_3/Walk.png", 10, 10, 1, 128, 128);
	std::vector<int> attack4_frames = rm->GetImages("Resource/Images/Enemy/Zombie_3/Walk.png", 4, 4, 1, 128, 128);



	for (int i = 0; i < 10; ++i)
	{
		zonbi4_walk[i] = walk4_frames[i];
	}

	for (int i = 0; i < 4; ++i)
	{
		zonbi4_attack[i] = attack4_frames[i];
	}


	zonbi4_image = zonbi4_walk[0];  // �ŏ��̃A�j���t���[��

	zonbi4_walk_index = 0;
	zonbi4_attack_index = 0;
	animation4_count = 0;

	location.x = enemy4_x;
	location.y = enemy4_y;

	hp = MAX_HP;

	//0626
	std::vector<int> die_frames = rm->GetImages("Resource/Images/Enemy/Zombie_3/Dead.png", 5, 5, 1, 128, 128);

	for (int i = 0; i < 5; ++i)
	{
		zonbi_die[i] = die_frames[i];
	}

	zonbi_die_index = 4;
}

void Enemy4::Update(float delta_second)
{
	Movement();
	AnimeControl();

}






void Enemy4::Draw(const Vector2D& screen_offset) const
{
	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	DrawRotaGraph(location.x, location.y - 40, 2.0f, 0.0f, zonbi4_image, TRUE);


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
void Enemy4::Finalize()
{

}


void Enemy4::OnHitCollision(GameBase* hit_object)
{
	// ���S�ς݂̏ꍇ�͉����������Ȃ�
	if (is_dead_) return;

	if (hit_object->GetCollision().object_type == eBullet)
	{
		int damage = 1;
		if (damage_boost) damage = 2;
		hp -= damage;

		if (hp <= 0 && !is_dead_)
		{
			hp = 0;
			is_dead_ = true;
			is_dead_anim_played_ = true;
			zonbi_die_index = 4;
			animation4_count = 0;
			ScoreManager::GetInstance()->AddScore(200);
			// Destroy�̓A�j���Đ��I����ɌĂ�
		}
	}
	if (hit_object->GetCollision().object_type == eCastle)
	{
		speed4 = 0;
		is_attacking4 = true;
	}
}


//�ړ�����
void Enemy4::Movement()
{
	location.x += speed4 - scroll;
}

void Enemy4::AnimeControl()
{
	animation4_count++;

	// ���S�A�j���Đ���
	if (is_dead_anim_played_)
	{
		if (animation4_count >= 10)
		{
			animation4_count = 0;
			zonbi_die_index--;
			if (zonbi_die_index < 0)
			{
				// ���A�j��5���ڂ��I������瑦Destroy
				is_dead_anim_played_ = false;
				GameBaseManager::GetInstance()->DestroyGameBase(this);
				return;
			}
			zonbi4_image = zonbi_die[zonbi_die_index];
		}
		return;
	}

	if (is_attacking4) // �U�����̏ꍇ
	{
		if (animation4_count >= 10)
		{
			animation4_count = 0;
			// �U���A�j���[�V�����t���[����1�i�߂�i5�����[�v�j
			zonbi4_attack_index = (zonbi4_attack_index + 1) % 4;
			zonbi4_image = zonbi4_attack[zonbi4_attack_index]; // ���݂̉摜���U���p�ɍX�V
		}
	}
	else // �ʏ�̕��s���
	{
		if (animation4_count >= 10)
		{
			animation4_count = 0;
			// ���s�A�j���[�V�����t���[����1�i�߂�i10�����[�v�j
			zonbi4_walk_index = (zonbi4_walk_index + 1) % 10;
			zonbi4_image = zonbi4_walk[zonbi4_walk_index]; // ���݂̉摜����s�p�ɍX�V
		}
	}
}

//�O�U�P�Q
void Enemy4::SetDamageBoost(bool enable)
{
	damage_boost = enable;
}