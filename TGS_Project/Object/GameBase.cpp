#include "GameBase.h"
#include "DxLib.h"

/// <summary>
/// ����������
/// </summary>
void GameBase::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void GameBase::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void GameBase::Draw(const Vector2D& screen_offset) const
{
	Vector2D graph_location = this->location - screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE, filp_flag);

}

/// <summary>
/// �I��������
/// </summary>
void GameBase::Finalize()
{

}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void GameBase::OnHitCollision(GameBase* hit_object)
{

}

void GameBase::Set_Hitflag(bool flag)
{
	hit_flag = flag;
}

/// <summary>
/// �ʒu���W�擾����
/// </summary>
/// <returns>�ʒu���W���</returns>
const Vector2D& GameBase::GetLocation() const
{
	return location;
}

// <summary>
/// �ʒu���ύX����
/// </summary>
/// <param name="location">�ύX�������ʒu���</param>
void GameBase::SetLocation(const Vector2D location)
{
	this->location = location;
}

/// <summary>
/// �����蔻��擾����
/// </summary>
/// <returns>�����蔻����</returns>
const Collision& GameBase::GetCollision() const
{
	return collision;
}
/// <summary>
/// Z���C���[���擾����
/// </summary>
/// <returns>Z���C���[���</returns>
unsigned char GameBase::GetZLayer() const
{
	return z_layer;
}

/// <summary>
/// �������̎擾����
/// </summary>
/// <returns>�������</returns>
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
