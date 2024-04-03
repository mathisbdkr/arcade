/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** DlLoader
*/

#ifndef DLLOADER_HPP_
    #define DLLOADER_HPP_
    #include <dlfcn.h>
    #include <string>
    #include "../lib/includes/IDisplayModule.hpp"
    #include "../lib/includes/IGameModule.hpp"
    #include <dirent.h>
    #include <deque>

static const int NB_LIB_GRAPHICAL = 13;
static const int NB_LIB_GAME = 7;

static std::string allGraphicalLibraryPath[NB_LIB_GRAPHICAL] = {
    "arcade_sfml.so",
    "arcade_sdl2.so",
    "arcade_ncurses.so",
    "arcade_qt5.so",
    "arcade_ndk++.so",
    "arcade_aalib.so",
    "arcade_libcaca.so",
    "arcade_allegro5.so",
    "arcade_xlib.so",
    "arcade_gtk+.so",
    "arcade_irrlicht.so",
    "arcade_opengl.so",
    "arcade_vulkan.so"
};

static std::string allGameLibraryPath[NB_LIB_GAME] = {
    "arcade_snake.so",
    "arcade_nibbler.so",
    "arcade_pacman.so",
    "arcade_qix.so",
    "arcade_centipede.so",
    "arcade_solarfox.so"
};

class DlLoader {
    public:
        DlLoader() {};
        ~DlLoader() {};
        std::vector <std::string> getGraphicalPath(void);
        std::vector <std::string> getGamePath(void);
        std::pair <arcade::IDisplayModule *,void *>getAIDisplayModule(int index);
        std::pair <arcade::IGameModule *,void *> getAIGameModule(int index);
    private:
        std::deque<std::string> allLibAvailable (void);
        bool isGraphicalLibExist(std::string path);
        bool isGameLibExist(std::string path);
        bool isALib (std::string path);
        void entryPointGraphical(std::string path);
        void entryPointGame(std::string path);

        std::pair <arcade::IDisplayModule *,void *> _IDisplayModulePair;
        std::pair <arcade::IGameModule *,void *> _IGameModulePair;
};


#endif /* !DLLOADER_HPP_ */
