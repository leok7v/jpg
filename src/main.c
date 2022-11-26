/* Copyright (c) Dmitry "Leo" Kuznetsov 2021 see LICENSE for details */
#include "quick.h"
#define quick_implementation // alt: quick_implementation_console
#include "quick.h"
#include "jpeg_encode.h"
#include "jpeg_decode.h"

begin_c

const char* title = "jpeg (en|de)coder";

static image_t image;

static char filename[260]; // c:\Users\user\Pictures\mandrill-4.2.03.png

static void init();

static int  console() {
    fatal_if(true, "%s only SUBSYSTEM:WINDOWS", app.argv[0]);
    return 1;
}

app_t app = {
    .class_name = "sample4",
    .init = init,
    .main = console, // optional
    .min_width = 640,
    .min_height = 640
};

static void* load_image(const byte* data, int64_t bytes, int32_t* w, int32_t* h,
    int32_t* bpp, int32_t preferred_bytes_per_pixel);

static void file_write(void* that, const void* data, int bytes) {
    FILE* fp = (FILE*)that;
    fwrite(data, bytes, 1, fp);
}

static void load_images() {
    int r = 0;
    void* data = 0;
    int64_t bytes = 0;
    r = crt.memmap_read(filename, &data, &bytes);
    fatal_if_not_zero(r);
    int w = 0;
    int h = 0;
    int bpp = 0; // bytes (!) per pixel
    void* pixels = load_image(data, bytes, &w, &h, &bpp, 0);
    if (pixels != null) {
        gdi.image_init(&image, w, h, bpp, pixels);
        strprintf(filename, "%s\\mandrill-4.2.03.jpg",
            app.known_folder(known_folder_pictures));
        FILE* f = fopen(filename, "wb");
        jpeg_encode(f, file_write, pixels, w, h, 3, 99);
        fclose(f);
        free(pixels);
    }
    crt.memunmap(data, bytes);
}

static void paint(uic_t* ui) {
    gdi.set_brush(gdi.brush_color);
    gdi.set_brush_color(colors.black);
    gdi.fill(0, 0, ui->w, ui->h);
    if (image.w > 0 && image.h > 0) {
        int w = min(ui->w, image.w);
        int h = min(ui->h, image.h);
        int x = (ui->w - w) / 2;
        int y = (ui->h - h) / 2;
        gdi.set_clip(0, 0, ui->w, ui->h);
        gdi.draw_image(x, y, w, h, &image);
        gdi.set_clip(0, 0, 0, 0);
    }
}

static void download() {
    static const char* url =
        "https://upload.wikimedia.org/wikipedia/commons/c/c1/"
        "Wikipedia-sipi-image-db-mandrill-4.2.03.png";
    if (access(filename, 04) != 0) {
        char cmd[256];
        strprintf(cmd, "curl.exe  --silent --fail --create-dirs "
            "\"%s\" --output \"%s\" 2>nul >nul", url, filename);
        int r = system(cmd);
        if (r != 0) {
            traceln("download %s failed %d %s", filename, r, strerror(r));
        }
    }
}

static void keyboard(uic_t* unused, int32_t ch) {
    (void)unused;
    if (ch == 'q' || ch == 'Q' || ch == 033) { app.close(); }
}

static void init() {
    app.title = title;
    app.ui->paint = paint;
    app.ui->keyboard = keyboard;
    strprintf(filename, "%s\\mandrill-4.2.03.png",
        app.known_folder(known_folder_pictures));
    download();
    load_images();
}

end_c


#pragma warning(disable: 4459) // parameter/local hides global declaration

#define STBI_ASSERT(x) assert(x)
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

begin_c

static void* load_image(const byte* data, int64_t bytes, int32_t* w, int32_t* h,
    int32_t* bpp, int32_t preferred_bytes_per_pixel) {
    void* pixels = stbi_load_from_memory((byte const*)data, (int)bytes, w, h,
        bpp, preferred_bytes_per_pixel);
    return pixels;
}
 end_c

 #define jpeg_encode_implementation
 #include "jpeg_encode.h"
 #define jpeg_decode_implementation
 #include "jpeg_decode.h"
