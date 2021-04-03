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
#include "chatreplayitem.h"
#include "chatrender.h"

namespace yld {

    class YtChatRender : public ChatRender {
        public:

            YtChatRender(int width, int height);
            void addMessage(ChatReplayItem &item);

        private:
            SkColor fMemberBgColor = SkColorSetARGB(128, 0, 255, 0);
            void addMembershipMessage(ChatReplayItem &item);
    };

}

#endif