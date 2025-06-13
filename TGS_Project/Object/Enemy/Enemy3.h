#pragma once
#include "../GameBase.h"

class Enemy3 : public GameBase
{
public:
	Enemy3();
	~Enemy3();

	// GameBase の仮想メソッドをオーバーライド
	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;
	void OnHitCollision(GameBase* hit_object) override;

private:
	void Movement();
	void AnimeControl();

	int enemy3_x;
	int enemy3_y;
	int size3_x_;
	int size3_y_;
	unsigned int color3_;

	int hp;             //初期HP（好きな数に調整）

	//0612
public:
	void SetDamageBoost(bool enable) override;
//private:

	int zonbi3_animation[10];
	int zonbi3_walk_index;
	int animation3_count;
	int zonbi3_image;


	bool damage_boost;
};

