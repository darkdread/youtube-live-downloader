#include <fstream>
#include <iostream>
#include "yld/chatwindow.h"

#include "skia/core/SkCanvas.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkGraphics.h"
#include "skia/core/SkSurface.h"
#include "skia/core/SkImageEncoder.h"
#include "skia/core/SkEncodedImageFormat.h"
#include "skia/effects/SkGradientShader.h"

#include "skia/core/SkData.h"
#include "skia/core/SkDocument.h"
#include "skia/core/SkImage.h"
#include "skia/core/SkStream.h"
#include "skia/core/SkString.h"
#include "skia/core/SkBitmap.h"

using namespace yld;

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
	if (sSurface == nullptr) abort();
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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

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