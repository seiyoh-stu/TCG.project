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

	// �t�H���g�T�C�Y32�A����6�A�S�V�b�N�̂̃t�H���g���쐬
	fontHandle = CreateFontToHandle("�l�r �S�V�b�N", 32, 6, DX_FONTTYPE_ANTIALIASING);


	// BGM �ǂݍ��݂ƍĐ�
	bgmHandle = LoadSoundMem("Resource/Sounds/�N���A�p.mp3");
	if (bgmHandle != -1)
	{
		ChangeVolumeSoundMem(200, bgmHandle); // ���ʂ�200�ɐݒ�i0?255�j
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ���[�v�Đ�
	}

	//�J�[�\���ړ�SE
	cursorSE = LoadSoundMem("Resource/Sounds/�J�[�\���ړ�8.mp3");
	if (cursorSE != -1) {
		ChangeVolumeSoundMem(250, cursorSE);//�����̑傫��
	}

	//����{�^��
	kakutei = LoadSoundMem("Resource/Sounds/�e��6.mp3");
	if (kakutei != -1) {
		ChangeVolumeSoundMem(300, kakutei);//�����̑傫��
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

		PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK);//�I��SE
	}

	// �E���́i�L�[�{�[�h or �R���g���[���[�j
	if (input->GetKeyDown(KEY_INPUT_RIGHT) || input->GetPadButtonState(PAD_INPUT_DOWN) == eInputState::ePress)
	{
		cursor_number++;
		cursor_number %= 2; // �E���烋�[�v

		PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK);//�I��SE
	}

	// ����i�X�y�[�X or B�{�^���j
	if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetPadButtonState(PAD_INPUT_RTRIGGER) == eInputState::ePress)
	{
		PlaySoundMem(kakutei, DX_PLAYTYPE_NORMAL);//����{�^��SE

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

		// ���b�Z�[�W�\��
		const char* message = "���ׂẴE�F�[�u�����z�����I";
		int text_width = GetDrawStringWidthToHandle(message, strlen(message), fontHandle);
		DrawStringToHandle((1280 - text_width) / 2, 90, message, GetColor(255, 255, 255), fontHandle);
	}

	// �J�[�\���`��ix=100�͉��A�K�v�ɉ����Ē����j
		// DrawExtendGraph(1000, cursor_x, 900, cursor_x + 110, Result_arrow, TRUE);
	DrawExtendGraph(cursor_x, 450, cursor_x + 100, 550, End_arrow, TRUE);

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
	if (fontHandle != -1)
	{
		DeleteFontToHandle(fontHandle);
	}
}

eSceneType Ending::GetNowSceneType() const
{
	return eSceneType::eEnding;
}
