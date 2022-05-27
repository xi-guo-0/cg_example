#ifndef CG_EXAMPLE_SRC_IMAGE_H_
#define CG_EXAMPLE_SRC_IMAGE_H_

#include <color.h>
#include <cstdint>
#include <png.h>
#include <string>
#include <vector>


class Image {
public:
    Image(int width, int height);

    const Color &Get(int x, int y) const;

    void Set(int x, int y, const Color &color);

    bool WritePngFile(const std::string &filename, bool vertical_flip = true);

    int Width() const;

    int Height() const;

    void Line(int x0, int y0, int x1, int y1, const Color &color);

    void Line(const Eigen::Vector2i &a, const Eigen::Vector2i &b,
              const Color &color);

    void Triangle(Eigen::Vector2i a, Eigen::Vector2i b, Eigen::Vector2i c,
                  const Color &color);

    ~Image();

private:
    std::vector<std::vector<Color>> data_;
};


#endif//CG_EXAMPLE_SRC_IMAGE_H_
