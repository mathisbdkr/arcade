/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <string>
    #include "../lib/includes/IDisplayModule.hpp"
    #include "../lib/includes/KeyPressed.hpp"
    #include "../lib/includes/IGameModule.hpp"
    #include "../lib/includes/Color.hpp"
    #include <chrono>
    #include "dlLoader.hpp"
    #include <fstream>

class Core {
    public:
        Core(int argc, char **argv);
        ~Core();
        void gameLoop(void);
    private:
        arcade::IDisplayModule *_graphicalLib;
        arcade::IDisplayModule *_DefaultGraphicalLib;
        arcade::IGameModule *_gameLib;
        std::pair <arcade::IDisplayModule *,void *> _graphicalLibAndHandler;
        std::pair <arcade::IGameModule *,void *> _gameLibAndHandler;
        std::size_t _libGraphicalLen;
        std::size_t _libGameLen;
        int _graphicalLibIndex;
        int _gameLibIndex;
        arcade::KeyPressed _key;
        int _gameSpeed;
        DlLoader *_dlLoader;
        int pass = 0;
        std::string playerName;

        int closeEvent(void);
        void quitMenu(void);
        arcade::GameStatus winAndLooseEvent(arcade::GameStatus status);
        void changeGraphicalLib(void);
        void changeGameLib(void);
        int getLibIndex(std::string path);
        void changeLibrary();
        int changeLibIndex(int index, int change, std::size_t nbLib);
        void saveScore(std::string playerName, std::string gameName, std::size_t score);
};

#endif /* !CORE_HPP_ */
