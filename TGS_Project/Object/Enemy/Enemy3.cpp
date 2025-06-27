#include "Enemy3.h"
#include"../../Object/GameObjectManager.h"
#include"../../Utility/ScoreManager.h"
#include"DxLib.h"
#include "../../Utility/ResourceManager.h"

#define MAX_HP 5

Enemy3::Enemy3() :
	enemy3_x(650), // 初期位置X座標
	enemy3_y(300), // 初期位置Y座標
	size3_x_(64),  // 四角の幅
	size3_y_(64),  // 四角の高さ
	zonbi3_walk_index(0), animation3_count(0)
{

}

Enemy3::~Enemy3()
{

}

void Enemy3::Initialize()
{
	collision.object_type = eEnemy;
	collision.box_size = 64;
	collision.hit_object_type.push_back(eBullet);
	collision.hit_object_type.push_back(eCastle);

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> walk3_frames = rm->GetImages("Resource/Images/Enemy/zombie_5/Walk.png", 10, 10, 1, 96, 96);
	std::vector<int> attack3_frames = rm->GetImages("Resource/Images/Enemy/zombie_5/Attack_1.png", 4, 4, 1, 96, 96);
	std::vector<int> die_frames = rm->GetImages("Resource/Images/Enemy/zombie_5/Dead.png", 5, 5, 1, 96, 96);


	for (int i = 0; i < 10; ++i)
	{
		zonbi3_walk[i] = walk3_frames[i];
	}

	for (int i = 0; i < 4; ++i)
	{
		zonbi3_attack[i] = attack3_frames[i];
	}

	for (int i = 0; i < 5; ++i)
	{
		zonbi_die[i] = die_frames[i];
	}


	zonbi3_image = zonbi3_walk[0];  // 最初のアニメフレーム

	zonbi3_walk_index = 0;
	zonbi3_attack_index = 0;
	animation3_count = 0;

	location.x = enemy3_x;
	location.y = enemy3_y;

	hp = MAX_HP;

	//0626
	

	zonbi_die_index = 4;

	/*deathSE = LoadSoundMem("Resource/Sounds/ゾンビ3.mp3");
	if (deathSE != -1)
	{
		ChangeVolumeSoundMem(250, deathSE);
	}*/

}

void Enemy3::Update(float delta_second)
{
	Movement();
	AnimeControl();

}

void Enemy3::Draw(const Vector2D& screen_offset) const
{
	//DrawBox(enemy_x, enemy_y, enemy_x + size_x_, enemy_y + size_y_, color_, TRUE);
	//DrawBox(location.x - collision.box_size.x, location.y - collision.box_size.y, location.x + collision.box_size.x, location.y + collision.box_size.y, color3_, TRUE);

	DrawRotaGraph(location.x, location.y - 40, 2.0f, 0.0f, zonbi3_image, TRUE);

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
void Enemy3::Finalize()
{
	/*if (deathSE != -1)
	{
		DeleteSoundMem(deathSE);
	}*/

}


void Enemy3::OnHitCollision(GameBase* hit_object)
{
	// 死亡済みの場合は何も処理しない
	if (is_dead_) return;

	if (hit_object->GetCollision().object_type == eBullet)
	{
		int damage = 1;
		if (damage_boost) damage = 2;
		hp -= damage;

		if (hp <= 0 && !is_dead_)
		{
			hp = 0;
			is_dead_ = true;
			is_dead_anim_played_ = true;
			zonbi_die_index = 4;
			animation3_count = 0;
			ScoreManager::GetInstance()->AddScore(200);
			// Destroyはアニメ再生終了後に呼ぶ
			// ここで効果音を鳴らす
			/*if (deathSE != -1)
			{
				PlaySoundMem(deathSE, DX_PLAYTYPE_BACK);
			}*/
		}
	}
	if (hit_object->GetCollision().object_type == eCastle)
	{
		speed3 = 0;
		is_attacking3 = true;
	}
}


//移動処理
void Enemy3::Movement()
{
	location.x += speed3 - scroll;
}

void Enemy3::AnimeControl()
{
	animation3_count++;


	// 死亡アニメ再生中
	if (is_dead_anim_played_)
	{
		if (animation3_count >= 10)
		{
			animation3_count = 0;
			zonbi_die_index--;
			if (zonbi_die_index < 0)
			{
				// 死アニメ5枚目が終わったら即Destroy
				is_dead_anim_played_ = false;
				GameBaseManager::GetInstance()->DestroyGameBase(this);
				return;
			}
			zonbi3_image = zonbi_die[zonbi_die_index];
		}
		return;
	}


	if (is_attacking3) // 攻撃中の場合
	{
		if (animation3_count >= 10)
		{
			animation3_count = 0;
			// 攻撃アニメーションフレームを1つ進める（5枚ループ）
			zonbi3_attack_index = (zonbi3_attack_index + 1) % 4;
			zonbi3_image = zonbi3_attack[zonbi3_attack_index]; // 現在の画像を攻撃用に更新
		}
	}
	else // 通常の歩行状態
	{
		if (animation3_count >= 10)
		{
			animation3_count = 0;
			// 歩行アニメーションフレームを1つ進める（10枚ループ）
			zonbi3_walk_index = (zonbi3_walk_index + 1) % 10;
			zonbi3_image = zonbi3_walk[zonbi3_walk_index]; // 現在の画像を歩行用に更新
		}
	}
}


//０６１２
void Enemy3::SetDamageBoost(bool enable)
{
	damage_boost = enable;
}