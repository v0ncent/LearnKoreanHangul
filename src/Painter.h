#ifndef PAINTER_H
#define PAINTER_H

#include <vector>

#include "Util.h"

class Painter {
    public:
        static inline std::vector<Util::Hangul> hangulImages = std::vector<Util::Hangul>();

        static inline bool showMenu = false;
        static inline bool showBackToMenu = false;
        static inline bool showGame = false;

        static void paintMainMenu(bool* open);
        static void paintBackToMenu(bool* open);
        static void paintGame(bool* open);

        static void shouldShowMenu(bool show);
        static void shouldShowBackToMenu(bool show);
        static void shouldPaintGame(bool paint);
};

#endif //PAINTER_H
