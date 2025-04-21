#ifndef ENEMY_H_
#define ENEMY_H_

class Enemy
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

#endif // ENEMY_H_

