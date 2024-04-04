/*
** EPITECH PROJECT, 2024
** test_lib
** File description:
** LibNcurses
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include <ncurses.h>
    #include "../../includes/IDisplayModule.hpp"
    #include <fstream>

static const int BASE_X = 2;
static const int BASE_Y = 3;

static const std::string WINDOW_TITLE = "Arcade Ncurses";

namespace arcade
{
    class libNcurses : virtual public arcade::IDisplayModule{
        public:
            libNcurses();
            ~libNcurses();
            void init(const std::unordered_map<std::string, std::pair<Color, std::string>> pattern) override;
            void stop() override;
            void handleEvent(const std::string gameName) override;
            void displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) override;
            void displayMap(std::array<std::string, 23> map, std::size_t size) override;
            arcade::KeyPressed getKey() const override;
            void setKey(arcade::KeyPressed newValue) override;
            void changeColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap) override;
            std::string getPlayerName() const override;
        private:
            WINDOW *win;
            int x;
            int y;
            std::map<std::string, arcade::Color> charMap;
            std::string _gameName;
            std::string _playerName;
            arcade::KeyPressed _keyPressed;
            int pressedChar;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDiplay;

            void sortScore(std::size_t textSize);
            int getNumber(std::string);
            void addScoreTabToDisplay(void);
            void otherGetKey(void);
            void pickColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap);
            void color_remove(void);
            void checkTwoChar(std::size_t j, std::string str);
    };
};

extern "C" {
    arcade::IDisplayModule *entryPoint() {
        return (new arcade::libNcurses);
    }
}

#endif /* !SFML_HPP_ */
