#include "Enemy4.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"
#include "../../Utility/ResourceManager.h"

#define MAX_HP 50

Enemy4::Enemy4() :
	enemy4_x(700), // èâä˙à íuXç¿ïW
	enemy4_y(580), // èâä˙à íuYç¿ïW
	size4_x_(64),  // éläpÇÃïù
	size4_y_(64),  // éläpÇÃçÇÇ≥
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



	for (int i = 0; i < 10; ++i)
	{
		zonbi4_animation[i] = walk4_frames[i];
	}

	zonbi4_image = zonbi4_animation[0];  // ç≈èâÇÃÉAÉjÉÅÉtÉåÅ[ÉÄ

	location.x = enemy4_x;
	location.y = enemy4_y;




	hp = MAX_HP;
}

void Enemy4::Update(float delta_second)
{
	Movement();
	AnimeControl();

}






void Enemy4::Draw(const Vector2D& screen_offset) const
{
	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	DrawRotaGraph(location.x, location.y, 4.0f, 0.0f, zonbi4_image, TRUE);


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
		speed4 = 0;
	}
}


//à⁄ìÆèàóù
void Enemy4::Movement()
{
	location.x += speed4 - scroll;
}

void Enemy4::AnimeControl()
{
	animation4_count++;
	if (animation4_count >= 10)
	{
		animation4_count = 0;
		zonbi4_walk_index = (zonbi4_walk_index + 1) % 10;
		zonbi4_image = zonbi4_animation[zonbi4_walk_index];
	}
}

//ÇOÇUÇPÇQ
void Enemy4::SetDamageBoost(bool enable)
{
	damage_boost = enable;
}