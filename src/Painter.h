#ifndef PAINTER_H
#define PAINTER_H

class Painter {
    public:
        static inline bool showMenu = false;
        static void paintMainMenu(bool* open);
        static void shouldShowMenu(bool show);
};

#endif //PAINTER_H
