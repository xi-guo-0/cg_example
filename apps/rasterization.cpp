#include <array>
#include <image.h>
#include <mesh.h>
#include <random>

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1080;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 10;
    Image img(image_width, image_height);

    Mesh mesh("figure.obj");

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < mesh.nfaces(); ++i) {
        std::array<Eigen::Vector2i, 3> coors;
        for (int j = 0; j < 3; ++j) {
            Eigen::Vector3d v = mesh.vert(i, j);
            coors[j] = Eigen::Vector2i{(v.x() + 1.0) * image_width / 2,
                                       (v.y() + 1.0) * image_height / 2};
        }

        img.Triangle(coors[0], coors[1], coors[2],
                     Color{dis(gen), dis(gen), dis(gen), 1.0});
    }
    img.WritePngFile("b.png");
}
