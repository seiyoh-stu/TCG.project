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
				if (obj == nullptr)
				{
					// デバッグ用の警告
					printf("create_object に nullptr が含まれています\n");
					continue;
				}
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
		if (destroy_object.empty())
		{
			return;
		}

		// 破棄リスト内のオブジェクトを game_object_list から削除し、解放する
		for (GameBase* obj : destroy_object)
		{
			auto itr = std::find(game_object_list.begin(), game_object_list.end(), obj);
			if (itr != game_object_list.end())
			{
				game_object_list.erase(itr);
			}

			// オブジェクトの後始末
			obj->Finalize();
			delete obj;
		}

		// 破棄リストをクリア
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
/// 当たり判定のチェック
/// </summary>
/// <param name="target">例：プレイヤー</param>
/// <param name="partner">例：敵</param>
	void CheckCollision(GameBase* target, GameBase* partner)
	{
		// 中身が入っているかをチェック
		if (target == nullptr || partner == nullptr)
		{
			return;
		}

		// 当たり判定情報を作成
		// tcとpcは、Collisionクラスのメンバ変数を利用できる
		Collision tc = target->GetCollision();
		Collision pc = partner->GetCollision();

		// 当たり判定が有効か確認する
		if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
		{
			// 対角線上の頂点座標を求める
			// プレイヤーの左上の座標を求める
			tc.point[0] += target->GetLocation() - target->GetBoxSize();
			// プレイヤーの右下の座標を求める
			tc.point[1] += target->GetLocation() + target->GetBoxSize();
			// 敵とかブロックの左上の座標を求める
			pc.point[0] += partner->GetLocation() - partner->GetBoxSize();
			// 敵とかブロックの右下の座標を求める
			pc.point[1] += partner->GetLocation() + partner->GetBoxSize();

			// ボックス同士の当たり判定
			if (IsCheckCollision(tc, pc))
			{
				// 当たっていることを通知する
				target->OnHitCollision(partner);
				partner->OnHitCollision(target);
			}
		}
	}
	// ここに書いてるのがだめ
	void Update(float delta_second);

	void Draw();

	void Finalize();

	void DrawWithOffset(const Vector2D& offset);

};