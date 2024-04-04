/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <string>
#include <array>
#include <map>
#include <vector>
#include "KeyPressed.hpp"
#include "GameStatus.hpp"
#include "Color.hpp"
#include <unordered_map>

namespace arcade
{
    class IGameModule
    {
        public:
            IGameModule() = default;
            ~IGameModule() = default;

            virtual void resetGame() = 0;
            virtual std::array<std::string, 23> getMap() const = 0;
            virtual std::size_t getMapCellSize() const = 0;
            virtual std::unordered_map<std::string, std::pair<Color, std::string>> getPattern() const = 0;
            virtual std::vector<std::pair<std::string, std::pair<int, int>>> getText() const = 0;
            virtual void incrementTime() = 0;
            virtual GameStatus updateMap(KeyPressed key) = 0;
            virtual std::pair<std::size_t, std::size_t> getIndexes() const = 0;
            virtual void initText(const std::vector<std::string>, const std::vector<std::string>) = 0;
            virtual std::string getGameName() const = 0;
            virtual std::size_t getScore() const = 0;
    };
}

#endif /* !IGAMEMODULE_HPP_ */