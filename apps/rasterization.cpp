#include <array>
#include <image.h>
#include <mesh.h>
#include <numbers>
#include <random>

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1080;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 10;
    Image img(image_width, image_height);

    Mesh mesh("figure.obj");

    Eigen::Vector3d light_dir{0, 0, -1};


    auto rotate_x = Eigen::AngleAxis<double>(std::numbers::pi * 18 / 12.0,
                                             Eigen::Vector3d{1, 0, 0});

    for (int i = 0; i < mesh.nfaces(); ++i) {
        std::array<Eigen::Vector2i, 3> coors;
        std::array<Eigen::Vector3d, 3> world_coors;
        for (int j = 0; j < 3; ++j) {
            Eigen::Vector3d v = rotate_x * mesh.vert(i, j);
            coors[j] = Eigen::Vector2i{(v.x() + 1.0) * image_width / 2,
                                       (v.y() + 1.0) * image_height / 2};
            world_coors[j] = v;
        }
        Eigen::Vector3d n = (world_coors[2] - world_coors[0])
                                    .cross(world_coors[1] - world_coors[0])
                                    .normalized();
        double intensity = n.dot(light_dir);

        if (0.0 < intensity) {
            img.Triangle(coors[0], coors[1], coors[2],
                         Color{intensity, intensity, intensity, 1.0});
        }
    }
    img.WritePngFile("b.png");
}
