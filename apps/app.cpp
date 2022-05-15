#include <Eigen/Dense>
#include <camera.h>
#include <color.h>
#include <hittable.h>
#include <image.h>
#include <iostream>
#include <light.h>
#include <limits>
#include <ray.h>

#include <random>
double RandomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

template<typename Hittable>
Color RayColor(const Ray &ray, const std::shared_ptr<Light> light,
               const Hittable &world, const int times) {
    HitRecord rec;
    Color c;
    if (world.Hit(ray, std::numeric_limits<double>::epsilon(),
                  std::numeric_limits<double>::max(), &rec)) {
        c = light->Illuminate(ray, rec);
        if (0 < times) {
            c += RayColor(
                    Ray(rec.point_,
                        (ray.direction_ -
                         2 * (ray.direction_.dot(rec.normal_)) * rec.normal_)),
                    light, world, times - 1);
        }
    } else {
        c = {0, 0, 0};
    }
    return c;
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 10;
    Image img(image_width, image_height);

    std::shared_ptr<Light> light = std::make_shared<PointLight>(
            Color(1, 1, 1), Eigen::Vector3d(1, 1, 0));

    // Camera
    const auto viewport_height = 2.0;
    const auto viewport_width = aspect_ratio * viewport_height;
    Camera camera({0, 0, 0}, {viewport_width, 0, 0}, {0, viewport_height, 0},
                  1.0);


    std::shared_ptr<Hittable> sphere0 = std::make_shared<Sphere>(
            Eigen::Vector3d{-0.6, 0.0, -1.0}, 0.5,
            std::make_shared<Material>(Color(0.2, 0.1, 0.1), 55, 0.99, 5));
    std::shared_ptr<Hittable> sphere1 = std::make_shared<Sphere>(
            Eigen::Vector3d{0.6, 0.0, -1.0}, 0.5,
            std::make_shared<Material>(Color{0.1, 0.2, 0.1}, 25, 0.99, 5));
    std::shared_ptr<Hittable> sphere2 = std::make_shared<Sphere>(
            Eigen::Vector3d{0.0, -50.5, -1.0}, 50.0,
            std::make_shared<Material>(Color{0.1, 0.1, 0.2}, 25, 0.99, 10));
    std::shared_ptr<Hittable> triangle = std::make_shared<Triangle>(
            Eigen::Vector3d{-0.5, 0, -0.5}, Eigen::Vector3d{0, 0.5, -2},
            Eigen::Vector3d{0.5, 0, -0.5},
            std::make_shared<Material>(Color(0, 0, 1), 38, 0.99, 10000));
    HitList hit_list;
    hit_list.add(sphere0);
    hit_list.add(sphere1);
    hit_list.add(sphere2);
    // hit_list.add(triangle);


    for (int y = 0; y < img.Height(); ++y) {
        for (int x = 0; x < img.Width(); ++x) {
            Color c;
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (x + RandomDouble()) / (image_width - 1);
                auto v = (y + RandomDouble()) / (image_height - 1);
                Ray ray = camera.GetRay(u, v);
                c += RayColor(ray, light, hit_list, 5);
            }
            c /= samples_per_pixel;
            img.Set(x, y, c);
        }
    }
    img.WritePngFile("a.png");
}
