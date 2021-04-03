#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#include "yld/ytchatrender.h"

using namespace yld;

YtChatRender::YtChatRender(int width, int height) : ChatRender(width, height){
    SkPaint tsPaint;
	tsPaint.setColor(SK_ColorBLUE);

    setTimestampPaint(tsPaint);
	setTimestampTypeface("Tahoma", SkFontStyle::Normal());

    SkString* familyName = new SkString{};
    for(int i = 0; i < ChatRender::FMGR.get()->countFamilies(); i++){
        ChatRender::FMGR.get()->getFamilyName(i, familyName);
        std::cout << familyName->c_str() << std::endl;
    }
}

void YtChatRender::addMembershipMessage(ChatReplayItem &item){
    fPaint.setColor(fMemberBgColor);

    int rectHeight = fFontSize * 2;
    float yPadding = 0.3f * rectHeight; // y padding = 30% Rect Height
    rectHeight += 2 * yPadding;

    drawPosX = 0;
    drawPosY += fMarginBetweenMsg + rectHeight;
    float posYAfter = drawPosY - fMarginBetweenMsg; // Remove margin from drawPosY

    if (drawPosY > height){
        drawPosY = rectHeight;
        posYAfter = drawPosY;
        create_new_bitmap(fBgColor);
    }

    // SkRect rect = SkRect::Make()
    SkIRect rect = SkIRect::MakeXYWH(
        0, (int) drawPosY - rectHeight,
        width / 2, rectHeight
    );

    // pSkCanvas->drawRect(rect, fPaint);
    pSkCanvas->drawIRect(rect, fPaint);

    drawPosX = 90;
    drawPosY += fFont.getSize() + (yPadding * 2/3) - rectHeight;

    drawText(item.m_author, fFont, fFontPaint);

    drawPosX = 90;
    drawPosY += fFont.getSize();
    drawText("New member", fFont, fFontPaint);

    // Reset Draw Position
    drawPosY = posYAfter;
    drawPosX = 0; 
}

void YtChatRender::addMessage(ChatReplayItem &item){

    if (item.m_responseType == ChatReplayItem::chat_replay_t::membership){
        addMembershipMessage(item);
        return;
    }

    // Draw timestamp
    drawPosX = 0;
    drawPosY += fFontSize + fMarginBetweenMsg;

    if (drawPosY > height){
        drawPosY = fFontSize;
        create_new_bitmap(fBgColor);
    }

    ChatRender::drawText(item.m_messageTimestampText + " ", fTsFont, fTsPaint);
    ChatRender::addMessage(item.m_author + ": " + item.BuildMessage(), fFont, fFontPaint);
}