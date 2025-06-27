#pragma once

#include"../../GameMain/SceneBase.h"

class Ending :public SceneBase
{
private:
	int EndImageHandle; // ���U���g�摜�̃n���h��
	int End_arrow; // ���U���g�̖��̃n���h��

	int cursor_number; // �J�[�\���̔ԍ�
	int cursor_x; // �J�[�\���̈ʒu

	int bgmHandle;

	int cursorSE;
	int kakutei;


public:
	Ending();
	virtual~Ending();

	int fontHandle;

	//����������
	virtual void Initialize() override;

	//�X�V����
	//�����F1�t���[��������̎���
	//�߂�l�F���̃V�[���^�C�v
	virtual eSceneType Update(float delta_second) override;

	//�`�揈��
	virtual void Draw() const override;

	//�I��������
	virtual void Finalize() override;

	//���݂̃V�[���^�C�v�i�I�[�o�[���C�h�K�{�j
	virtual eSceneType GetNowSceneType() const override;

};

