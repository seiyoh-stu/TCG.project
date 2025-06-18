#pragma once

#include"../Utility/Vector2D.h"
#include "../Utility/Collision.h"

class GameBase
{
protected:
	Vector2D location;
	Collision collision;
	int image;
	unsigned char z_layer;
	bool is_mobility;
	bool filp_flag;
	bool hit_flag;
	class Player* player;

    //移動速度
    int speed = -2;
    //移動量
    int move_x = 0;

    //移動速度
    int speed2 = -2;
    //移動量
    int move_x2 = 0;

    //移動速度
    int speed3 = -4;
    //移動量
    int move_x3 = 0;

    //移動速度
    int speed4 = -2;
    //移動量
    int move_x4 = 0;


public:
    bool is_dead_ = false;   //死亡フラグ

    virtual int GetAttackPower() const { return 0; } // デフォルトは攻撃力0


public:
    virtual void Initialize();
    virtual void Update(float delta_second);
    virtual void Draw(const Vector2D& screen_offset) const;
    virtual void Finalize();
    virtual void OnHitCollision(GameBase* hit_object);
    void Set_Hitflag(bool flag);
    const Vector2D& GetLocation() const;
    void SetLocation(const Vector2D location);
    const Collision& GetCollision() const;
    unsigned char GetZLayer() const;
    bool GetMobility() const;
    Vector2D GetBoxSize() const;
    bool IsDead() const;


    //追加0612ーーーーー
private:
    static bool damage_boost; // ★全体フラグとして追加

public:
    virtual void SetDamageBoost(bool enable);

    //までーーーーーーーーーーー

    void SetEScroll(float scro);

    float scroll;
};