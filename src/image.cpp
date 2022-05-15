#include <algorithm>
#include <image.h>
#include <memory>
#include <png.h>

Image::Image(int width, int height) {
    assert(0 < width);
    assert(0 < height);
    data_ = std::vector<std::vector<Color>>(height, std::vector<Color>(width));
}

const Color &Image::Get(int x, int y) const {
    return data_[y][x];
}

void Image::Set(int x, int y, const Color &color) {
    data_[y][x] = color;
}

bool Image::WritePngFile(const std::string &filename,
                         const bool vertical_flip) {
    std::unique_ptr<FILE, std::function<int(FILE *)>> file(
            fopen(filename.c_str(), "wb"), fclose);
    if (!file) {
        return false;
    }
    auto *png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr,
                                        nullptr);
    if (!png) {
        return false;
    }
    auto *info = png_create_info_struct(png);
    if (!info) {
        return false;
    }
    png_init_io(png, file.get());
    png_set_IHDR(png, info, Width(), Height(), 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    auto **data = new std::uint8_t *[Height()];
    for (int i = Height() - 1; 0 <= i; --i) {
        int line = vertical_flip ? (Height() - 1 - i) : i;
        data[line] = new std::uint8_t[3 * Width()];
        for (int j = 0; j < Width(); ++j) {
            std::uint8_t *pixel = &data[line][3 * j];
            for (int k = 0; k < 3; ++k) {
                pixel[k] = static_cast<std::uint8_t>(
                        255 * std::clamp(data_[i][j][k], 0.0, 1.0));
            }
        }
    }
    png_write_image(png, data);
    for (int i = 0; i < Height(); ++i) {
        delete[] data[i];
    }
    delete[] data;
    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    return true;
}

int Image::Width() const {
    return data_[0].size();
}

int Image::Height() const {
    return data_.size();
}

Image::~Image() = default;
