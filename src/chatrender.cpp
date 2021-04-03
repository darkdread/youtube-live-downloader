#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#include "chatrender.h"

const sk_sp<SkFontMgr> ChatRender::FMGR(SkFontMgr::RefDefault());

// https://gist.github.com/ad8e/dd150b775ae6aa4d5cf1a092e4713add
void ChatRender::init_skia(int w, int h) {
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

void ChatRender::cleanup_skia() {
	delete sSurface;
	delete sContext;
}

char getUtf8DataSize(char &c){
    unsigned char sBit = c;

    if (sBit >> 7 == 0){
        // ASCII
        return 0;
    } else if (sBit >> 5 == 6){
        // 2 bytes
        return 1;
    } else if (sBit >> 4 == 14){
        // 3 bytes
        return 2;
    } else if (sBit >> 3 == 30){
        // 4 bytes
        return 3;
    }

    throw std::runtime_error("Not a proper utf8 char.");
    return -1;
}

SkUnichar getSkUnichar(std::string &s, int offset, int dataSize){
    unsigned char hBit = char(s[offset]);
    unsigned char dBit = char(s[offset + dataSize]);
    if (dataSize == 0){
        // ASCII
        return dBit;
    } else {
        // More than 1 byte
        if (dBit >> 6 == 2){
            // Data byte.
            SkUnichar r = 0;
            if (dataSize == 1){
                r |= 1UL << ((hBit & 0b00010000) > 0 ? 10 : 0);
                r |= 1UL << ((hBit & 0b00001000) > 0 ? 9 : 0);
                r |= 1UL << ((hBit & 0b00000100) > 0 ? 8 : 0);
                r |= 1UL << ((hBit & 0b00000010) > 0 ? 7 : 0);
                r |= 1UL << ((hBit & 0b00000001) > 0 ? 6 : 0);
            } else if (dataSize == 2){
                r |= 1UL << ((hBit & 0b00001000) > 0 ? 15 : 0);
                r |= 1UL << ((hBit & 0b00000100) > 0 ? 14 : 0);
                r |= 1UL << ((hBit & 0b00000010) > 0 ? 13 : 0);
                r |= 1UL << ((hBit & 0b00000001) > 0 ? 12 : 0);
            } else if (dataSize == 3){
                r |= 1UL << ((hBit & 0b00000100) > 0 ? 20 : 0);
                r |= 1UL << ((hBit & 0b00000010) > 0 ? 19 : 0);
                r |= 1UL << ((hBit & 0b00000001) > 0 ? 18 : 0);
            }

            for(int i = 1; i < dataSize + 1; i++){
                dBit = char(s[offset + i]);
                r |= 1UL << ((dBit & 0b00100000) > 0 ? 5 + ((dataSize - i) * 6) : 0);
                r |= 1UL << ((dBit & 0b00010000) > 0 ? 4 + ((dataSize - i) * 6) : 0);
                r |= 1UL << ((dBit & 0b00001000) > 0 ? 3 + ((dataSize - i) * 6) : 0);
                r |= 1UL << ((dBit & 0b00000100) > 0 ? 2 + ((dataSize - i) * 6) : 0);
                r |= 1UL << ((dBit & 0b00000010) > 0 ? 1 + ((dataSize - i) * 6) : 0);
                r |= 1UL << ((dBit & 0b00000001) > 0 ? 0 + ((dataSize - i) * 6) : 0);
            }
            // If last data bit is 0, remove 1. This is done because (1UL << 0) sets last bit of our SkUnichar to 1.
            r = (dBit & 0b00000001) == 0 ? r - 1 : r;
            return r;
        }
    }
    return 0x00000000;
}

void ChatRender::setFontSize(int size){
    fFontSize = size;
    fFont = SkFont(fTypef, fFontSize, 1.0f, 0.0f);
}

void ChatRender::setTypeface(const char* familyName){
    SkFontStyle fontStyle = SkFontStyle::Normal();
    fTypef = sk_sp<SkTypeface>(FMGR->matchFamilyStyle(familyName, fontStyle));
}

void ChatRender::create_new_bitmap(SkColor bgColor){
    SkBitmap bitmap;
    bitmap.allocPixels(SkImageInfo::MakeN32Premul(width, height));
    fBitmaps.push_back(bitmap);
    pSkCanvas = new SkCanvas{bitmap};
    pSkCanvas->drawColor(bgColor);
}

ChatRender::ChatRender(int width, int height){

    this->width = width;
    this->height = height;

    setTypeface("Tahoma");
    setFontSize(30);
    fFontPaint.setAntiAlias(true);
    fFontPaint.setColor(fFontColor);
    fFont = SkFont{fTypef, fFontSize, 1.0f, 0.0f};

    create_new_bitmap(fBgColor);
    // Render();
}

void ChatRender::encodeToFile(){
    for(int i = 0; i < fBitmaps.size(); i++){
        std::stringstream ss;
        ss << "build/myfile" << i << ".png";
        std::string str;
        ss >> str;
        const char* path = &str[0];
        SkFILEWStream myfile{path};
        SkWStream* mystream = &myfile;
        SkEncodeImage(mystream, fBitmaps[i], SkEncodedImageFormat::kPNG, 0);
    }
}

void ChatRender::renderGl(){

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
    glfwSwapInterval(1);

    init_skia(width, height);

    pSkCanvas = sSurface->getCanvas();
    pSkCanvas->drawColor(SK_ColorWHITE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        std::string message = "dogecoin 🚀ز🚀dogecoin 🚀ز🚀";
        addMessage(message, fFont, fFontPaint);

        sContext->flush();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    cleanup_skia();

    glfwTerminate();
}

void ChatRender::drawText(std::string message, SkFont &sFont, SkPaint &sPaint){
    SkFont font = sFont;

    for (int i = 0; i < message.size(); i++)
    {
        char c[5] = {message[i]};

        // Reset font back to original font.
        font = sFont;
        char dataSize = getUtf8DataSize(c[0]);
        SkUnichar sUnichar = getSkUnichar(message, i, dataSize);
        SkGlyphID id[1] {font.getTypeface()->unicharToGlyph(sUnichar)};

        if (id[0] == 0){
            // Not supported glyph
            sk_sp<SkTypeface> tff (FMGR->matchFamilyStyleCharacter(nullptr, SkFontStyle(), nullptr, 0, sUnichar));

            if (tff == nullptr){
                // No supported typeface to support glyph
                if (!fDrawUnsupportedGlyph){
                    i += dataSize;
                    continue;
                }
            } else {
                font = SkFont{tff, fFontSize, 1.0f, 0.0f};
                id[0] = tff->unicharToGlyph(sUnichar);
            }
        }

        for(char j = 1; j < dataSize + 1; j++){
            c[j] = message[i + j];
        }

        SkScalar skScalar[1];
        font.getWidths(id, 1, skScalar);
        if (drawPosX + skScalar[0] > width){
            drawPosX = 0;
            drawPosY += font.getSize();

            if (drawPosY > height){
                drawPosY = sFont.getSize();
                drawPosX = 0;
                create_new_bitmap(fBgColor);
            }
        }

        sk_sp<SkTextBlob> sBlob = SkTextBlob::MakeFromString(c, font);
        pSkCanvas->drawTextBlob(sBlob.get(), drawPosX, drawPosY, sPaint);

        drawPosX += skScalar[0];

        i+= dataSize;
    }
}

void ChatRender::addMessage(std::string message, SkFont &sFont, SkPaint &sPaint){
    drawPosX = 0;
    drawPosY += fMarginBetweenMsg + sFont.getSize();

    if (drawPosY > height){
        drawPosY = sFont.getSize();
        create_new_bitmap(fBgColor);
    }

    drawText(message, sFont, sPaint);
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