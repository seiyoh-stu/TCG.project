#include"TarotScene.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"

Tarot::Tarot()
{

}




Tarot::~Tarot()
{

}




void Tarot::Initialize()
{
	
}




eSceneType Tarot::Update(float delta_second)
{
	return GetNowSceneType();
}





void Tarot::Draw() const
{
	
}




void Tarot::Finalize()
{
	
}




eSceneType Tarot::GetNowSceneType() const
{
	return eSceneType::eTarot;
}
