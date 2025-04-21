#include "Enemy.h"
#include"DxLib.h"

Enemy::Enemy() :
	pos_x_(550), // 初期位置X座標
	pos_y_(350), // 初期位置Y座標
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

void Enemy::Update()
{
	Movement();
	AnimeControl();

}

void Enemy::Draw()
{
	DrawBox(pos_x_, pos_y_, pos_x_ + size_x_, pos_y_ + size_y_, color_, TRUE);
}
void Enemy::Finalize()
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
	if (pos_x_ >= 100)
	{
		move_x -= speed;
	}

	pos_x_ += move_x;
} 

void Enemy::AnimeControl()
{
	// アニメーションに関する処理を記述 (今回は空)
}