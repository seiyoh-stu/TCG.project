#pragma once

enum eSceneType
{
    eTitle,
    eInGame,
    eResult,
    eHelp,
    eEnd,
};

class SceneBase {
protected:
    // シングルトンインスタンス保持用

public:
    SceneBase() {}
    virtual ~SceneBase() {}

    // 初期化処理
    virtual void Initialize() {}

    // 更新処理
    // 戻り値: 次のシーンタイプ
    virtual eSceneType Update()
    {
        return GetNowSceneType();
    }

    // 描画処理
    virtual void Draw() const {}

    // 終了処理
    virtual void Finalize() {}

    // 現在のシーンタイプを取得
    virtual eSceneType GetNowSceneType() const = 0;
};