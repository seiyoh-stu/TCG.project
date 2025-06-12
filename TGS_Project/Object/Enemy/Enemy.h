#pragma once
#include "../GameBase.h"

class Enemy : public GameBase
{
public:
	Enemy();
	~Enemy();

	// GameBase の仮想メソッドをオーバーライド
	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;
	void OnHitCollision(GameBase* hit_object) override;

	////移動速度
	//int speed = -4;
	////移動量
	//int move_x = 0;

private:
	void Movement();
	void AnimeControl();

	int enemy_x;
	int enemy_y;
	int size_x_;
	int size_y_;
	unsigned int color_;

	int hp;             //初期HP（好きな数に調整）

	//0612
public:
	void SetDamageBoost(bool enable) override;
//private:
	bool damage_boost;
};

