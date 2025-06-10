#pragma once

#include "../../GameMain/SceneBase.h"
#include "../../../Object/Player/Player.h"
#include <vector>
#include <string>
#include <algorithm>  // std::max �ɕK�v

struct CardInfo
{
    int x, y, width, height;
    std::string effect;  // "power_up" �܂��� "power_down"
};
class Tarot : public SceneBase
{
private:


    std::vector<CardInfo> cards;
    int selectedIndex = 0;
    bool keyLeftPrev = false;
    bool keyRightPrev = false;
    bool keyEnterPrev = false;

    int ticket = 0;         // �`�P�b�g��
    Player* player = nullptr;  // �v���C���[�Q��

public:
    Tarot();
    virtual ~Tarot();

    // �`�P�b�g����
    void AddTicket();       // �`�P�b�g+1
    int GetTicket() const;  // �`�P�b�g�擾

    void SetPlayer(Player* p);  // �v���C���[���Z�b�g

    virtual void Initialize() override;
    virtual eSceneType Update(float delta_second) override;
    virtual void Draw() const override;
    virtual void Finalize() override;
    virtual eSceneType GetNowSceneType() const override;
};
