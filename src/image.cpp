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
    if (!file) { return false; }
    auto *png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr,
                                        nullptr);
    if (!png) { return false; }
    auto *info = png_create_info_struct(png);
    if (!info) { return false; }
    png_init_io(png, file.get());
    png_set_IHDR(png, info, Width(), Height(), 8, PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    auto **data = new std::uint8_t *[Height()];
    for (int i = Height() - 1; 0 <= i; --i) {
        int line = vertical_flip ? (Height() - 1 - i) : i;
        data[line] = new std::uint8_t[4 * Width()];
        for (int j = 0; j < Width(); ++j) {
            std::uint8_t *pixel = &data[line][4 * j];
            for (int k = 0; k < 4; ++k) {
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
void Image::Line(int x0, int y0, int x1, int y1, const Color &color) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x1 < x0) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; ++x) {
        if (steep) {
            Set(y, x, color);
        } else {
            Set(x, y, color);
        }
        error2 += derror2;
        if (dx < error2) {
            y += (y0 < y1 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

void Image::Line(const Eigen::Vector2i &a, const Eigen::Vector2i &b,
                 const Color &color) {
    Line(a.x(), a.y(), b.x(), b.y(), color);
}

void Image::Triangle(Eigen::Vector2i a, Eigen::Vector2i b, Eigen::Vector2i c,
                     const Color &color) {
    if (a.y() == b.y() && a.y() == c.y()) { return; }
    if (b.y() < a.y()) { std::swap(a, b); }
    if (c.y() < a.y()) { std::swap(a, c); }
    if (c.y() < b.y()) { std::swap(b, c); }
    int total_height = c.y() - a.y();
    for (int i = 0; i < total_height; ++i) {
        bool is_second_half = (b.y() - a.y() < i) || a.y() == b.y();
        int segment_height = is_second_half ? c.y() - b.y() : b.y() - a.y();
        double alpha = static_cast<double>(i) / total_height;
        double beta =
                static_cast<double>(i - (is_second_half ? b.y() - a.y() : 0)) /
                segment_height;
        Eigen::Vector2i left{static_cast<int>(a.x() + (c.x() - a.x()) * alpha),
                             static_cast<int>(a.y() + (c.y() - a.y()) * alpha)};

        Eigen::Vector2i right{static_cast<int>(a.x() + (b.x() - a.x()) * beta),
                              static_cast<int>(a.y() + (b.y() - a.y()) * beta)};
        if (is_second_half) {
            right = Eigen::Vector2i{
                    static_cast<int>(b.x() + (c.x() - b.x()) * beta),
                    static_cast<int>(b.y() + (c.y() - b.y()) * beta)};
        }
        if (right.x() < left.x()) { std::swap(left, right); }
        for (int j = left.x(); j <= right.x(); ++j) {
            Set(j, a.y() + i, color);
        }
    }
}

Image::~Image() = default;
