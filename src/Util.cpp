#include <filesystem>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Util.h"
#include "Constants.h"

Util::ImageData Util::loadImage(const std::string &path) {
    int w, h, ch;
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &ch, 4);

    if (!data) {
        std::cerr << "Failed to load " << path << std::endl;
        return {};
    }

    return {w, h, ch, data};
}

std::vector<Util::Hangul> Util::loadHanguls() {
    const std::filesystem::path projectRoot = std::filesystem::current_path().parent_path();
    const auto hangulPath = projectRoot / "hangul";

    std::vector<Hangul> hanguls;

    if (!exists(hangulPath)) {
        std::cerr << "Failed to load " << hangulPath << std::endl;
        return {};
    }

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_GIYEOK),
                        STR_GIYEOK, PRON_GIYEOK_INIT, PRON_GIYEOK_MED, PRON_GIYEOK_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_SSANG_GIYEOK),
                        STR_SSANG_GIYEOK, PRON_SSANG_GIYEOK, PRON_SSANG_GIYEOK, PRON_SSANG_GIYEOK, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_NIEUN),
                        STR_NIEUN, PRON_NIEUN, PRON_NIEUN, PRON_NIEUN, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_DIGEUT),
                        STR_DIGEUT, PRON_DIGEUT_INIT, PRON_DIGEUT_MED, PRON_DIGEUT_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_SSANG_DIGEUT),
                        STR_SSANG_DIGEUT, PRON_SSANG_DIGEUT, PRON_SSANG_DIGEUT, PRON_SSANG_DIGEUT, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_RIEUL),
                        STR_RIEUL, PRON_RIEUL_INIT, PRON_RIEUL_MED, PRON_RIEUL_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_MIEUM),
                        STR_MIEUM, PRON_MIEUM, PRON_MIEUM, PRON_MIEUM, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_BIEUP),
                        STR_BIEUP, PRON_BIEUP_INIT, PRON_BIEUP_MED, PRON_BIEUP_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_SSANG_BIEUP),
                        STR_SSANG_BIEUP, PRON_SSANG_BIEUP, PRON_SSANG_BIEUP, PRON_SSANG_BIEUP, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_SIOT),
                        STR_SIOT, PRON_SIOT_INIT, PRON_SIOT_MED, PRON_SIOT_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_SSANG_SIOT),
                        STR_SSANG_SIOT, PRON_SSANG_SIOT_INIT, PRON_SSANG_SIOT_MED, PRON_SSANG_SIOT_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_IEUNG),
                        STR_IEUNG, PRON_IEUNG_INIT, PRON_IEUNG_MED, PRON_IEUNG_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_JIEUT),
                        STR_JIEUT, PRON_JIEUT_INIT, PRON_JIEUT_MED, PRON_JIEUT_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_SSANG_JIEUT),
                        STR_SSANG_JIEUT, PRON_SSANG_JIEUT_INIT, PRON_SSANG_JIEUT_MED, PRON_SSANG_JIEUT_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_CHIEUT),
                        STR_CHIEUT, PRON_CHIEUT_INIT, PRON_CHIEUT_MED, PRON_CHIEUT_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_KIEUK),
                        STR_KIEUK, PRON_KIEUK, PRON_KIEUK, PRON_KIEUK, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_TIEUT),
                        STR_TIEUT, PRON_TIEUT, PRON_TIEUT, PRON_TIEUT, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_PIEUP),
                        STR_PIEUP, PRON_PIEUP, PRON_PIEUP, PRON_PIEUP, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_HIEUT),
                        STR_HIEUT, PRON_HIEUT_INIT, PRON_HIEUT_MED, PRON_HIEUT_FINAL, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_A),
                        STR_A, PRON_A, PRON_A, PRON_A, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_EO),
                        STR_EO, PRON_EO, PRON_EO, PRON_EO, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_O),
                        STR_O, PRON_O, PRON_O, PRON_O, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_U),
                        STR_U, PRON_U, PRON_U, PRON_U, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_EU),
                        STR_EU, PRON_EU, PRON_EU, PRON_EU, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_I),
                        STR_I, PRON_I, PRON_I, PRON_I, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_AE),
                        STR_AE, PRON_AE, PRON_AE, PRON_AE, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_E),
                        STR_E, PRON_E, PRON_E, PRON_E, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_YA),
                        STR_YA, PRON_YA, PRON_YA, PRON_YA, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_YEO),
                        STR_YEO, PRON_YEO, PRON_YEO, PRON_YEO, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_YO),
                        STR_YO, PRON_YO, PRON_YO, PRON_YO, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_YU),
                        STR_YU, PRON_YU, PRON_YU, PRON_YU, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_YAE),
                        STR_YAE, PRON_YAE, PRON_YAE, PRON_YAE, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_YE),
                        STR_YE, PRON_YE, PRON_YE, PRON_YE, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_WA),
                        STR_WA, PRON_WA, PRON_WA, PRON_WA, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_WAE),
                        STR_WAE, PRON_WAE, PRON_WAE, PRON_WAE, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_WO),
                        STR_WO, PRON_WO, PRON_WO, PRON_WO, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_WE),
                        STR_WE, PRON_WE, PRON_WE, PRON_WE, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_OE),
                        STR_OE, PRON_OE, PRON_OE, PRON_OE, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_WI),
                        STR_WI, PRON_WI, PRON_WI, PRON_WI, false });

    hanguls.push_back({ loadImage(hangulPath.string() + "/" + IMG_UI),
                        STR_UI, PRON_UI, PRON_UI, PRON_UI, false });

    return hanguls;
}

