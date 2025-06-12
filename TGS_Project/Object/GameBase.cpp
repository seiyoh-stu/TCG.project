#include "GameBase.h"
#include "DxLib.h"

/// <summary>
/// 初期化処理
/// </summary>
void GameBase::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void GameBase::Update(float delta_second)
{

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void GameBase::Draw(const Vector2D& screen_offset) const
{
	Vector2D graph_location = this->location - screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE, filp_flag);

}

/// <summary>
/// 終了時処理
/// </summary>
void GameBase::Finalize()
{

}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void GameBase::OnHitCollision(GameBase* hit_object)
{

}

void GameBase::Set_Hitflag(bool flag)
{
	hit_flag = flag;
}

/// <summary>
/// 位置座標取得処理
/// </summary>
/// <returns>位置座標情報</returns>
const Vector2D& GameBase::GetLocation() const
{
	return location;
}

// <summary>
/// 位置情報変更処理
/// </summary>
/// <param name="location">変更したい位置情報</param>
void GameBase::SetLocation(const Vector2D location)
{
	this->location = location;
}

/// <summary>
/// 当たり判定取得処理
/// </summary>
/// <returns>当たり判定情報</returns>
const Collision& GameBase::GetCollision() const
{
	return collision;
}
/// <summary>
/// Zレイヤー情報取得処理
/// </summary>
/// <returns>Zレイヤー情報</returns>
unsigned char GameBase::GetZLayer() const
{
	return z_layer;
}

/// <summary>
/// 可動性情報の取得処理
/// </summary>
/// <returns>可動性情報</returns>
bool GameBase::GetMobility() const
{
	return is_mobility;
}

Vector2D GameBase::GetBoxSize() const
{
	return collision.box_size;
}

bool GameBase::IsDead() const
{
	return is_dead_;
}

void GameBase::SetDamageBoost(bool enable)
{

}
