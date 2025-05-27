#pragma once
#include "../GameBase.h"
#include "../../Object/Player/Player.h"

class Bullet : public GameBase
{
public:
    Bullet(); // �f�t�H���g�R���X�g���N�^
    void Initialize() override; // �g�p���Ȃ��Ȃ�폜���Ă�OK
    void Initialize(int start_x, int start_y,bool flip_flag); // �� �ʒu�w��t��������
    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    void OnHitCollision(GameBase* hit_object) override;

    bool IsActive() const;
    int GetX() const { return location.x; }
    int GetY() const { return location.y; }
    void Deactivate() { is_active_ = false; }

    void GetFlipFlag(bool flag);

private:
    int speed_;
    bool is_active_;
    bool move_left_;  // �� �ǉ��A���������ǂ���

    //Player* player;
};

