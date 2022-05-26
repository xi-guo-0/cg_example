#include <image.h>

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 10;
    Image img(image_width, image_height);
    img.Line(0, 0, 100, 100, Color(1, 0, 0, 1));
    img.WritePngFile("b.png");
}
