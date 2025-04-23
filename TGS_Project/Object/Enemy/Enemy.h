#pragma once
#include "../GameBase.h"

class Enemy : public GameBase
{
public:
	Enemy();
	~Enemy();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

private:
	void Movement();
	void AnimeControl();

	int pos_x_;
	int pos_y_;
	int size_x_;
	int size_y_;
	unsigned int color_;
};

