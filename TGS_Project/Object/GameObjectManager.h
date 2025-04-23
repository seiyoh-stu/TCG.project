#pragma once
#include "../Utility/SingleTone.h"
#include "GameBase.h"
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
		// �j�����X�g������łȂ��ꍇ�A���X�g���̃I�u�W�F�N�g��j������
		if (!destroy_object.empty())
		{
			for (GameBase* obj : destroy_object)
			{
				std::vector<GameBase*>::iterator itr = game_object_list.begin();	// �I�u�W�F�N�g���X�g�̐擪
				// ���X�g�̖����ɂȂ�܂ő�������
				for (; itr != game_object_list.end(); itr++)
				{
					// ���X�g���ɂ���΁A�폜����
					if ((*itr) == obj)
					{
						game_object_list.erase(itr);
						obj->Finalize();
						delete obj;
						break;
					}
				}
			}
			// ���I�z��̊J��
			destroy_object.clear();

			// ���X�g����Ȃ珈�����I������
			if (destroy_object.empty())
			{
				return;
			}
			// ���X�g���̃I�u�W�F�N�g���폜����
			for (GameBase* obj : destroy_object)
			{
				obj->Finalize();
				delete obj;
			}
			// ���X�g�̉��
			destroy_object.clear();
		}
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
			if (game_object_list[i]->GetMobility() == false)
			{
				continue;
			}

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

	void CheckCollision(GameBase* target, GameBase* partner)
	{
		bool flag = false;

		if (target == nullptr || partner == nullptr)
		{
			return;
		}

		Collision tc = target->GetCollision();
		Collision pc = partner->GetCollision();


		if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
		{

			tc.pivot = target->GetLocation();
			pc.pivot = partner->GetLocation();

			if (tc.IsCheckHitCollision(tc, pc))
			{
				target->OnHitCollision(partner);
				partner->OnHitCollision(target);
			}

		}
	}


};
