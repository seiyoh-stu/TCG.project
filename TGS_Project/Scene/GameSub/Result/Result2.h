#pragma once

#include"../../GameMain/SceneBase.h"

class Result2 :public SceneBase
{
private:
	int ResultImageHandle; // リザルト画像のハンドル
	int Result_arrow; // リザルトの矢印のハンドル

	int cursor_number; // カーソルの番号
	int cursor_x; // カーソルの位置

	int bgmHandle;
	int cursorSE;
	int kakutei;

public:
	Result2();
	virtual~Result2();

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



