#include "image.h"

int main() {
    Image img(256, 128);
    for (int y = 0; y < img.Height(); ++y) {
        for (int x = 0; x < img.Width(); ++x) {
            img.Set(x, y, {static_cast<std::uint8_t>(x), static_cast<std::uint8_t>(y), 0, 255});
        }
    }
    img.WritePngFile("a.png");
}
