#include "Enemy3.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"
#include "../../Utility/ResourceManager.h"

#define MAX_HP 2

Enemy3::Enemy3() :
	enemy3_x(650), // èâä˙à íuXç¿ïW
	enemy3_y(300), // èâä˙à íuYç¿ïW
	size3_x_(64),  // éläpÇÃïù
	size3_y_(64),  // éläpÇÃçÇÇ≥
	zonbi3_walk_index(0), animation3_count(0)
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
	collision.hit_object_type.push_back(eCastle);

	ResourceManager* rm = ResourceManager::GetInstance();
	// std::vector<int> walk3_frames = rm->GetImages("Resource/Images/Enemy/Zombie_2/Walk.png", 10, 10, 1, 128, 128);
	std::vector<int> walk3_frames = rm->GetImages("Resource/Images/Enemy/zombie_5/Walk.png", 10, 10, 1, 96, 96);


	for (int i = 0; i < 10; ++i)
	{
		zonbi3_animation[i] = walk3_frames[i];
	}

	zonbi3_image = zonbi3_animation[0];  // ç≈èâÇÃÉAÉjÉÅÉtÉåÅ[ÉÄ

	location.x = enemy3_x;
	location.y = enemy3_y;

	hp = MAX_HP;
}

void Enemy3::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy3::Draw(const Vector2D& screen_offset) const
{
	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	//DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color3_, TRUE);

	DrawRotaGraph(location.x, location.y, 2.0f, 0.0f, zonbi3_image, TRUE);

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
void Enemy3::Finalize()
{

}


void Enemy3::OnHitCollision(GameBase* hit_object)
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
		speed3 = 0;
	}
}


//à⁄ìÆèàóù
void Enemy3::Movement()
{
	location.x += speed3 - scroll;
}

void Enemy3::AnimeControl()
{
	animation3_count++;
	if (animation3_count >= 10)
	{
		animation3_count = 0;
		zonbi3_walk_index = (zonbi3_walk_index + 1) % 10;
		zonbi3_image = zonbi3_animation[zonbi3_walk_index];
	}
}

//ÇOÇUÇPÇQ
void Enemy3::SetDamageBoost(bool enable)
{
	damage_boost = enable;
}