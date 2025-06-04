#pragma once
#include "../GameBase.h"

class Enemy : public GameBase
{
public:
	Enemy();
	~Enemy();

	// GameBase �̉��z���\�b�h���I�[�o�[���C�h
	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;
	void OnHitCollision(GameBase* hit_object) override;


private:
	void Movement();
	void AnimeControl();

	int enemy_x;
	int enemy_y;
	int size_x_;
	int size_y_;
	unsigned int color_;

	int hp_ = 3;             //����HP�i�D���Ȑ��ɒ����j
};

