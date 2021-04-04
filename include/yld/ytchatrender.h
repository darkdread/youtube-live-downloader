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
            void setTimestampPaint(SkPaint &paint){
                fTsPaint = paint;
            }
            void setTimestampTypeface(const char* familyName, SkFontStyle fontStyle){
                fTsTypef = sk_sp<SkTypeface>(FMGR->matchFamilyStyle(familyName, fontStyle));
                if (fTsTypef == nullptr){
                    return;
                }
                fTsFont = SkFont(fTsTypef, fFontSize, 1.0f, 0.0f);
            }
            void setTimestampFontSize(int size){
                fTsFontSize = size;
                fTsFont = SkFont(fTsTypef, size, 1.0f, 0.0f);
            }
            void drawTimestamp(bool draw){
                fDrawTimestamp = draw;
            }
            void drawAvatar(bool draw){
                fDrawAvatar = draw;
            }
            void setAvatarSize(int size){
                fAvatarSize = size;
            }
            const int getAvatarSize() const {
                if (!fDrawAvatar){
                    return 0;
                }
                return fAvatarSize;
            }
        private:
            SkPaint fTsPaint;
            SkFont fTsFont;
            sk_sp<SkTypeface> fTsTypef;
            SkColor fMemberBgColor = SkColorSetARGB(255,15,157,88);

            bool fDrawTimestamp;
            bool fDrawAvatar;
            int fAvatarSize = fFontSize * 2;
            int fTsFontSize;
            void drawImage(ChatReplayItem &item);
            void addMembershipMessage(ChatReplayItem &item);
    };

}

#endif