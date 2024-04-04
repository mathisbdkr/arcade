/*
** EPITECH PROJECT, 2024
** test_lib
** File description:
** libSdl
*/

#ifndef libSdl_HPP_
    #define libSdl_HPP_

    #include "../../includes/IDisplayModule.hpp"
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_image.h>
    #include <fstream>

static const int BASE_X = 550;
static const int BASE_Y = 200;

static const std::string FONT_PATH = "assets/font/ARCADE_N.TTF";
static const std::string BACKGROUND_PATH = "assets/sprites/background.png";
static const std::string WINDOW_TITLE = "Arcade SDL2";

namespace arcade
{
    class libSdl : virtual public arcade::IDisplayModule{
        public:
            libSdl();
            ~libSdl() {};
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
            SDL_Window* window;
            SDL_Event event;
            SDL_Renderer* render;
            float x;
            float y;
            float squareSize;
            TTF_Font* _font;
            KeyPressed oldKeyPressed;
            KeyPressed _key;
            std::map<std::string, SDL_Texture*> charMap;
            std::string _gameName;
            std::string _playerName;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDiplay;
            SDL_Texture *backgroundSprite;

            void sortScore(std::size_t textSize);
            int getNumber(std::string);
            void addScoreTabToDisplay(void);
            void pickColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap);
            void checkTwoChar(std::size_t j, std::string str);
            SDL_Texture* madeRectangle(int r, int g, int b);
    };
};

extern "C" {
    arcade::IDisplayModule *entryPoint() {
        return (new arcade::libSdl);
    }
}

#endif /* !libSdl_HPP_ */
