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

    //�ړ����x
    int speed = -2;
    //�ړ���
    int move_x = 0;

    //�ړ����x
    int speed2 = -2;
    //�ړ���
    int move_x2 = 0;

    //�ړ����x
    int speed3 = -4;
    //�ړ���
    int move_x3 = 0;

    //�ړ����x
    int speed4 = -2;
    //�ړ���
    int move_x4 = 0;


public:
    bool is_dead_ = false;   //���S�t���O

    virtual int GetAttackPower() const { return 0; } // �f�t�H���g�͍U����0


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


    //�ǉ�0612�[�[�[�[�[
private:
    static bool damage_boost; // ���S�̃t���O�Ƃ��Ēǉ�

public:
    virtual void SetDamageBoost(bool enable);

    //�܂Ł[�[�[�[�[�[�[�[�[�[�[

    void SetEScroll(float scro);

    float scroll;
};