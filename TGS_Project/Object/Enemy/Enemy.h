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

	////�ړ����x
	//int speed = -4;
	////�ړ���
	//int move_x = 0

private:
	void Movement();
	void AnimeControl();

	int enemy_x;
	int enemy_y;
	int size_x_;
	int size_y_;
	unsigned int color_;

	int hp;             //����HP�i�D���Ȑ��ɒ����j

	//0612
public:
	void SetDamageBoost(bool enable) override;

	// �A�j���[�V�����֌W
	int zonbi_walk[10];
	int zonbi_attack[5];
	
	int zonbi_walk_index;
	int zonbi_attack_index;

	//0626
	int zonbi_die_index;
	int zonbi_die[5];

	int animation_count;
	int zonbi_image;

	int deathSE = -1;  // ���S��

//private:
	bool damage_boost;
	bool is_attacking = false; // �U�����t���O��ǉ�

public:
	int GetAttackPower() const { return attack_power_; }
private:
	int attack_power_ = 10;  // ��F�f�t�H���g�U����
};

