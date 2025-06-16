#pragma once

#include "../../GameMain/SceneBase.h"
#include "../../../Object/Player/Player.h"
#include <vector>
#include <string>
#include <algorithm>  // std::max に必要

struct CardInfo
{
    int x, y, width, height;
    std::string effect;  // "power_up" または "power_down"
};
class Tarot : public SceneBase
{
private:


    std::vector<CardInfo> cards;
    int selectedIndex = 0;
    bool keyLeftPrev = false;
    bool keyRightPrev = false;
    bool keyEnterPrev = false;

    int ticket_tarot = 0;         // チケット数
    Player* player = nullptr;  // プレイヤー参照

public:
    Tarot();
    virtual ~Tarot();

    void SetPlayer(Player* p);  // プレイヤーをセット

    virtual void Initialize() override;
    virtual eSceneType Update(float delta_second) override;
    virtual void Draw() const override;
    virtual void Finalize() override;
    virtual eSceneType GetNowSceneType() const override;

    //０６１１追加
    void SetTicket(int t);
    int GetTicket() const { return ticket_tarot; }//0616
};
