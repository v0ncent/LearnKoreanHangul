#include <filesystem>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Util.h"

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

    // this alphabet is so fucking long
    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "giyeok.PNG"),
            "giyok",
            "k (walk)",
            "g (ghost)",
            "k (walk)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "ssang-giyeok.PNG"),
            "ssang-giyeok",
            "g (gone)",
            "g (gone)",
            "g (gone)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "nieun.PNG"),
            "nieun",
            "n (now)",
            "n (now)",
            "n (now)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "digeut.PNG"),
            "digeut",
            "t (talk)",
            "d (mind)",
            "t (talk)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "ssang-digeut.PNG"),
            "ssang-digeut",
            "d (dog)",
            "d (dog)",
            "d (dog)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "rieul.PNG"),
            "rieul",
            "r (run)",
            "r (run)",
            "l (real)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "mieum.PNG"),
            "mieum",
            "m (mop)",
            "m (mop)",
            "m (mop)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "bieup.PNG"),
            "bieup",
            "p (pool)",
            "b (bay)",
            "p (pool)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "ssang-bieup.PNG"),
            "ssang-bieup",
            "b (bird)",
            "b (bird)",
            "b (bird)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "siot.PNG"),
            "siot",
            "s (show)",
            "s (show)",
            "t (hot)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "ssang-siot.PNG"),
            "ssang-siot",
            "s (sun)",
            "s (sun)",
            "t (hot)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "ieung.PNG"),
            "ieung",
            "silent",
            "silent",
            "ng (ring)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "jieut.PNG"),
            "jieut",
            "ch (chop)",
            "j (jar)",
            "t (hot)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "ssang-jieut.PNG"),
            "ssang-jieut",
            "j (jim)",
            "j (jim)",
            "t (hot)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "chieut.PNG"),
            "chieut",
            "ch (itch)",
            "ch (itch)",
            "t (hot)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "kieuk.PNG"),
            "kieuk",
            "kh (khaki)",
            "kh (khaki)",
            "kh (khaki)",
            false
        }
        );

    hanguls.push_back(
        {
            loadImage(hangulPath.string() + "/" + "tieut.PNG"),
            "tieut",
            "t (tip)",
            "t (tip)",
            "t (tip)",
            false
        }
        );

    hanguls.push_back(
    {
        loadImage(hangulPath.string() + "/" + "pieup.PNG"),
        "pieup",
        "p (pit)",
        "p (pit)",
        "p (pit)",
        false
    }
    );

    hanguls.push_back(
        {
        loadImage(hangulPath.string() + "/" + "hieut.PNG"),
        "hieut",
        "h (hot)",
        "h (hot)",
        "silent",
        false
    }
    );

    hanguls.push_back(
{
    loadImage(hangulPath.string() + "/" + "a.PNG"),
    "a",
    "ah (rah)",
    "ah (rah)",
    "ah (rah)",
    false
    }
    );

    hanguls.push_back(
{
    loadImage(hangulPath.string() + "/" + "eo.PNG"),
    "eo",
    "uh (run)",
    "uh (run)",
    "uh (run)",
    false
    }
    );

    hanguls.push_back(
{
    loadImage(hangulPath.string() + "/" + "o.PNG"),
    "o",
    "oh (dough)",
    "oh (dough)",
    "oh (dough)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "u.PNG"),
    "u",
    "oo (moon)",
    "oo (moon)",
    "oo (moon)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "eu.PNG"),
    "eu",
    "uh (brook)",
    "uh (brook)",
    "uh (brook)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "i.PNG"),
    "i",
    "ee (meek)",
    "ee (meek)",
    "ee (meek)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "ae.PNG"),
    "ae",
    "ae (at)",
    "ae (at)",
    "ae (at)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "e.PNG"),
    "e",
    "eh (met)",
    "eh (met)",
    "eh (met)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "ya.PNG"),
    "ya",
    "yah (yawn)",
    "yah (yawn)",
    "yah (yawn)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "e.PNG"),
    "e",
    "eh (met)",
    "eh (met)",
    "eh (met)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "yeo.PNG"),
    "yeo",
    "yuh (yum)",
    "yuh (yum)",
    "yuh (yum)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "yo.PNG"),
    "yo",
    "yoh (yodel)",
    "yoh (yodel)",
    "yoh (yodel)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "yu.PNG"),
    "yu",
    "yoo (view)",
    "yoo (view)",
    "yoo (view)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "yae.PNG"),
    "yae",
    "yae (yak)",
    "yae (yak)",
    "yae (yak)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "ye.PNG"),
    "ye",
    "yeh (yes)",
    "yeh (yes)",
    "yeh (yes)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "wa.PNG"),
    "wa",
    "wah (wand)",
    "wah (wand)",
    "wah (wand)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "wae.PNG"),
    "wae",
    "wae (wax)",
    "wae (wax)",
    "wae (wax)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "wo.PNG"),
    "wo",
    "wuh (wonder)",
    "wuh (wonder)",
    "wuh (wonder)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "we.PNG"),
    "we",
    "weh (web)",
    "weh (web)",
    "weh (web)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "oe.PNG"),
    "oe",
    "way (wait)",
    "way (wait)",
    "way (wait)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "wi.PNG"),
    "wi",
    "wee (week)",
    "wee (week)",
    "wee (week)",
    false
    }
    );

    hanguls.push_back(
    {
    loadImage(hangulPath.string() + "/" + "ui.PNG"),
    "ui",
    "uey (muey)",
    "uey (muey)",
    "uey (muey)",
    false
    }
    );





    return hanguls;
}
