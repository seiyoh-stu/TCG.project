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

    int ticket_tarot = 0;         // �`�P�b�g��
    Player* player = nullptr;  // �v���C���[�Q��

public:
    Tarot();
    virtual ~Tarot();

    void SetPlayer(Player* p);  // �v���C���[���Z�b�g

    virtual void Initialize() override;
    virtual eSceneType Update(float delta_second) override;
    virtual void Draw() const override;
    virtual void Finalize() override;
    virtual eSceneType GetNowSceneType() const override;

    //�O�U�P�P�ǉ�
    void SetTicket(int t);
    int GetTicket() const { return ticket_tarot; }//0616
};
