#include <array>
#include <image.h>
#include <mesh.h>
#include <numbers>
#include <random>

void Rasterize(const Triangle &triangle, Image *img) {
    Eigen::Vector3d light_dir{0, 0, -1};
    std::array<Eigen::Vector2i, 3> coors;
    coors[0] = Eigen::Vector2i{(triangle.a().x() + 1.0) * img->Width() / 2,
                               (triangle.a().y() + 1.0) * img->Height() / 2};
    coors[1] = Eigen::Vector2i{(triangle.b().x() + 1.0) * img->Width() / 2,
                               (triangle.b().y() + 1.0) * img->Height() / 2};
    coors[2] = Eigen::Vector2i{(triangle.c().x() + 1.0) * img->Width() / 2,
                               (triangle.c().y() + 1.0) * img->Height() / 2};

    Eigen::Vector3d n = (triangle.c() - triangle.a())
                                .cross(triangle.b() - triangle.c())
                                .normalized();
    double intensity = n.dot(light_dir);

    if (0.0 < intensity) {
        img->Triangle(coors[0], coors[1], coors[2],
                      Color{intensity, intensity, intensity, 1.0});
    }
}

void Draw(const BspTree::Node *node, const Eigen::Vector3d &e, Image *img) {
    if (node->f(e) < 0) {
        if (node->right_) { Draw(node->right_, e, img); }
        Rasterize(node->triangle_, img);
        if (node->left_) { Draw(node->left_, e, img); }
    } else {
        if (node->left_) { Draw(node->left_, e, img); }
        Rasterize(node->triangle_, img);
        if (node->right_) { Draw(node->right_, e, img); }
    }
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1080;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 10;
    Image img(image_width, image_height);

    Mesh mesh("figure.obj");


    auto rotate_x = Eigen::AngleAxis<double>(std::numbers::pi * 18 / 12.0,
                                             Eigen::Vector3d{1, 0, 0});

    BspTree tree;

    for (int i = 0; i < mesh.nfaces(); ++i) {
        std::array<Eigen::Vector3d, 3> world_coors;
        for (int j = 0; j < 3; ++j) {
            Eigen::Vector3d v = rotate_x * mesh.vert(i, j);
            world_coors[j] = v;
        }
        Triangle triangle(
                world_coors[0], world_coors[1], world_coors[2],
                std::make_shared<Material>(Color(0, 0, 1, 1), 38, 0.99, 10000));
        tree.Add(triangle);
    }
    Draw(tree.root, Eigen::Vector3d{0, 0, 2}, &img);
    img.WritePngFile("b.png");
}
