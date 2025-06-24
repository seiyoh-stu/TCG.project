#include"Ending.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"

Ending::Ending() : EndImageHandle(-1), End_arrow(-1), bgmHandle(-1)
{

}

Ending::~Ending()
{

}

void Ending::Initialize()
{
	EndImageHandle = LoadGraph("Resource/Images/CLEAR.png");
	End_arrow = LoadGraph("Resource/Images/AimMark.png");

	cursor_number = 0;
	cursor_x = 100;  //�J�[�\���̏����ʒu

	// BGM �ǂݍ��݂ƍĐ�
	bgmHandle = LoadSoundMem("Resource/Sounds/�I�[�v�j���O.mp3");
	if (bgmHandle != -1)
	{
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ���[�v�Đ�
	}

	if (EndImageHandle == -1 || End_arrow == -1 || bgmHandle == -1) {
		printfDx("End�V�[���̃��\�[�X�ǂݍ��݂Ɏ��s���܂���\n");
	}
}

eSceneType Ending::Update(float delta_second)
{
	//���͋@�\�̎擾
	InputControl* input = InputControl::GetInstance();

	// �����́i�L�[�{�[�h or �R���g���[���[�j
	if (input->GetKeyDown(KEY_INPUT_LEFT) || input->GetPadButtonState(PAD_INPUT_UP) == eInputState::ePress)
	{
		cursor_number--;
		if (cursor_number < 0)
			cursor_number = 1; // �����烋�[�v
	}

	// �E���́i�L�[�{�[�h or �R���g���[���[�j
	if (input->GetKeyDown(KEY_INPUT_RIGHT) || input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::ePress)
	{
		cursor_number++;
		cursor_number %= 2; // �E���烋�[�v
	}

	// ����i�X�y�[�X or B�{�^���j
	if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetPadButtonState(PAD_INPUT_2) == eInputState::ePress)
	{
		switch (cursor_number)
		{
		case 0: return eSceneType::eTitle;
		case 1: return eSceneType::eEnd;
		}
	}

	// �J�[�\���ʒu�X�V
	cursor_x = 60 + cursor_number * 690;

	return GetNowSceneType();
}


void Ending::Draw() const
{
	if (EndImageHandle != -1)
	{
		DrawExtendGraph(0, 0, 1280, 720, EndImageHandle, TRUE);

		// �J�[�\���`��ix=100�͉��A�K�v�ɉ����Ē����j
		// DrawExtendGraph(1000, cursor_x, 900, cursor_x + 110, Result_arrow, TRUE);
		DrawExtendGraph(cursor_x, 450, cursor_x + 100, 550, End_arrow, TRUE);
	}

	//DrawFormatString(10, 10, GetColor(255, 255, 255), "���U���g��ʂł�");
}

void Ending::Finalize()
{
	if (EndImageHandle != -1)
	{
		DeleteGraph(EndImageHandle);
	}
	if (End_arrow != -1)
	{
		DeleteGraph(End_arrow);
	}
	//BGM�I������
	if (bgmHandle != -1)
	{
		StopSoundMem(bgmHandle);
		DeleteSoundMem(bgmHandle);
	}
}

eSceneType Ending::GetNowSceneType() const
{
	return eSceneType::eEnding;
}
