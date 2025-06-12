#include "Enemy4.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"

#define MAX_HP 50

Enemy4::Enemy4() :
	enemy4_x(700), // 初期位置X座標
	enemy4_y(580), // 初期位置Y座標
	size4_x_(64),  // 四角の幅
	size4_y_(64),  // 四角の高さ
	color4_(GetColor(255, 255, 255)) // 四角の色 (赤)
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
	DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color4_, TRUE);


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
}




//移動処理
void Enemy4::Movement()
{
	//移動速度
	const int speed = 2;
	//移動量
	int move_x = 0;

	// 右の端っこに着くと、左の端っこに移動する
	if (location.x >= 0)
	{
		move_x -= speed;
	}

	location.x += move_x;
}

void Enemy4::AnimeControl()
{
	// アニメーションに関する処理を記述 (今回は空)
}






//０６１２
void Enemy4::SetDamageBoost(bool enable)
{
	damage_boost = enable;
}