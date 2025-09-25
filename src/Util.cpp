#include "Util.h"
#include <iostream>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::vector<Util::ImageData> Util::load_images(const std::string &path) {
    std::vector<ImageData> images;

    for (const auto& entry : std::filesystem::__cxx11::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".PNG") {
            const std::string filePath = entry.path().string();

            int w, h, ch;
            unsigned char* data = stbi_load(filePath.c_str(), &w, &h, &ch, 4);
            if (!data) {
                std::cerr << "Failed to load " << filePath << std::endl;
                continue;
            }

            images.push_back({ w, h, ch, data, filePath });
        }
    }

    return images;
}
