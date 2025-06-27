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
	int zonbi2_walk[12];
	int zonbi2_attack[10];

	//0626
	int zonbi_die_index;
	int zonbi_die[5];


	int zonbi2_walk_index;
	int zonbi2_attack_index;
	int animation2_count;
	int zonbi2_image;

	int deathSE = -1;  // 死亡音

//private:
	bool damage_boost;
	bool is_attacking2 = false; // 攻撃中フラグを追加

public:
	int GetAttackPower() const { return attack_power_; }
private:
	int attack_power_ = 20;  // 例：デフォルト攻撃力
};

