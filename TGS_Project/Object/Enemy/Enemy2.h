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
};

