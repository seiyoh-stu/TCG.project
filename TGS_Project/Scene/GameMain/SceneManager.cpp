#include "SceneManager.h"
#include "../../Utility/InputControl.h"
#include"DxLib.h"
#include"../GameSub/Title/TitleScene.h"
#include"../GameMain/InGame.h"
#include"../GameSub/Result/Result.h"
#include"../GameSub/Result/Result2.h"
#include"../GameSub/Help/Help.h"
#include"../GameSub/TarotScene/TarotScene.h"
#include <map>

// グローバル変数定義
LONGLONG old_time;        // 前回計測値
LONGLONG now_time;        // 現在計測値
float delta_second;        // １フレームあたりの時間

std::map<eSceneType, SceneBase*> scene_map;

SceneManager::SceneManager() : current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{
    // 終了処理
    Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneManager::Initialize()
{
    // ウインドウモードへの変更
    ChangeWindowMode(TRUE);

    // 画面サイズのセット
    SetGraphMode(1280, 720, 32);

    // DXライブラリの初期化処理
    if (DxLib_Init() == -1)
    {
        throw("DXライブラリの初期化に失敗しました\n");
    }

    // 描画先を裏画面に設定
    SetDrawScreen(DX_SCREEN_BACK);

    // 最初のシーンをタイトルに設定
    ChangeScene(eSceneType::eTitle);

}

/// <summary>
/// 実行処理
/// </summary>
void SceneManager::Run()
{
    // 入力制御インスタンスの取得
    InputControl* input = InputControl::GetInstance();

    // メインループ(メッセージ処理とESCキーが押されるまで)
    while (ProcessMessage() != -1 && input->GetKeyUp(KEY_INPUT_ESCAPE) != true)
    {
        // 入力制御の更新処理
        input->Update();
        FrameControl();
        // 現在のシーンの更新処理
        eSceneType next_scene_type = current_scene->Update(delta_second);

        // 現在のシーンの描画処理
        Draw();

        // シーン遷移処理
        if (next_scene_type != current_scene->GetNowSceneType())
        {
            ChangeScene(next_scene_type);
        }

        // フレームレート制御(バックバッファへの描画完了後に同期)
    }
}

/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Draw() const
{
    // 画面のクリア
    ClearDrawScreen();

    // 現在のシーンの描画処理
    current_scene->Draw();

    // 裏画面の内容を表画面へ反映
    ScreenFlip();
}

/// <summary>
/// シーン切り替え処理
/// </summary>
/// <param name="type">切り替え先のシーンタイプ</param>
void SceneManager::ChangeScene(eSceneType type)
{
    // 指定されたシーンタイプの新しいシーンを作成
    SceneBase* new_scene = CreateScene(type);

    // シーンの作成に失敗した場合
    if (new_scene == nullptr)
    {
        throw("シーンの作成に失敗しました\n");
    }

    // 現在のシーンが存在する場合、終了処理を行う
    if (current_scene != nullptr)
    {
        current_scene->Finalize();
        delete current_scene;
        current_scene = new_scene;
    }

    // 新しいシーンの初期化処理
    new_scene->Initialize();
    current_scene = new_scene;
}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="type">生成するシーンタイプ</param>
/// <returns>生成したシーンのインスタンス</returns>
SceneBase* SceneManager::CreateScene(eSceneType type)
{
    // シーンタイプに応じて新しいシーンのインスタンスを生成する
    switch (type)
    {
    case eSceneType::eTitle:
        return dynamic_cast<SceneBase*>(new TitleScene());

    case eSceneType::eInGame:
        return dynamic_cast<SceneBase*>(new InGame());

    case eSceneType::eResult:
        return dynamic_cast<SceneBase*>(new Result());

    case eSceneType::eResult2:
        return dynamic_cast<SceneBase*>(new Result2());

    case eSceneType::eHelp:
        return dynamic_cast<SceneBase*>(new Help());
    case eSceneType::eTarot:
        return dynamic_cast<SceneBase*>(new Tarot());


    case eSceneType::eEnd:

        return nullptr;
    default:
        return nullptr;
    }
}

void SceneManager::FrameControl()
{
    // 現在時間の取得（μ秒）
    now_time = GetNowHiPerformanceCount();

    // 開始時間から現在時間までに経過した時間を計算する（μ秒）
    // 分解能をμ秒→秒に変換する
    delta_second = (float)(now_time - old_time) * 1.0e-6f;

    // 計測開始時間を更新する
    old_time = now_time;

    // ディスプレイのリフレッシュレートを取得する
    float refresh_rate = (float)GetRefreshRate();

    // １フレーム当たりの時間が1/リフレッシュレート秒を超えたら、整える
    if (delta_second > (1.0f / refresh_rate))
    {
        delta_second = (1.0f / refresh_rate);
    }
}

//シーンタイプ設定
void SceneManager::SetScene(eSceneType type, SceneBase* scene)
{
    scene_map[type] = scene;
}

/// <summary>
/// 終了処理
/// </summary>
void SceneManager::Finalize()
{
    // 現在のシーンが存在する場合、終了処理を行い削除する
    if (current_scene != nullptr)
    {
        current_scene->Finalize();
        delete current_scene;
        current_scene = nullptr;
    }

    // 入力制御インスタンスの削除
    InputControl::DeleteInstance();

    // DXライブラリの終了処理
    DxLib_End();
}