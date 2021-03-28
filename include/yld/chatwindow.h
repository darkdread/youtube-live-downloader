#ifndef YT_CHAT_WINDOW_H
#define YT_CHAT_WINDOW_H

#include "tools/sk_app/Application.h"
#include "tools/sk_app/Window.h"

namespace yld {

    class ChatWindow : public sk_app::Application, sk_app::Window::Layer {
        public:
            ChatWindow(int argc, char** argv, void* platformData);
            ~ChatWindow() override;

            void onIdle() override;

            void onBackendCreated() override;
            void onPaint(SkSurface*) override;
            bool onChar(SkUnichar c, skui::ModifierKey modifiers) override;

        private:
            void updateTitle();

            sk_app::Window* fWindow;
            sk_app::Window::BackendType fBackendType;

            SkScalar fRotationAngle;
    };

}

#endif