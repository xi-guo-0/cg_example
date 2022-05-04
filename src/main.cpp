#include "image.h"
#include "ray.h"
#include "sphere.h"
#include "vec.h"

int main() {
    Vec3d origin = Vec3d{128.0, 128.0, 16.0};
    Sphere sphere({128.0, 128.0, -32.0}, 32.0);
    Image img(256, 256);
    for (int y = 0; y < img.Height(); ++y) {
        for (int x = 0; x < img.Width(); ++x) {
            Ray ray(origin, Vec3d{x - origin.x_, y - origin.y_, 0 - origin.z_});
            double t0;
            if (sphere.Hit(ray, &t0)) {
                img.Set(x, y, {255, 0, 0, 255});
            } else {
                img.Set(x, y, {0, 0, 0, 255});
            }
        }
    }
    img.WritePngFile("a.png");
}
