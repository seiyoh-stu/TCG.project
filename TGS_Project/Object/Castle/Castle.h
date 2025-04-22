#pragma once
#include "../GameBase.h"
class Castle : public GameBase
{


public:
	Castle();
	~Castle();
    virtual void Initialize();
    virtual void Update(float delta_second);
    virtual void Draw(const Vector2D& screen_offset) const;
    virtual void Finalize();
    //virtual void OnHitCollision(GameBase* hit_object);
};

