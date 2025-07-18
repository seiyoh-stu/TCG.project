#pragma once

#include"../../GameMain/SceneBase.h"

class Result :public SceneBase
{
private:
	int ResultImageHandle; // リザルト画像のハンドル
	int Result_arrow; // リザルトの矢印のハンドル

	int cursor_number; // カーソルの番号
	int cursor_x; // カーソルの位置

	int bgmHandle;
	int cursorSE;
	int kakutei;


	//歩いてるzombieの描画
	int mobu_walk[10];
	int mobu_walk_index;
	int animation_count;
	int mobu_image;

	float mobu_x;           // ゾンビのx座標
	int mobu_y;           // ゾンビのy座標
	float mobu_speed;       // 移動速度（±で左右移動）
	bool mobu_flip;       // 左右反転描画用フラグ



	void AnimeControl();

public:
	Result();
	virtual~Result();

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


