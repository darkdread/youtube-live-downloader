#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "yld/chatwindow.h"

using namespace yld;

// https://gist.github.com/ad8e/dd150b775ae6aa4d5cf1a092e4713add
void ChatWindow::init_skia(int w, int h) {
	auto interface = GrGLMakeNativeInterface();
	sContext = GrDirectContext::MakeGL(interface).release();

	GrGLFramebufferInfo framebufferInfo;
	framebufferInfo.fFBOID = 0; // assume default framebuffer
	// We are always using OpenGL and we use RGBA8 internal format for both RGBA and BGRA configs in OpenGL.
	//(replace line below with this one to enable correct color spaces) framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
	framebufferInfo.fFormat = GL_RGBA8;

	SkColorType colorType = kRGBA_8888_SkColorType;
	GrBackendRenderTarget backendRenderTarget(w, h,
		0, // sample count
		0, // stencil bits
		framebufferInfo);

	//(replace line below with this one to enable correct color spaces) sSurface = SkSurface::MakeFromBackendRenderTarget(sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(), nullptr).release();
	sSurface = SkSurface::MakeFromBackendRenderTarget(sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr).release();
    // sSurface = SkSurface::MakeFromBackendRenderTarget(sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(), nullptr).release();
	if (sSurface == nullptr) abort();
}

void ChatWindow::cleanup_skia() {
	delete sSurface;
	delete sContext;
}

SkUnichar getSkUnichar(std::string &s, int offset, int dataSize = 0){
    unsigned char sBit = char(s[offset + dataSize]);
    if (sBit >> 7 == 0){
        // ASCII
        return sBit;
    } else {
        // More than 1 byte
        if (sBit >> 6 == 2){
            // Data byte.
            SkUnichar r = 0;
            if (dataSize == 1){
                r |= 1UL << ((char(s[offset]) & 0b00010000) > 0 ? 10 : 0);
                r |= 1UL << ((char(s[offset]) & 0b00001000) > 0 ? 9 : 0);
                r |= 1UL << ((char(s[offset]) & 0b00000100) > 0 ? 8 : 0);
                r |= 1UL << ((char(s[offset]) & 0b00000010) > 0 ? 7 : 0);
                r |= 1UL << ((char(s[offset]) & 0b00000001) > 0 ? 6 : 0);
            } else if (dataSize == 2){
                r |= 1UL << ((char(s[offset]) & 0b00001000) > 0 ? 15 : 0);
                r |= 1UL << ((char(s[offset]) & 0b00000100) > 0 ? 14 : 0);
                r |= 1UL << ((char(s[offset]) & 0b00000010) > 0 ? 13 : 0);
                r |= 1UL << ((char(s[offset]) & 0b00000001) > 0 ? 12 : 0);
            } else if (dataSize == 3){
                r |= 1UL << ((char(s[offset]) & 0b00000100) > 0 ? 20 : 0);
                r |= 1UL << ((char(s[offset]) & 0b00000010) > 0 ? 19 : 0);
                r |= 1UL << ((char(s[offset]) & 0b00000001) > 0 ? 18 : 0);
            }

            for(int i = 1; i < dataSize + 1; i++){
                sBit = char(s[offset + i]);
                r |= 1UL << ((sBit & 0b00100000) > 0 ? 5 + ((dataSize - i) * 6) : 0);
                r |= 1UL << ((sBit & 0b00010000) > 0 ? 4 + ((dataSize - i) * 6) : 0);
                r |= 1UL << ((sBit & 0b00001000) > 0 ? 3 + ((dataSize - i) * 6) : 0);
                r |= 1UL << ((sBit & 0b00000100) > 0 ? 2 + ((dataSize - i) * 6) : 0);
                r |= 1UL << ((sBit & 0b00000010) > 0 ? 1 + ((dataSize - i) * 6) : 0);
                r |= 1UL << ((sBit & 0b00000001) > 0 ? 0 + ((dataSize - i) * 6) : 0);
            }
            r = (sBit & 0b00000001) == 0 ? r - 1 : r;
            return r;
        }
        if (sBit >> 5 == 6){
            // 2 bytes
            return getSkUnichar(s, offset, 1);
        } else if (sBit >> 4 == 14){
            // 3 bytes
            return getSkUnichar(s, offset, 2);
        } else if (sBit >> 3 == 30){
            // 4 bytes
            return getSkUnichar(s, offset, 3);
        }
    }
    return 0x00000000;
}

ChatWindow::ChatWindow(int width, int height){
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    this->width = width;
    this->height = height;

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    init_skia(width, height);

    glfwSwapInterval(1);
    sCanvas = sSurface->getCanvas();
    sCanvas->drawColor(SK_ColorWHITE);
    float yRect = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // SkPaint paint;
        // paint.setAntiAlias(true);
        // paint.setColor(SK_ColorRED);
        // SkRect rect = {
        //     (float) width / 2, 0,
        //     (float) width, yRect
        // };
        // sCanvas->drawRect(rect, paint);

        SkFontStyle fontStyle;
        sk_sp<SkFontMgr> fontManager = SkFontMgr::RefDefault();

        std::string message = "🚀";
        SkUnichar sUc = getSkUnichar(fuck, 0);

        sk_sp<SkTypeface> tf (fontManager->matchFamilyStyleCharacter(nullptr, fontStyle, nullptr, 0, sUc));
        SkFont sFont{tf, 12.0f, 1.0f, 0.0f};

        paint2.setAntiAlias(true);
        paint2.setColor(SK_ColorBLACK);

        AddMessage(message, sFont, paint2);

        sContext->flush();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        // yRect++;
    }

    cleanup_skia();

    glfwTerminate();
};

void ChatWindow::AddMessage(std::string message, SkFont &sFont, SkPaint &sPaint){

    for (int i = 0; i < message.size(); i++)
    {
        const char c = message[i];
        sk_sp<SkTextBlob> sBlob = SkTextBlob::MakeFromString("🚀", sFont);
        sCanvas->drawTextBlob(sBlob.get(), drawPosX, sFont.getSize(), sPaint);

        // SkString sString{c};
        // sCanvas->drawString(sString, drawPosX, sFont.getSize(), sFont, sPaint);

        drawPosX += sFont.getSize();
        if (drawPosX > width){
            drawPosX = 0;
        }
    }
}


// SkBitmap bitmap;
//     bitmap.allocPixels(SkImageInfo::MakeN32Premul(width, height));
//     SkCanvas canvas(bitmap);
//     canvas.drawColor(SK_ColorWHITE);

//     SkPaint paint;
//     paint.setAntiAlias(true);
//     paint.setColor(SK_ColorRED);
//     SkRect rect = {
//         20, 20,
//         (float) width, 50
//     };
//     canvas.drawRect(rect, paint);

//     SkFILEWStream myfile{"myfile.png"};
//     SkWStream* mystream = &myfile;
//     SkEncodeImage(mystream, bitmap, SkEncodedImageFormat::kPNG, 0);