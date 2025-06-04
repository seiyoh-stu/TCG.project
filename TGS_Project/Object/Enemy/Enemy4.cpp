#include "Enemy4.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"

Enemy4::Enemy4() :
	enemy4_x(700), // 初期位置X座標
	enemy4_y(500), // 初期位置Y座標
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
		is_dead_ = true; // 死亡フラグ立てる

		static bool check_hit = false;

		if (check_hit == false)
		{
			// スコアを加算する
			ScoreManager* score = ScoreManager::GetInstance();
			score->AddScore(200); // 敵を倒すと100点加算（適宜調整）
			check_hit = true;
		}

		GameBaseManager* gbmm = GameBaseManager::GetInstance();
		gbmm->DestroyGameBase(this);
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
	if (location.x >= 100)
	{
		move_x -= speed;
	}

	location.x += move_x;
}

void Enemy4::AnimeControl()
{
	// アニメーションに関する処理を記述 (今回は空)
}

//void OnHitCollision(GameBase* hit_object)
//{
//
//}