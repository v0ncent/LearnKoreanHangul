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

        // keep in here to avoid circular imports
        struct Hangul {
            ImageData image;
            std::string name;
            std::string startPronunciation;
            std::string middlePronunciation;
            std::string endPronunciation;
            bool shown;
        };

        static ImageData loadImage(const std::string& path);
        static std::vector<Hangul> loadHanguls();
};

#endif
