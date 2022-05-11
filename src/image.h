#ifndef CG_EXAMPLE_SRC_IMAGE_H_
#define CG_EXAMPLE_SRC_IMAGE_H_

#include "color.h"
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

    ~Image();

private:
    std::vector<std::vector<Color>> data_;
};


#endif//CG_EXAMPLE_SRC_IMAGE_H_
