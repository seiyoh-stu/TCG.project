#include "Enemy3.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"

#define MAX_HP 2  // 6なら3発で死ぬ

Enemy3::Enemy3() :
	enemy3_x(650), // 初期位置X座標
	enemy3_y(300), // 初期位置Y座標
	size3_x_(64),  // 四角の幅
	size3_y_(64),  // 四角の高さ
	color3_(GetColor(0, 0, 255)) // 四角の色 (赤)
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
	DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color3_, TRUE);

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
		// HPを減らす
		hp--;

		// HPが0以下ならオブジェクトを削除
		if (hp <= 0)
		{
			is_dead_ = true;

			GameBaseManager* gbmm = GameBaseManager::GetInstance();
			gbmm->DestroyGameBase(this);

			// スコア加算（倒した瞬間のみ）
			ScoreManager* score = ScoreManager::GetInstance();
			score->AddScore(200); // 200点（必要に応じて調整）
		};
	}
}
//移動処理
void Enemy3::Movement()
{
	//移動速度
	const int speed = 10;
	//移動量
	int move_x = 0;

	// 右の端っこに着くと、左の端っこに移動する
	if (location.x >= 10)
	{
		move_x -= speed;
	}

	location.x += move_x;
}

void Enemy3::AnimeControl()
{
	// アニメーションに関する処理を記述 (今回は空)
}

//void OnHitCollision(GameBase* hit_object)
//{
//
//}