#pragma once
#include "../GameBase.h"

class Enemy4 : public GameBase
{
public:
	Enemy4();
	~Enemy4();

	// GameBase の仮想メソッドをオーバーライド
	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;
	void OnHitCollision(GameBase* hit_object) override;

private:
	void Movement();
	void AnimeControl();

	int enemy4_x;
	int enemy4_y;
	int size4_x_;
	int size4_y_;
	unsigned int color4_;

	int hp;             //初期HP（好きな数に調整）
};

