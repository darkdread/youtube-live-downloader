#ifndef CHAT_RENDER_H
#define CHAT_RENDER_H

#include <GLFW/glfw3.h>
#include <thread>
#define SK_GL
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkGraphics.h"
#include "include/core/SkSurface.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkTextBlob.h"
#include "include/core/SkFont.h"
#include "include/core/SkString.h"

class ChatRender {
    public:
        int width;
        int height;

        GrDirectContext* sContext = nullptr;
        SkSurface* sSurface = nullptr;
        SkCanvas* pSkCanvas;
        GLFWwindow* window;

        ChatRender(int width, int height);
        void renderGl();
        void setFontSize(int size);
        void setTypeface(const char* familyName, SkFontStyle fontStyle);
        void drawText(std::string message, SkFont &sFont, SkPaint &sPaint);
        void addMessage(std::string message, SkFont &sFont, SkPaint &sPaint);
        void encodeToFile();
        void setBackgroundColor(SkColor);
        void drawUnsupportedGlyph(bool draw){
            fDrawUnsupportedGlyph = draw;
        }

    private:
        bool fDrawUnsupportedGlyph;
        void cleanup_skia();
        void init_skia(int width, int height);

    protected:
        static const sk_sp<SkFontMgr> FMGR;

        SkScalar drawPosX = 0.0f;
        SkScalar drawPosY = 0.0f;
        SkScalar drawPosXNewLine = 0.0f;

        std::vector<SkBitmap> fBitmaps;
        sk_sp<SkTypeface> fTypef;
        SkFont fFont;
        SkPaint fFontPaint;
        SkPaint fPaint;
        SkColor fFontColor = SK_ColorBLACK;
        SkColor fBgColor = SK_ColorWHITE;
        float fFontSize = 12;
        float fMarginBetweenMsg = 12;

        void create_new_bitmap(SkColor bgColor);
};

#endif