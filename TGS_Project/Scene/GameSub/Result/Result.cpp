#include"Result.h"
#include"../../../Utility/InputControl.h"
#include"DxLib.h"
#include "../../../Utility/ResourceManager.h"

Result::Result() : ResultImageHandle(-1), Result_arrow(-1), bgmHandle(-1)
{

}

Result::~Result()
{

}

void Result::Initialize()
{
	//�Q�[���I�[�o�[�摜
	ResultImageHandle = LoadGraph("Resource/Images/Gameover2.png");
	Result_arrow = LoadGraph("Resource/Images/AimMark.png");

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> mobu_frames = rm->GetImages("Resource/Images/Enemy/Zombie_1/Walk.png", 10, 10, 1, 128, 128);

	for (int i = 0; i < 10; ++i)
	{
		mobu_walk[i] = mobu_frames[i];
	}

	mobu_image = mobu_walk[0];
	mobu_walk_index = 0;
	animation_count = 0;



	mobu_x = 1140;       //�����ʒu
	mobu_y = 350;
	mobu_speed = 0.4f;  //�]���r�̈ړ����x
	mobu_flip = true;   // �ŏ��͉E����


	cursor_number = 0;
	cursor_x = 100;  //�J�[�\���̏����ʒu

	// BGM �ǂݍ��݂ƍĐ�
	bgmHandle = LoadSoundMem("Resource/Sounds/�I�[�v�j���O.mp3");
	if (bgmHandle != -1)
	{
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE); // ���[�v�Đ�
		ChangeVolumeSoundMem(130, bgmHandle);//�����̑傫��
	}

	//�J�[�\���ړ�SE
	cursorSE = LoadSoundMem("Resource/Sounds/�J�[�\���ړ�8.mp3");
	ChangeVolumeSoundMem(250, cursorSE);//�����̑傫��

	//����{�^��
	kakutei = LoadSoundMem("Resource/Sounds/�e��6.mp3");
	ChangeVolumeSoundMem(300, kakutei);//�����̑傫��


}

eSceneType Result::Update(float delta_second)
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
		case 0: return eSceneType::eInGame;
		case 1: return eSceneType::eEnd;
		}
	}

	// �J�[�\���ʒu�X�V
	cursor_x = 60 + cursor_number * 690;


	mobu_x += mobu_speed;


	// �ǂɓ��������甽�]�i���E�[�j
	if (mobu_x >= 1250)  // ��ʉE�[
	{
		mobu_speed = -mobu_speed; // ���Ɉړ�
		mobu_flip = false;
	}
	else if (mobu_x <= -350)
	{
		mobu_speed = -mobu_speed; // �E�Ɉړ�
		mobu_flip = true;
	}

	animation_count++;
	AnimeControl();

	return GetNowSceneType();

}


void Result::Draw() const
{
	if (ResultImageHandle != -1)
	{
		DrawExtendGraph(0, 0, 1280, 720, ResultImageHandle, TRUE);

		// �J�[�\���`��ix=100�͉��A�K�v�ɉ����Ē����j
		// DrawExtendGraph(1000, cursor_x, 900, cursor_x + 110, Result_arrow, TRUE);
		DrawExtendGraph(cursor_x, 450, cursor_x + 100, 550, Result_arrow, TRUE);
	}
	
	/*DrawExtendGraph(576, 296, 704, 424, mobu_image, TRUE);*/
	const float scale = 2.0f; // 2�{�Ɋg��

	if (mobu_flip)
	{
		// �������i���E���]�j
		DrawRotaGraph2(mobu_x + 64, mobu_y + 64, 0, 0, scale, 0.0, mobu_image, TRUE, TRUE);
	}
	else
	{
		// �E�����i���̂܂܁j
		DrawRotaGraph2(mobu_x + 64, mobu_y + 64, 0, 0, scale, 0.0, mobu_image, TRUE, FALSE);
	}
		

	
}

void Result::Finalize()
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

void Result::AnimeControl()
{
	if (animation_count >= 30)
	{
		animation_count = 0;
		// ���s�A�j���[�V�����t���[����1�i�߂�i10�����[�v�j
		mobu_walk_index = (mobu_walk_index + 1) % 10;
		mobu_image = mobu_walk[mobu_walk_index]; // ���݂̉摜����s�p�ɍX�V
	}
}


eSceneType Result::GetNowSceneType() const
{
	return eSceneType::eResult;
}
