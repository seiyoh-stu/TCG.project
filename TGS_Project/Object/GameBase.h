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

};