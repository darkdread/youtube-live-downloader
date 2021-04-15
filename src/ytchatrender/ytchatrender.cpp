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

void YtChatRender::drawImage(ChatReplayItem &item){

    sk_sp<SkData> png = SkData::MakeFromFileName("author.png");
    sk_sp<SkImage> image = SkImage::MakeFromEncoded(png);
    sk_sp<SkSurface> surf = SkSurface::MakeRasterN32Premul(fAvatarSize, fAvatarSize);
    SkCanvas* c = surf->getCanvas();
    SkScalar iWidth = image.get()->width();
    SkScalar resize = fAvatarSize / iWidth;
    c->scale(resize, resize);
    c->drawImage(image, 0, 0);

    sk_sp<SkImage> image2 = surf->makeImageSnapshot();
    pSkCanvas->drawImage(image2, drawPosX, drawPosY - fAvatarSize/2);
    // pSkCanvas->drawImage(image, 0, drawPosY - fFontSize/2 - fMarginBetweenMsg);
    drawPosX += image2.get()->width();
}

void YtChatRender::addMessage(ChatReplayItem &item){

    SkCanvas* pCanvas = pSkCanvas;
    SkPaint debugPaint;
    
    // New message line
    debugPaint.setColor(SK_ColorRED);
    pSkCanvas->drawLine(drawPosX, drawPosY, width, drawPosY, debugPaint);

    drawPosX = fMarginBetweenMsg;
    drawPosY += fMarginBetweenMsg;

    SkScalar posYAfterAvatar = 0.0;
    // pSkCanvas->drawLine(drawPosX, drawPosY, width, drawPosY, fPaint);

    if (item.m_responseType == ChatReplayItem::chat_replay_t::membership){
        addMembershipMessage(item);
        return;
    }

    if (fDrawAvatar){
        drawPosY += fAvatarSize;
        if (drawPosY + fAvatarSize/2 > height){
            drawPosY = fAvatarSize + fMarginBetweenMsg;
            create_new_bitmap(fBgColor);
            pCanvas = pSkCanvas;
        }
        // Line after avatar
        debugPaint.setColor(SK_ColorBLACK);
        pSkCanvas->drawLine(drawPosX, drawPosY + fAvatarSize/2, width, drawPosY + fAvatarSize/2, debugPaint);
        drawImage(item);
        posYAfterAvatar = drawPosY + fAvatarSize/2;
        drawPosX += fMarginBetweenMsg;
    } else {
        drawPosY += fFontSize;

        if (drawPosY > height){
            drawPosY = fFontSize + fMarginBetweenMsg;
            create_new_bitmap(fBgColor);
            pCanvas = pSkCanvas;
        }
    }

    // Line half of avatar
    debugPaint.setColor(SK_ColorBLUE);
    pSkCanvas->drawLine(drawPosX, drawPosY, width, drawPosY, debugPaint);

    if (fDrawTimestamp){
        ChatRender::drawText(item.m_messageTimestampText, fTsFont, fTsPaint);
        drawPosX += fMarginBetweenMsg;
    }
    drawPosXNewLine = drawPosX;
    ChatRender::addMessage(item.m_author + ": " + item.BuildMessage(), fFont, fFontPaint);
    drawPosXNewLine = 0.0F;
    if (fDrawAvatar && pCanvas == pSkCanvas && posYAfterAvatar > drawPosY){
        drawPosY = posYAfterAvatar;
    }
}