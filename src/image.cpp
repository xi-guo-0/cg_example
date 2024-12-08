#include <algorithm>
#include <image.h>
#include <memory>

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

bool Image::WritePngFile(const std::string &filename, bool vertical_flip) {

    std::unique_ptr<FILE, std::function<int(FILE *)>> file(
            fopen(filename.c_str(), "wb"), fclose);
    if (!file) {
        return false;
    }

    uint8_t *output_data = nullptr;

    std::vector<uint8_t> data(Width() * Height() * 3);

    for (int i = Height() - 1; 0 <= i; --i) {
        int line = vertical_flip ? (Height() - 1 - i) : i;
        for (int j = 0; j < Width(); ++j) {
            std::uint8_t *pixel = &data[line * Width() * 3 + 3 * j];
            for (int k = 0; k < 3; ++k) {
                pixel[k] = static_cast<std::uint8_t>(
                        255 * std::clamp(data_[i][j][k], 0.0, 1.0));
            }
        }
    }

    size_t output_size = WebPEncodeLosslessRGB(data.data(), Width(), Height(),
                                               3 * Width(), &output_data);

    fwrite(output_data, 1, output_size, file.get());

    WebPFree(output_data);

    return true;
}

int Image::Width() const {
    return data_[0].size();
}

int Image::Height() const {
    return data_.size();
}

Image::~Image() = default;
