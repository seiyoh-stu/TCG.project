#pragma once
#include "../GameBase.h"

class Enemy2 : public GameBase
{
public:
	Enemy2();
	~Enemy2();

	// GameBase の仮想メソッドをオーバーライド
	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;
	void OnHitCollision(GameBase* hit_object) override;

private:
	void Movement();
	void AnimeControl();

	int enemy2_x;
	int enemy2_y;
	int size2_x_;
	int size2_y_;
	unsigned int color2_;

	int hp;             //初期HP（好きな数に調整）

	//0612
public:
	void SetDamageBoost(bool enable) override;

	// アニメーション関係
	int zonbi_animation[12];
	int zonbi_walk_index;
	int animation_count;
	int zonbi_image;
	int attack_frames;

	/*int zonbi_walk_animation[12];
	int zonbi_attack_animation[10];*/

//private:
	bool damage_boost;
};

