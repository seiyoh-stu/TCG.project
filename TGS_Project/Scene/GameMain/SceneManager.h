#pragma once
#include"SceneBase.h"

class SceneManager
{
private:
    SceneBase* current_scene; // 現在のシーン

public:
    SceneManager();
    ~SceneManager();

    // 初期化
    void Initialize();

    // 実行処理
    void Run();

    // 終了処理
    void Finalize();

private:
    // 描画処理
    void Draw() const;

    // シーン切り替え
    void ChangeScene(eSceneType);

    // シーン生成
    SceneBase* CreateScene(eSceneType type);

    void FrameControl();


};