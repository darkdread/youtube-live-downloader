#include <fstream>
#include <iostream>
#include "yld/chatwindow.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkFont.h"
#include "include/core/SkGraphics.h"
#include "include/core/SkSurface.h"
#include "include/core/SkImageEncoder.h"
#include "include/core/SkEncodedImageFormat.h"
#include "include/effects/SkGradientShader.h"

#include "include/core/SkData.h"
#include "include/core/SkDocument.h"
#include "include/core/SkImage.h"
#include "include/core/SkStream.h"
#include "include/core/SkString.h"
#include "include/core/SkBitmap.h"

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

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    init_skia(width, height);

    glfwSwapInterval(1);
    SkCanvas* canvas = sSurface->getCanvas();
    float yRect = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        canvas->drawColor(SK_ColorWHITE);

        SkPaint paint;
        paint.setAntiAlias(true);
        paint.setColor(SK_ColorRED);
        SkRect rect = {
            (float) width / 2, 0,
            (float) width, yRect
        };
        canvas->drawRect(rect, paint);
        sContext->flush();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        yRect++;
    }

    cleanup_skia();

    glfwTerminate();
};


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