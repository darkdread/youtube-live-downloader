#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#include "yld/ytchatrender.h"

using namespace yld;

YtChatRender::YtChatRender(int width, int height) : ChatRender(width, height){

}

void YtChatRender::addMembershipMessage(ChatReplayItem &item){
    fPaint.setColor(fMemberBgColor);

    drawPosX = 0;
    drawPosY += fMarginBetweenMsg + 75;

    if (drawPosY > height){
        drawPosY = 75;
        create_new_bitmap(fBgColor);
    }

    // SkRect rect = SkRect::Make()
    SkIRect rect = SkIRect::MakeXYWH(
        0, (int) drawPosY - 75,
        width / 2, 75
    );
    // pSkCanvas->drawRect(rect, fPaint);
    pSkCanvas->drawIRect(rect, fPaint);

    // Remove margin from drawPosY
    drawPosY -= fMarginBetweenMsg;
}

void YtChatRender::addMessage(ChatReplayItem &item){

    if (item.m_responseType == ChatReplayItem::chat_replay_t::membership){
        addMembershipMessage(item);
        return;
    }

    ChatRender::addMessage(item.m_author + ": " + item.BuildMessage(), fFont, fFontPaint);
}