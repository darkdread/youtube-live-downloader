#ifndef YT_CHAT_WINDOW_H
#define YT_CHAT_WINDOW_H

#include <GLFW/glfw3.h>
#define SK_GL
#include "skia/gpu/GrBackendSurface.h"
#include "skia/gpu/GrDirectContext.h"
#include "skia/gpu/gl/GrGLInterface.h"

#include "skia/core/SkCanvas.h"
#include "skia/core/SkGraphics.h"
#include "skia/core/SkImageEncoder.h"
#include "skia/core/SkString.h"
#include "skia/private/SkTemplates.h"
#include "skia/core/SkTypeface.h"

namespace yld {

    class ChatWindow {
        public:
            GrDirectContext* sContext = nullptr;
            SkSurface* sSurface = nullptr;
            GLFWwindow* window;
            ChatWindow(int width, int height);

        private:
            void init_skia(int width, int height);
    };

}

#endif