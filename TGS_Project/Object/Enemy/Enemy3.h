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
};

