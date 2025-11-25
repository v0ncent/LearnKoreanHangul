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

        static inline auto nameOptions = std::vector<std::string>();
        static inline auto startPronunciationOptions = std::vector<std::string>();
        static inline auto middlePronunciationOptions = std::vector<std::string>();
        static inline auto endPronunciationsOptions = std::vector<std::string>();

        static inline bool nameAnswerd = false;
        static inline bool startPronunciationAnswerd = false;
        static inline bool middlePronunciationAnswerd = false;
        static inline bool endPronunciationAnswerd = false;

        static inline bool showMenu = false;
        static inline bool showBackToMenu = false;
        static inline bool showGame = false;
        static inline bool showOptions = false;

        static inline bool shouldPrepareQuestion = false;

        static inline int score = 0;

        static inline Util::Hangul currentHangul = {};

        static void paintMainMenu(bool* open);
        static void paintBackToMenu(bool* open);
        static void paintGame(bool* open);

        static void shouldShowMenu(bool show);
        static void shouldShowBackToMenu(bool show);
        static void shouldPaintGame(bool paint);
        static void shouldShowOptions(bool show);
};

#endif //PAINTER_H
