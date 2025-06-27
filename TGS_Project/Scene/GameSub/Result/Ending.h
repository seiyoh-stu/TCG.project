#pragma once

#include"../../GameMain/SceneBase.h"

class Ending :public SceneBase
{
private:
	int EndImageHandle; // リザルト画像のハンドル
	int End_arrow; // リザルトの矢印のハンドル

	int cursor_number; // カーソルの番号
	int cursor_x; // カーソルの位置

	int bgmHandle;

	int cursorSE;
	int kakutei;


public:
	Ending();
	virtual~Ending();

	int fontHandle;

	//初期化処理
	virtual void Initialize() override;

	//更新処理
	//引数：1フレーム当たりの時間
	//戻り値：次のシーンタイプ
	virtual eSceneType Update(float delta_second) override;

	//描画処理
	virtual void Draw() const override;

	//終了時処理
	virtual void Finalize() override;

	//現在のシーンタイプ（オーバーライド必須）
	virtual eSceneType GetNowSceneType() const override;

};

