#pragma once

#include"../../GameMain/SceneBase.h"

class TitleScene : public SceneBase
{
private:
	int titleImageHandle;

public:
	TitleScene();
	virtual ~TitleScene();

	// 初期化
	virtual void Initialize() override;

	// 更新処理
	// 戻り値: 次のシーンタイプ
	virtual eSceneType Update(float delta_second) override;

	// 描画処理
	virtual void Draw() const override;

	// 終了処理
	virtual void Finalize() override;

	// 現在のシーンタイプを取得
	virtual eSceneType GetNowSceneType() const override;

};