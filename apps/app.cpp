#include <Eigen/Dense>
#include <camera.h>
#include <color.h>
#include <hittable.h>
#include <image.h>
#include <iostream>
#include <light.h>
#include <limits>
#include <ray.h>

template<typename Hittable>
Color RayColor(const Ray &ray, const Hittable &world) {
    HitRecord rec;
    if (Hit(ray, world, 0, std::numeric_limits<double>::max(), &rec)) {
        return Color(0.5 * (rec.normal_ + Eigen::Vector3d(1.0, 1.0, 1.0)));
    }
    Eigen::Vector3d direction = ray.direction_.normalized();
    auto t = 0.5 * (direction(1) + 1.0);
    return Color((1.0 - t) * Eigen::Vector3d(1.0, 1.0, 1.0) +
                 t * Eigen::Vector3d(0.5, 0.7, 1.0));
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    Image img(image_width, image_height);

    std::shared_ptr<Light> light = std::make_shared<PointLight>(
            Color(1, 1, 1), Eigen::Vector3d(0.5, 0.5, 0));

    // Camera
    const auto viewport_height = 2.0;
    const auto viewport_width = aspect_ratio * viewport_height;
    Camera camera({0, 0, 0}, {viewport_width, 0, 0}, {0, viewport_height, 0},
                  1.0);


    std::shared_ptr<Hittable> sphere0 = std::make_shared<Sphere>(
            Eigen::Vector3d{0.0, 0.0, -1.0}, 0.5,
            std::make_shared<Material>(Color(1, 0, 0)));
    std::shared_ptr<Hittable> sphere1 = std::make_shared<Sphere>(
            Eigen::Vector3d{0.0, -50.5, -1.0}, 50.0,
            std::make_shared<Material>(Color{0, 1, 0}));
    std::shared_ptr<Hittable> triangle = std::make_shared<Triangle>(
            Eigen::Vector3d{-0.5, 0, -0.5}, Eigen::Vector3d{0, 0.5, -2},
            Eigen::Vector3d{0.5, 0, -0.5},
            std::make_shared<Material>(Color(0, 0, 1)));
    HitList hit_list;
    hit_list.add(sphere0);
    hit_list.add(sphere1);
    hit_list.add(triangle);


    for (int y = 0; y < img.Height(); ++y) {
        for (int x = 0; x < img.Width(); ++x) {
            auto u = static_cast<double>(x) / (image_width - 1);
            auto v = static_cast<double>(y) / (image_height - 1);
            Ray ray = camera.GetRay(u, v);
            HitRecord rec;
            if (hit_list.Hit(ray, 0, std::numeric_limits<double>::max(),
                             &rec)) {
                img.Set(x, y, light->Illuminate(ray, rec));
            } else {
                Eigen::Vector3d direction = ray.direction_.normalized();
                auto t = 0.5 * (direction(1) + 1.0);
                img.Set(x, y,
                        Color((1.0 - t) * Eigen::Vector3d(1.0, 1.0, 1.0) +
                              t * Eigen::Vector3d(0.5, 0.7, 1.0)));
            }
        }
    }
    img.WritePngFile("a.png");
}
