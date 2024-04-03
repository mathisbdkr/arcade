/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** LibPacman
*/

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "../../includes/IGameModule.hpp"
#include <ostream>

namespace arcade {
    class LibSnake : virtual public arcade::IGameModule {
        public:
            LibSnake();
            ~LibSnake() {};
            void resetGame() override;
            std::array<std::string, 23> getMap() const override;
            std::size_t getMapCellSize() const override;
            std::unordered_map<std::string, Color> getPattern() const override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() const override;
            void incrementTime() override {};
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::pair<std::size_t, std::size_t> getIndexes() const override;
            void initText(const std::vector<std::string>, const std::vector<std::string>) override {};
            std::string getGameName() const override;
            std::size_t getScore() const override;
        protected:
        private:
            void getQueue();
            int findPlayer();
            bool isAvailable(char c);
            bool isAvailableFood(char c);
            void getSnakeLenght();
            void init();
            int moovePlayer(arcade::KeyPressed Key);
            int moove();
            int changePlayerPos(std::string str);
            void placeFood();
            void fillVector();

            std::string _gameName;
            std::vector<std::pair<int, int>> MyVector;
            KeyPressed keyPressed;
            std::size_t queueY;
            std::size_t queueX;
            std::size_t playerX;
            std::size_t playerY;
            std::size_t mapSize;
            std::size_t SnakeLenght;
            std::array<std::string, 23> map;
            enum Direction {
                DROITE,
                HAUT,
                GAUCHE,
                BAS
            };
            Direction direction;
            size_t score;
    };
}

extern "C" {
    arcade::IGameModule *entryPoint() {
        return (new arcade::LibSnake);
    }
}

#endif /* !LIBPACMAN_HPP_ */