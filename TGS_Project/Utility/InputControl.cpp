#include"InputControl.h"
#include"DxLib.h"

//静的メンバ変数定義
InputControl* InputControl::instance = nullptr; //クラスのインスタンスのポインタ

//入力制御クラスのインスタンス取得する処理
InputControl* InputControl::GetInstance()
{
	//インスタンスがなければ、生成する
	if (instance == nullptr)
	{
		instance = new InputControl();
	}
	//自分自身のポインタを返却する
	return instance;
}


//入力制御クラスのインスタンス削除する
void InputControl::DeleteInstance()
{
	//インスタンスが存在していれば
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void InputControl::Update()
{
	//前回入力値の更新
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	//現在入力値の更新
	GetHitKeyStateAll(now_key);
}


//キーが押されているか確認する処理
bool InputControl::GetKey(int key_code)const
{
	return(CheckKeyCodeRange(key_code) && (now_key[key_code] == TRUE &&
		old_key[key_code] == TRUE));
}

//キーが押された瞬間か確認する処理
bool InputControl::GetKeyDown(int key_code)const
{
	return(CheckKeyCodeRange(key_code) && (now_key[key_code] == TRUE &&
		old_key[key_code] == FALSE));
}

//キーを離した瞬間
bool InputControl::GetKeyUp(int key_code)const
{
	return(CheckKeyCodeRange(key_code) && ((now_key[key_code] == FALSE) &&
		old_key[key_code] == TRUE));
}


//キーコードの範囲内か確認する処理
bool InputControl::CheckKeyCodeRange(int key_code)const
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}
