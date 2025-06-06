#pragma once

#include <vector>
#include "../../Object/Bullet/Bullet.h"
#include "../GameBase.h"
#include "../../Utility/Vector2D.h"

class BulletAim : public GameBase
{
public:
    BulletAim();
    ~BulletAim();

    // GameBase の仮想メソッドをオーバーライド
    void Initialize() override;                                 // 初期化
    void Update(float delta_second) override;                   // 更新
    void Draw(const Vector2D& screen_offset) const override;    // 描画
    void Finalize() override;                                   // 終了処理

private:
    void Movement(float delta_second);// 移動処理
    void AnimeControl();              // アニメーション制御

    // メンバ変数 
    Vector2D location;   // Aim の位置
    int Aim_Image;       // Aim画像
};