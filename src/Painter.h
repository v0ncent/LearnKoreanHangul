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

        inline static bool wrongName[4]   = { false, false, false, false };
        inline static bool wrongStart[4]  = { false, false, false, false };
        inline static bool wrongMiddle[4] = { false, false, false, false };
        inline static bool wrongEnd[4]    = { false, false, false, false };

        inline static bool correctName[4]   = { false, false, false, false };
        inline static bool correctStart[4]  = { false, false, false, false };
        inline static bool correctMiddle[4] = { false, false, false, false };
        inline static bool correctEnd[4]    = { false, false, false, false };

        static inline auto hanguls = std::vector<Util::Hangul>();

        static inline auto nameOptions = std::vector<std::string>();
        static inline auto startPronunciationOptions = std::vector<std::string>();
        static inline auto middlePronunciationOptions = std::vector<std::string>();
        static inline auto endPronunciationsOptions = std::vector<std::string>();

        static inline bool nameAnswered = false;
        static inline bool startPronunciationAnswered = false;
        static inline bool middlePronunciationAnswered = false;
        static inline bool endPronunciationAnswered = false;

        static inline bool showMenu = false;
        static inline bool showBackToMenu = false;
        static inline bool showGame = false;
        static inline bool showEndScreen = false;

        static inline bool shouldPrepareQuestion = false;

        static inline bool shouldProceed = false;
        static inline bool timerRunning = false;

        static inline bool shouldProceedToMenu = false;
        static inline bool endTimerRunning = false;

        static inline int score = 0;

        static inline Util::Hangul currentHangul = {};

        static void paintMainMenu(bool* open);
        static void paintBackToMenu(bool* open);
        static void paintGame(bool* open);
        static void paintEndScreen(bool* open);

        static void shouldShowMenu(bool show);
        static void shouldShowBackToMenu(bool show);
        static void shouldPaintGame(bool paint);
        static void shouldShowEndScreen(bool show);
};

#endif //PAINTER_H
