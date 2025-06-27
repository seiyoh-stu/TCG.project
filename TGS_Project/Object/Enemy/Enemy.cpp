#include "Enemy.h"
#include "../../Object/GameObjectManager.h"
#include "../../Utility/ScoreManager.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"

#define MAX_HP 60

Enemy::Enemy() :
    enemy_x(550),
    enemy_y(580),
    size_x_(64),
    size_y_(64),
    zonbi_walk_index(0), animation_count(0)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
    collision.object_type = eEnemy;
    collision.box_size = 64;
    collision.hit_object_type.push_back(eBullet);
    collision.hit_object_type.push_back(eCastle);

    is_dead_ = false;
    is_dead_anim_played_ = false;
    hp = MAX_HP;

    ResourceManager* rm = ResourceManager::GetInstance();
    std::vector<int> walk_frames = rm->GetImages("Resource/Images/Enemy/Zombie_1/Walk.png", 10, 10, 1, 128, 128);
    std::vector<int> attack_frames = rm->GetImages("Resource/Images/Enemy/Zombie_1/Attack.png", 5, 5, 1, 128, 128);
    

    for (int i = 0; i < 10; ++i)
        zonbi_walk[i] = walk_frames[i];
    for (int i = 0; i < 5; ++i)
        zonbi_attack[i] = attack_frames[i];
    

    zonbi_image = zonbi_walk[0];
    zonbi_walk_index = 0;
    zonbi_attack_index = 0;
   
    animation_count = 0;
    location.x = enemy_x;
    location.y = enemy_y;
    

    //0626
    std::vector<int> die_frames = rm->GetImages("Resource/Images/Enemy/Zombie_1/Dead.png", 5, 5, 1, 128, 128);

    for (int i = 0; i < 5; ++i)
    {
        zonbi_die[i] = die_frames[i];
    }
        
    zonbi_die_index = 4;

    /*deathSE = LoadSoundMem("Resource/Sounds/ゾンビ1.mp3");
    if (deathSE != -1)
    {
        ChangeVolumeSoundMem(200, deathSE);
    }*/
}

void Enemy::Update(float delta_second)
{
    // 死亡アニメ再生中の場合、アニメ制御のみ行う
    if (is_dead_anim_played_)
    {
        AnimeControl();
        return;
    }

    Movement();
    AnimeControl();
}

void Enemy::Draw(const Vector2D& screen_offset) const
{
    DrawRotaGraph(location.x, location.y - 40, 2.0f, 0.0f, zonbi_image, TRUE);

    // 死亡中はHPバーを描画しない
    if (is_dead_) return;

    // HPバー描画
    Vector2D hp_bar = location;
    hp_bar -= Vector2D(25.0f, 60.0f);
    int color = GetColor(7, 255, 0);

    if (hp <= (MAX_HP / 2))
        color = GetColor(255, static_cast<int>(255 * static_cast<float>(hp) / MAX_HP), 0);
    else
        color = GetColor(7 + 2 * static_cast<int>(248 * (1 - static_cast<float>(hp) / MAX_HP)), 255, 0);

    DrawBoxAA(hp_bar.x, hp_bar.y, hp_bar.x + 50, hp_bar.y + 5.0f, 0x000000, TRUE);
    DrawBoxAA(hp_bar.x, hp_bar.y, hp_bar.x + (50 * (static_cast<float>(hp) / MAX_HP)), hp_bar.y + 5.0f, color, TRUE);
    DrawBoxAA(hp_bar.x, hp_bar.y, hp_bar.x + 50, hp_bar.y + 5.0f, 0x8f917f, FALSE);
}

void Enemy::Finalize()
{
    /*if (deathSE != -1)
    {
        DeleteSoundMem(deathSE);
    }*/
}

void Enemy::OnHitCollision(GameBase* hit_object)
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
            animation_count = 0;
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
        speed = 0;
        is_attacking = true;
    }
}

void Enemy::Movement()
{
    //（必要な移動処理をここに記載してください）
    location.x += speed - scroll;
}

void Enemy::AnimeControl()
{
    animation_count++;

    // 死亡アニメ再生中
    if (is_dead_anim_played_)
    {
        if (animation_count >= 10)
        {
            animation_count = 0;
            zonbi_die_index--;
            if (zonbi_die_index <0)
            {
                // 死アニメ5枚目が終わったら即Destroy
                is_dead_anim_played_ = false;
                GameBaseManager::GetInstance()->DestroyGameBase(this);
                return;
            }
            zonbi_image = zonbi_die[zonbi_die_index];
        }
        return;
    }

    // 歩行・攻撃アニメーション
    if (is_attacking)
    {
        if (animation_count >= 10)
        {
            animation_count = 0;
            zonbi_attack_index = (zonbi_attack_index + 1) % 5;
            zonbi_image = zonbi_attack[zonbi_attack_index];
        }
    }
    else
    {
        if (animation_count >= 10)
        {
            animation_count = 0;
            zonbi_walk_index = (zonbi_walk_index + 1) % 10;
            zonbi_image = zonbi_walk[zonbi_walk_index];
        }
    }
}

void Enemy::SetDamageBoost(bool enable)
{
    damage_boost = enable;
}
