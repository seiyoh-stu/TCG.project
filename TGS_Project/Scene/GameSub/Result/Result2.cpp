#include"Result2.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"

Result2::Result2() : ResultImageHandle(-1), Result_arrow(-1), bgmHandle(-1)
{

}

Result2::~Result2()
{

}

void Result2::Initialize()
{
	ResultImageHandle = LoadGraph("Resource/Images/CLEAR.png");
	Result_arrow = LoadGraph("Resource/Images/AimMark.png");

	cursor_number = 0;
	cursor_x = 100;  //�J�[�\���̏����ʒu

	// BGM �ǂݍ��݂ƍĐ�
	bgmHandle = LoadSoundMem("Resource/Sounds/Title.mp3");
	if (bgmHandle != -1)
	{
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ���[�v�Đ�
		ChangeVolumeSoundMem(200, bgmHandle);
	}
	//�J�[�\���ړ�SE
	cursorSE = LoadSoundMem("Resource/Sounds/�J�[�\���ړ�8.mp3");
	ChangeVolumeSoundMem(250, cursorSE);//�����̑傫��

	//����{�^��
	kakutei = LoadSoundMem("Resource/Sounds/�e��6.mp3");
	ChangeVolumeSoundMem(300, kakutei);//�����̑傫��

}

eSceneType Result2::Update(float delta_second)
{
	//���͋@�\�̎擾
	InputControl* input = InputControl::GetInstance();

	// �����́i�L�[�{�[�h or �R���g���[���[�j
	if (input->GetKeyDown(KEY_INPUT_LEFT) || input->GetPadButtonState(PAD_INPUT_RIGHT) == eInputState::ePress)
	{
		cursor_number--;
		if (cursor_number < 0)
			cursor_number = 1; // �����烋�[�v

		PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK);//�I��SE

	}

	// �E���́i�L�[�{�[�h or �R���g���[���[�j
	if (input->GetKeyDown(KEY_INPUT_RIGHT) || input->GetPadButtonState(PAD_INPUT_LEFT) == eInputState::ePress)
	{
		cursor_number++;
		cursor_number %= 2; // �E���烋�[�v

		PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK);//�I��SE

	}

	// ����i�X�y�[�X or B�{�^���j
	if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetPadButtonState(PAD_INPUT_B) == eInputState::ePress)
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


void Result2::Draw() const
{
	if (ResultImageHandle != -1)
	{
		DrawExtendGraph(0, 0, 1280, 720, ResultImageHandle, TRUE);

		// �J�[�\���`��ix=100�͉��A�K�v�ɉ����Ē����j
		// DrawExtendGraph(1000, cursor_x, 900, cursor_x + 110, Result_arrow, TRUE);
		DrawExtendGraph(cursor_x, 450, cursor_x + 100, 550, Result_arrow, TRUE);
	}

	//DrawFormatString(10, 10, GetColor(255, 255, 255), "���U���g��ʂł�");
}

void Result2::Finalize()
{
	if (ResultImageHandle != -1)
	{
		DeleteGraph(ResultImageHandle);
	}
	if (Result_arrow != -1)
	{
		DeleteGraph(Result_arrow);
	}
	//BGM�I������
	if (bgmHandle != -1)
	{
		StopSoundMem(bgmHandle);
		DeleteSoundMem(bgmHandle);
	}
	DeleteSoundMem(cursorSE);
	DeleteSoundMem(kakutei);

}

eSceneType Result2::GetNowSceneType() const
{
	return eSceneType::eResult2;
}
