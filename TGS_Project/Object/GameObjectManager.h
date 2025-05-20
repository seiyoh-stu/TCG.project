#pragma once
#include "../Utility/SingleTone.h"
#include "GameBase.h"
#include "../Object/Enemy/Enemy.h"
#include "../Object/Enemy/Enemy2.h"
#include "../Object/Enemy/Enemy3.h"
#include "../Object/Enemy/Enemy4.h"
#include <vector>

class GameBaseManager : public Singleton <GameBaseManager>
{
private:
	//�쐬����I�u�W�F�N�g�̃��X�g
	std::vector<GameBase*> create_object;
	//�����I�u�W�F�N�g�̃��X�g
	std::vector<GameBase*> destroy_object;
	//�Q�[�����X�g
	std::vector<GameBase*> game_object_list;

public:

	void CheckCreateObject()
	{
		if (!create_object.empty())
		{
			for (GameBase* obj : create_object)
			{
				if (obj == nullptr)
				{
					// �f�o�b�O�p�̌x��
					printf("create_object �� nullptr ���܂܂�Ă��܂�\n");
					continue;
				}
				//�I�u�W�F�N�g��Z���C���[��������
				int z_layer = obj->GetZLayer();
				std::vector<GameBase*>::iterator itr = game_object_list.begin();

				//�I�u�W�F�N�g��Z���C���[�̒l���r���A�}������ꏊ�����߂�B
				for (; itr != game_object_list.end(); itr++)
				{
					if (z_layer < (*itr)->GetZLayer())
					{
						break;
					}
				}
				//�I�u�W�F�N�g���X�g�ɑ}������
				game_object_list.insert(itr, obj);
			}
			//�I�u�W�F�N�g�������X�g���������
			create_object.clear();

		}
	}

	void CheckDestroyObject()
	{
		if (destroy_object.empty())
		{
			return;
		}

		// �j�����X�g���̃I�u�W�F�N�g�� game_object_list ����폜���A�������
		for (GameBase* obj : destroy_object)
		{
			auto itr = std::find(game_object_list.begin(), game_object_list.end(), obj);
			if (itr != game_object_list.end())
			{
				game_object_list.erase(itr);
			}

			// �I�u�W�F�N�g�̌�n��
			obj->Finalize();
			delete obj;
		}

		// �j�����X�g���N���A
		destroy_object.clear();
	}
	const std::vector<GameBase*>& GetObjectsList() const
	{
		return game_object_list;
	}

	template <class OBJECT>
	OBJECT* CreateGameBase(const Vector2D& generate_location)
	{
		OBJECT* new_instance = new OBJECT();

		GameBase* new_object = dynamic_cast<GameBase*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;

			throw ("�Q�[���I�u�W�F�N�g�������ł��܂���ł���\n");
			return nullptr;
		}

		new_object->Initialize();

		new_object->SetLocation(generate_location);

		create_object.push_back(new_object);

		CheckCreateObject();

		return new_instance;
	}

	void DestroyGameBase(GameBase* target)
	{
		if (target == nullptr)
		{
			return;
		}

		for (GameBase* obj : destroy_object)
		{
			if (obj == target)
			{
				return;
			}
		}

		destroy_object.push_back(target);
	}

	void HitCheck()
	{
		for (int i = 0; i < game_object_list.size(); i++)
		{
			//if (game_object_list[i]->GetMobility() == false)
			//{
			//	continue;
			//}

			for (int j = 0; j < game_object_list.size(); j++)
			{
				if (i == j)
				{
					continue;
				}

				CheckCollision(game_object_list[i], game_object_list[j]);
			}
		}
	}

	/// <summary>
/// �����蔻��̃`�F�b�N
/// </summary>
/// <param name="target">��F�v���C���[</param>
/// <param name="partner">��F�G</param>
	void CheckCollision(GameBase* target, GameBase* partner)
	{
		// ���g�������Ă��邩���`�F�b�N
		if (target == nullptr || partner == nullptr)
		{
			return;
		}

		// �����蔻������쐬
		// tc��pc�́ACollision�N���X�̃����o�ϐ��𗘗p�ł���
		Collision tc = target->GetCollision();
		Collision pc = partner->GetCollision();

		// �����蔻�肪�L�����m�F����
		if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
		{
			// �Ίp����̒��_���W�����߂�
			// �v���C���[�̍���̍��W�����߂�
			tc.point[0] += target->GetLocation() - target->GetBoxSize();
			// �v���C���[�̉E���̍��W�����߂�
			tc.point[1] += target->GetLocation() + target->GetBoxSize();
			// �G�Ƃ��u���b�N�̍���̍��W�����߂�
			pc.point[0] += partner->GetLocation() - partner->GetBoxSize();
			// �G�Ƃ��u���b�N�̉E���̍��W�����߂�
			pc.point[1] += partner->GetLocation() + partner->GetBoxSize();

			// �{�b�N�X���m�̓����蔻��
			if (IsCheckCollision(tc, pc))
			{
				// �������Ă��邱�Ƃ�ʒm����
				target->OnHitCollision(partner);
				partner->OnHitCollision(target);
			}
		}
	}
	// �����ɏ����Ă�̂�����
	void Update(float delta_second);

	void Draw();

	void Finalize();

	void DrawWithOffset(const Vector2D& offset);

};