#ifndef CG_EXAMPLE_SRC_IMAGE_H_
#define CG_EXAMPLE_SRC_IMAGE_H_

#include <cstdint>
#include <png.h>
#include <string>
#include <vector>

struct Color {
    union {
        std::uint8_t rgba[4]{};
        struct {
            std::uint8_t r;
            std::uint8_t g;
            std::uint8_t b;
            std::uint8_t a;
        };
    };

    Color() = default;

    Color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b,
          const uint8_t a)
        : rgba{r, g, b, a} {
    }
};

class Image {
public:
    Image(int w, int h);

    Color Get(int x, int y) const;

    void Set(int x, int y, const Color &color);

    bool WritePngFile(const std::string &filename, bool vertical_flip = true);

    int Width() const;

    int Height() const;

    ~Image();

private:
    int w_;
    int h_;
    std::uint8_t **data_;
};


#endif//CG_EXAMPLE_SRC_IMAGE_H_
