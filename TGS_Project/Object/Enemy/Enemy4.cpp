#include "Enemy4.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"

#define MAX_HP 26  // 6�Ȃ�3���Ŏ���

Enemy4::Enemy4() :
	enemy4_x(700), // �����ʒuX���W
	enemy4_y(580), // �����ʒuY���W
	size4_x_(64),  // �l�p�̕�
	size4_y_(64),  // �l�p�̍���
	color4_(GetColor(255, 255, 255)) // �l�p�̐F (��)
{

}

Enemy4::~Enemy4()
{

}

void Enemy4::Initialize()
{
	collision.object_type = eEnemy;
	collision.box_size = 64;
	collision.hit_object_type.push_back(eBullet);

	hp = MAX_HP;
}

void Enemy4::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy4::Draw(const Vector2D& screen_offset) const
{
	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color4_, TRUE);


	Vector2D hp_bar = location;
	hp_bar -= Vector2D(25.0f, 60.0f);

	int color = GetColor(7, 255, 0);

	if (hp <= (MAX_HP / 2))
	{
		color = GetColor(255, static_cast<int>(255 * static_cast<float>(hp) / MAX_HP), 0);
	}
	else
	{
		color = GetColor(7 + 2 * static_cast<int>(248 * (1 - static_cast<float>(hp) / MAX_HP)), 255, 0);
	}
	DrawBoxAA(hp_bar.x, hp_bar.y, hp_bar.x + 50, hp_bar.y + 5.0f,
		0x000000, TRUE);
	DrawBoxAA(hp_bar.x, hp_bar.y, hp_bar.x + (50 * (static_cast<float>(hp) / MAX_HP)), hp_bar.y + 5.0f,
		color, TRUE);
	DrawBoxAA(hp_bar.x, hp_bar.y, hp_bar.x + 50, hp_bar.y + 5.0f,
		0x8f917f, FALSE);

}
void Enemy4::Finalize()
{

}
void Enemy4::OnHitCollision(GameBase* hit_object)
{
	if (hit_object->GetCollision().object_type == eBullet)
	{

		// HP�����炷
		hp--;

		// HP��0�ȉ��Ȃ�I�u�W�F�N�g���폜
		if (hp <= 0)
		{
			is_dead_ = true;

			GameBaseManager* gbmm = GameBaseManager::GetInstance();
			gbmm->DestroyGameBase(this);

			// �X�R�A���Z�i�|�����u�Ԃ̂݁j
			ScoreManager* score = ScoreManager::GetInstance();
			score->AddScore(600); // 600�_�i�K�v�ɉ����Ē����j
		}

		//is_dead_ = true; // ���S�t���O���Ă�

		//static bool check_hit = false;

		//if (check_hit == false)
		//{
		//	// �X�R�A�����Z����
		//	ScoreManager* score = ScoreManager::GetInstance();
		//	score->AddScore(200); // �G��|����100�_���Z�i�K�X�����j
		//	check_hit = true;
		//}

		//GameBaseManager* gbmm = GameBaseManager::GetInstance();
		//gbmm->DestroyGameBase(this);
	}
}
//�ړ�����
void Enemy4::Movement()
{
	//�ړ����x
	const int speed = 2;
	//�ړ���
	int move_x = 0;

	// �E�̒[�����ɒ����ƁA���̒[�����Ɉړ�����
	if (location.x >= 250)
	{
		move_x -= speed;
	}

	location.x += move_x;
}

void Enemy4::AnimeControl()
{
	// �A�j���[�V�����Ɋւ��鏈�����L�q (����͋�)
}

//void OnHitCollision(GameBase* hit_object)
//{
//
//}