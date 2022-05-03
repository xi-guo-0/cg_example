#include "image.h"
#include <memory>
#include <png.h>

Image::Image(const int w, const int h) : w_(w), h_(h) {
    data_ = new std::uint8_t *[h];
    for (int i = 0; i < h; ++i) {
        data_[i] = new std::uint8_t[w * 4];
    }
}

Color Image::Get(const int x, const int y) const {
    if (0 < x && x < w_ && 0 < y && y < h_) {
        const auto *px = &data_[y][x * 4];
        return {px[0], px[1], px[2], px[3]};
    } else {
        return {};
    }
}

void Image::Set(const int x, const int y, const Color &color) {
    if (0 < x && x < w_ && 0 < y && y < h_) {
        auto *px = &data_[y][x * 4];
        px[0] = color.r;
        px[1] = color.g;
        px[2] = color.b;
        px[3] = color.a;
    }
}

bool Image::WritePngFile(const std::string &filename, const bool vertical_flip) {
    std::unique_ptr<FILE, std::function<int(FILE *)>> file(fopen(filename.c_str(), "wb"), fclose);
    if (!file) {
        return false;
    }
    auto *png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        return false;
    }
    auto *info = png_create_info_struct(png);
    if (!info) {
        return false;
    }
    png_init_io(png, file.get());
    png_set_IHDR(png, info, Width(), Height(), 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    png_write_image(png, data_);
    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    return true;
}

int Image::Width() const {
    return w_;
}

int Image::Height() const {
    return h_;
}

Image::~Image() {
    for (int y = 0; y < Height(); ++y) {
        delete[] data_[y];
    }
    delete[] data_;
}
