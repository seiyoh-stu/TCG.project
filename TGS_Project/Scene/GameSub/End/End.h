#pragma once

#include"../../GameMain/SceneBase.h"

class End :public SceneBase
{
private:

public:
	End();
	virtual~End();

	//初期化処理
	virtual void Initialize() override;

	//更新処理
	//引数：1フレーム当たりの時間
	//戻り値：次のシーンタイプ
	virtual eSceneType Update() override;

	//描画処理
	virtual void Draw() const override;

	//終了時処理
	virtual void Finalize() override;

	//現在のシーンタイプ（オーバーライド必須）
	virtual eSceneType GetNowSceneType() const override;

};

