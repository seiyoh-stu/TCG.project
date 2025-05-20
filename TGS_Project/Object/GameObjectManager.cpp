#include "GameObjectManager.h"
#include "DxLib.h"

void GameBaseManager::Update(float delta_second)
{
	CheckCreateObject();
	for (GameBase* gb : game_object_list)
	{
		gb->Update(delta_second);
	}

	HitCheck();
	CheckDestroyObject();
}

void GameBaseManager::Draw()
{
	for (GameBase* gb : game_object_list)
	{
		gb->Draw(0);
	}

}

void GameBaseManager::Finalize()
{
	for (GameBase* gb : game_object_list)
	{
		gb->Finalize();
	}
}



void GameBaseManager::DrawWithOffset(const Vector2D& offset)
{
	for (GameBase* gb : game_object_list)
	{
		gb->Draw(offset);
	}
}
