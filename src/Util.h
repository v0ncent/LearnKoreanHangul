#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>


class Util {
    public:
        struct ImageData {
            int width;
            int height;
            int channels;
            unsigned char* data;
            std::string path;
        };

        static std::vector<ImageData> load_images(const std::string& path);
};

#endif //UTIL_H
