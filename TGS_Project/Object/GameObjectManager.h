#pragma once
#include "../Utility/SingleTone.h"
#include "GameBase.h"
#include <vector>

class GameBaseManager : public Singleton <GameBaseManager>
{
private:
	//作成するオブジェクトのリスト
	std::vector<GameBase*> create_object;
	//消すオブジェクトのリスト
	std::vector<GameBase*> destroy_object;
	//ゲームリスト
	std::vector<GameBase*> game_object_list;

public:

	void CheckCreateObject()
	{
		if (!create_object.empty())
		{
			for (GameBase* obj : create_object)
			{
				//オブジェクトのZレイヤー情報を入れる
				int z_layer = obj->GetZLayer();
				std::vector<GameBase*>::iterator itr = game_object_list.begin();

				//オブジェクトのZレイヤーの値を比較し、挿入する場所を決める。
				for (; itr != game_object_list.end(); itr++)
				{
					if (z_layer < (*itr)->GetZLayer())
					{
						break;
					}
				}
				//オブジェクトリストに挿入する
				game_object_list.insert(itr, obj);
			}
			//オブジェクト生成リストを解放する
			create_object.clear();

		}
	}

	void CheckDestroyObject()
	{
		// 破棄リスト内が空でない場合、リスト内のオブジェクトを破棄する
		if (!destroy_object.empty())
		{
			for (GameBase* obj : destroy_object)
			{
				std::vector<GameBase*>::iterator itr = game_object_list.begin();	// オブジェクトリストの先頭
				// リストの末尾になるまで走査する
				for (; itr != game_object_list.end(); itr++)
				{
					// リスト内にあれば、削除する
					if ((*itr) == obj)
					{
						game_object_list.erase(itr);
						obj->Finalize();
						delete obj;
						break;
					}
				}
			}
			// 動的配列の開放
			destroy_object.clear();

			// リストが空なら処理を終了する
			if (destroy_object.empty())
			{
				return;
			}
			// リスト内のオブジェクトを削除する
			for (GameBase* obj : destroy_object)
			{
				obj->Finalize();
				delete obj;
			}
			// リストの解放
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

			throw ("ゲームオブジェクトが生成できませんでした\n");
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
