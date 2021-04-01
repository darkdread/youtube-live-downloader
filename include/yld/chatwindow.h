#ifndef YT_CHAT_WINDOW_H
#define YT_CHAT_WINDOW_H

#include <GLFW/glfw3.h>
#define SK_GL
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkGraphics.h"
#include "include/core/SkImageEncoder.h"
#include "include/core/SkString.h"
#include "include/private/SkTemplates.h"
#include "include/core/SkTypeface.h"

namespace yld {

    class ChatWindow {
        public:
            GrDirectContext* sContext = nullptr;
            SkSurface* sSurface = nullptr;
            GLFWwindow* window;

            ChatWindow(int width, int height);

        private:
            void cleanup_skia();
            void init_skia(int width, int height);
    };

}

#endif