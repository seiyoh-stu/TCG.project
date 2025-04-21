#pragma once


#define D_KEYCODE_MAX (256)


class InputControl
{
private:
	
	static InputControl* instance;

	
	char now_key[D_KEYCODE_MAX]; 
	char old_key[D_KEYCODE_MAX]; 

private:
	
	InputControl() = default;

	
	InputControl(InputControl& v) = delete;
	InputControl& operator=(const InputControl& v) = delete;
	

public:
	~InputControl() = default;

public:
	
	static InputControl* GetInstance();
	
	static void DeleteInstance();

public:
	
	void Update();

	
	bool GetKey(int key_code)const;      
	bool GetKeyDown(int key_code) const; 
	bool GetKeyUp(int key_code) const;  

private:
	
	bool CheckKeyCodeRange(int key_code) const;

};
