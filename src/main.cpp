#include "hittable.h"
#include "image.h"
#include "ray.h"
#include "vec.h"
#include <limits>

template<typename Hittable>
Color RayColor(const Ray &ray, const Hittable &world) {
    HitRecord rec;
    if (Hit(ray, world, 0, std::numeric_limits<double>::max(), &rec)) {
        return Color(0.5 * (rec.normal_ + Vec3d(1.0, 1.0, 1.0)));
    }
    Vec3d direction = ray.direction_.Normalized();
    auto t = 0.5 * (direction.y_ + 1.0);
    return Color((1.0 - t) * Vec3d(1.0, 1.0, 1.0) + t * Vec3d(0.5, 0.7, 1.0));
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    Image img(image_width, image_height);


    // Camera
    const auto viewport_height = 2.0;
    const auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Vec3d(0.0, 0.0, 0.0);
    auto horizontal = Vec3d(viewport_width, 0.0, 0.0);
    auto vertical = Vec3d(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 -
                             Vec3d(0.0, 0.0, focal_length);


    Sphere sphere0({0.0, 0.0, -1.0}, 0.5);
    Sphere sphere1({0.0, -50.5, -1.0}, 50.0);
    std::vector<Sphere> spheres{sphere0, sphere1};
    for (int y = 0; y < img.Height(); ++y) {
        for (int x = 0; x < img.Width(); ++x) {
            auto u = static_cast<double>(x) / (image_width - 1);
            auto v = static_cast<double>(y) / (image_height - 1);
            Ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
            img.Set(x, y, RayColor(ray, spheres));
        }
    }
    img.WritePngFile("a.png");
}
