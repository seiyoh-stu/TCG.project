#pragma once
#include "../GameBase.h"

class Enemy4 : public GameBase
{
public:
	Enemy4();
	~Enemy4();

	// GameBase �̉��z���\�b�h���I�[�o�[���C�h
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

	int hp;             //����HP�i�D���Ȑ��ɒ����j



	//0612
public:
	void SetDamageBoost(bool enable) override;

	// �A�j���[�V�����֌W
	int zonbi4_walk[10];
	int zonbi4_attack[4];


	int zonbi4_walk_index;
	int zonbi4_attack_index;
	int animation4_count;
	int zonbi4_image;

	//private:
	bool damage_boost;
	bool is_attacking4 = false; // �U�����t���O��ǉ�
};

