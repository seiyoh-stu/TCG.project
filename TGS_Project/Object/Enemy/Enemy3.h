#pragma once
#include "../GameBase.h"

class Enemy3 : public GameBase
{
public:
	Enemy3();
	~Enemy3();

	// GameBase �̉��z���\�b�h���I�[�o�[���C�h
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

	int hp;             //����HP�i�D���Ȑ��ɒ����j

	//0612
public:
	void SetDamageBoost(bool enable) override;
//private:

	// �A�j���[�V�����֌W
	int zonbi3_walk[10];
	int zonbi3_attack[4];

	//0626
	int zonbi_die_index;
	int zonbi_die[5];


	int zonbi3_walk_index;
	int zonbi3_attack_index;
	int animation3_count;
	int zonbi3_image;

	//int deathSE = -1;  // ���S��


	bool damage_boost;
	bool is_attacking3 = false; // �U�����t���O��ǉ�

public:
	int GetAttackPower() const { return attack_power_; }
private:
	int attack_power_ = 30;  // ��F�f�t�H���g�U����
};

