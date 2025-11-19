#ifndef PAINTER_H
#define PAINTER_H

#include <vector>

#include "Util.h"

class Painter {
    public:
        struct Answer {
            std::string content;
            bool answer;
        };

        static inline auto hanguls = std::vector<Util::Hangul>();

        static inline auto randomNames = std::vector<std::string>();
        static inline auto randomStartPronunciations = std::vector<std::string>();
        static inline auto randomMiddlePronunciations = std::vector<std::string>();
        static inline auto randomEndPronunciations = std::vector<std::string>();

        static inline bool showMenu = false;
        static inline bool showBackToMenu = false;
        static inline bool showGame = false;
        static inline bool showOptions = false;

        static inline bool running = false;

        static inline int score = 0;

        static inline Util::Hangul currentHangul = {};

        static void paintMainMenu(bool* open);
        static void paintBackToMenu(bool* open);
        static void paintGame(bool* open);

        static void shouldShowMenu(bool show);
        static void shouldShowBackToMenu(bool show);
        static void shouldPaintGame(bool paint);
};

#endif //PAINTER_H
