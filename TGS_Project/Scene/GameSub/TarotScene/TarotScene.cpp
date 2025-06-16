#include "TarotScene.h"
#include "../../../Utility/InputControl.h"
#include "DxLib.h"
#include <iostream>

extern Tarot* g_sharedTarot;//ーーーーーーーー追加0610

Tarot::Tarot() {}

Tarot::~Tarot() {}

void Tarot::Initialize()
{
    cards.clear();
    int cardWidth = 120;
    int cardHeight = 60;
    int margin = 20;
    int baseY = 300;

    cards.push_back({ margin + 0 * (cardWidth + margin), baseY, cardWidth, cardHeight, "power_up" });
    cards.push_back({ margin + 1 * (cardWidth + margin), baseY, cardWidth, cardHeight, "power_up" });
    cards.push_back({ margin + 2 * (cardWidth + margin), baseY, cardWidth, cardHeight, "power_down" });
    cards.push_back({ margin + 3 * (cardWidth + margin), baseY, cardWidth, cardHeight, "power_down" });

    selectedIndex = 0;
}

eSceneType Tarot::Update(float delta_second)
{
    bool keyLeft = CheckHitKey(KEY_INPUT_LEFT) != 0;
    bool keyRight = CheckHitKey(KEY_INPUT_RIGHT) != 0;
    bool keyEnter = CheckHitKey(KEY_INPUT_RETURN) != 0;

    // ←キーで選択インデックス減少
    if (keyLeft && !keyLeftPrev) {
        selectedIndex = (selectedIndex - 1 + cards.size()) % cards.size();
    }

    // →キーで選択インデックス増加
    if (keyRight && !keyRightPrev) {
        selectedIndex = (selectedIndex + 1) % cards.size();
    }

    // Enterキーでカード決定・効果適用
    if (keyEnter && !keyEnterPrev && player != nullptr)
    {
        const std::string& effect = cards[selectedIndex].effect;
        if (effect == "power_up")
        {
            player->Player_LevelUp(player->Get_Level() + 1);
        }
        else if (effect == "power_down")
        {
            int level = player->Get_Level() - 1;
            if (level < 1) level = 1;
            player->Player_LevelUp(level);
        }

        return eSceneType::eInGame;  // 処理後は InGame シーンへ戻る
    }

    keyLeftPrev = keyLeft;
    keyRightPrev = keyRight;
    keyEnterPrev = keyEnter;







    //プレイヤーが強化しているように見せる処理ーーーーーーーーーーー
    if (InputControl::GetInstance()->GetKey(KEY_INPUT_1))
    {
        for (int i = 0; i < enemy_list.size(); i++)
        {
            // 生成されているかチェックして大丈夫だったらダメージをブースト
            if (enemy_list[i] != nullptr && enemy_list[i]->is_dead_ != true)
            {
                enemy_list[i]->SetDamageBoost(1);
            }
        }
    }



    // 2キーが押されたら弾数を5→8に変更ーーーーーーーーーーーーーーーーー
    if (input->GetKeyDown(KEY_INPUT_2))
    {
        bullet_magazine = 40;
    }





    return GetNowSceneType();
}



void Tarot::Draw() const
{
    DrawFormatString(50, 250, GetColor(255, 255, 255), "カードを選んでください (← → 決定:Enter)");
    DrawFormatString(50, 220, GetColor(255, 255, 0), "チケット: %d", g_sharedTarot->GetTicket());

    for (size_t i = 0; i < cards.size(); ++i) {
        const auto& card = cards[i];
        int color = (i == selectedIndex) ? GetColor(0, 0, 255) : GetColor(200, 200, 200);

        DrawBox(card.x, card.y, card.x + card.width, card.y + card.height, color, TRUE);
        DrawBox(card.x, card.y, card.x + card.width, card.y + card.height, GetColor(0, 0, 0), FALSE);

        const char* text = (card.effect == "power_up") ? "Power Up" : "Power Down";
        DrawFormatString(card.x + 10, card.y + card.height / 2 - 10, GetColor(0, 0, 0), text);
    }
}

void Tarot::Finalize()
{
}

void Tarot::SetPlayer(Player* p)
{
    player = p;
}

//０６１１
void Tarot::SetTicket(int t)
{
    ticket_tarot = t;
}


eSceneType Tarot::GetNowSceneType() const
{
    return eSceneType::eTarot;
}
