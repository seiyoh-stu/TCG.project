#include "Enemy.h"
#include"DxLib.h"

Enemy::Enemy() :
	enemy_x(550), // 初期位置X座標
	enemy_y(350), // 初期位置Y座標
	size_x_(64),  // 四角の幅
	size_y_(64),  // 四角の高さ
	color_(GetColor(255, 0, 0)) // 四角の色 (赤)
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{

}

void Enemy::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy::Draw(const Vector2D& screen_offset) const
{
	DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
}
void Enemy::Finalize()
{

}
void Enemy::OnHitCollision(GameBase* hit_object)
{

}
//移動処理
void Enemy::Movement()
{
	//移動速度
	const int speed = 2;
	//移動量
	int move_x = 0;

	// 右の端っこに着くと、左の端っこに移動する
	if (enemy_x >= 100)
	{
		move_x -= speed;
	}

	enemy_x += move_x;
} 

void Enemy::AnimeControl()
{
	// アニメーションに関する処理を記述 (今回は空)
}

void OnHitCollision(GameBase* hit_object)
{

}