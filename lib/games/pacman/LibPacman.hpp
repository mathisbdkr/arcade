/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** LibPacman
*/

#ifndef LIBPACMAN_HPP_
#define LIBPACMAN_HPP_

#include "../../includes/IGameModule.hpp"
#include <string>
#include <chrono>

namespace arcade {
    class LibPacman : virtual public arcade::IGameModule {
        public:
            LibPacman();
            ~LibPacman() {};
            void resetGame() override;
            std::array<std::string, 23> getMap() const override;
            std::size_t getMapCellSize() const override;
            std::unordered_map<std::string, std::pair<Color, std::string>> getPattern() const override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() const override;
            void incrementTime() override {};
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::pair<std::size_t, std::size_t> getIndexes() const override;
            void initText(const std::vector<std::string>, const std::vector<std::string>) override {};
            std::string getGameName() const override;
            std::size_t getScore() const override;
        private:
            void init();
            int findPlayer();
            void updateKeyPressed(arcade::KeyPressed key);
            bool isAvailable(char c);
            void moovePlayer(arcade::KeyPressed key);
            bool tpPlayerSide(arcade::KeyPressed key, int defaultX, int defaultY);
            void changePlayerPos(arcade::KeyPressed key);
            void moovePlayerBis(arcade::KeyPressed key);
            void addScore(char c);
            void changeGhostState(void);
            void isGameWin(void);

            void launchMooveGhost();
            void getNexGhost();
            bool tpGhostSide(arcade::KeyPressed key, int defaultX, int defaultY);
            void changeGhostPos(arcade::KeyPressed key);
            arcade::KeyPressed randKey(arcade::KeyPressed key1, arcade::KeyPressed key2, arcade::KeyPressed key3);
            arcade::KeyPressed changeGhostKey(arcade::KeyPressed key);
            arcade::KeyPressed mooveGhost(arcade::KeyPressed key);
            bool isAvailableGhost(char c);
            void wallBoxGhost(void);

            std::array<std::string, 23> map;
            std::string _gameName;
            std::size_t mapSize;
            std::size_t playerX;
            std::size_t playerY;
            GameStatus gameStatus;
            KeyPressed keyPressed;
            KeyPressed keyPressedGhost;
            int score;
            bool pacBuff;
            std::chrono::_V2::steady_clock::time_point timeEatBuff;
            KeyPressed oldkeyPressed;

            std::size_t ghostX;
            std::size_t ghostY;
            std::array<arcade::KeyPressed, 4> keyGhost = {arcade::UP, arcade::UP, arcade::UP, arcade::UP};
            std::array<std::pair<std::pair<std::size_t, std::size_t>, char>, 4> ghostPos;
            std::pair<std::size_t, std::size_t> ghostEat;
            int ghostID;
            char ghostChar;
            bool ghostCanMoove;
            
            std::chrono::_V2::steady_clock::time_point timeStart;
    };
}


#endif /* !LIBPACMAN_HPP_ */
