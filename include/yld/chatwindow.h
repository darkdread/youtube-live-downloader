#ifndef YT_CHAT_WINDOW_H
#define YT_CHAT_WINDOW_H

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
// #include "include/core/SkImageEncoder.h"
// #include "include/core/SkEncodedImageFormat.h"

// #include "include/core/SkData.h"
// #include "include/core/SkImage.h"
// #include "include/core/SkStream.h"

namespace yld {

    class ChatWindow {
        public:
            int width;
            int height;

            std::vector<SkBitmap> sBitmaps;
            GrDirectContext* sContext = nullptr;
            SkSurface* sSurface = nullptr;
            SkCanvas* sCanvas = nullptr;
            GLFWwindow* window;

            ChatWindow(int width, int height);
            void AddMessage(std::string message, SkFont &sFont, SkPaint &sPaint);

        private:
            sk_sp<SkFontMgr> fontManager;
            SkScalar drawPosX = 0.0f;
            SkPaint paint2;
            void cleanup_skia();
            void init_skia(int width, int height);
    };

}

#endif