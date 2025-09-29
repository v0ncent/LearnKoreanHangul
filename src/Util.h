#ifndef UTIL_H
#define UTIL_H

#include <GL/gl.h>

#include <string>
#include <vector>

class Util {
    public:
        static inline int shownHangul = 0;

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

            bool empty() const {
                return name.empty() && image.data == nullptr && image.width == 0 && image.height == 0;
            }
        };

        static ImageData loadImage(const std::string& path);
        static std::vector<Hangul> loadHanguls();
        static Hangul getRandomHangul();
        static void resetGame();
        static void initGame();
        static GLuint createTextureFromImage(const ImageData& image);
};

#endif
