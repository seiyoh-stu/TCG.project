#pragma once

class Bullet
{
public:
    Bullet(); // �f�t�H���g�R���X�g���N�^
    void Initialize(int x, int y); // ����������
    void Update();
    void Draw() const;
    bool IsActive() const;
    int GetX() const { return x_; }
    int GetY() const { return y_; }
    void Deactivate() { is_active_ = false; }


private:
    int x_;
    int y_;
    int speed_;
    bool is_active_;
};
