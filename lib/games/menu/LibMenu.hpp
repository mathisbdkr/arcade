/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** LibMenu
*/

#ifndef LIBMENU_HPP_
#define LIBMENU_HPP_

#include "../../includes/IGameModule.hpp"
#include <string>

namespace arcade {
    class LibMenu : virtual public arcade::IGameModule {
        public:
            LibMenu();
            ~LibMenu() {};
            void resetGame() override;
            std::array<std::string, 23> getMap() const override;
            std::size_t getMapCellSize() const override;
            std::unordered_map<std::string, std::pair<Color, std::string>> getPattern() const override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() const override;
            void incrementTime() override {};
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::pair<std::size_t, std::size_t> getIndexes() const override;
            void initText(const std::vector<std::string>, const std::vector<std::string>) override;
            std::string getGameName() const override;
            std::size_t getScore() const override;
        private:
            std::vector<std::string> _gameLibName;
            std::vector<std::string> _graphicalName;
            std::array<std::string, 23> map;
            std::size_t _SelectedGameIndex;
            std::size_t _SelectedLibIndex;
            int _libTypeSelected;

            int changeLibIndex(int index, int change, int nbLib);
    };
}

extern "C" {
    arcade::IGameModule *entryPoint() {
        return (new arcade::LibMenu);
    }
}

#endif /* !LIBMENU_HPP_ */
