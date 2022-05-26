#include <image.h>
#include <mesh.h>

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1080;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 10;
    Image img(image_width, image_height);

    Mesh mesh("figure.obj");

    for (int i = 0; i < mesh.nfaces(); ++i) {
        Eigen::Vector3d v0 = mesh.vert(i, 0);
        Eigen::Vector3d v1 = mesh.vert(i, 1);
        int x0 = (v0.x() + 1.) * image_width / 2.;
        int y0 = (v0.y() + 1.) * image_height / 2.;
        int x1 = (v1.x() + 1.) * image_width / 2.;
        int y1 = (v1.y() + 1.) * image_height / 2.;
        img.Line(x0, y0, x1, y1, Color{1, 1, 1, 1});
    }
    img.WritePngFile("b.png");
}
