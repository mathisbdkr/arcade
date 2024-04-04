/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include "KeyPressed.hpp"
#include "Color.hpp"
#include <string>
#include <map>
#include <array>
#include <vector>
#include <unordered_map>

namespace arcade
{
    class IDisplayModule
    {
        public:
            IDisplayModule() = default;
            ~IDisplayModule() = default;

            virtual void init(const std::unordered_map<std::string, std::pair<Color, std::string>> pattern) = 0;
            virtual void stop() = 0;
            virtual void handleEvent(const std::string gameName) = 0;
            virtual void changeColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap) = 0;
            virtual void displayText(const std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) = 0;
            virtual void displayMap(const std::array<std::string, 23> map, const std::size_t size) = 0;
            virtual KeyPressed getKey() const = 0;
            virtual void setKey(const KeyPressed newValue) = 0;
            virtual std::string getPlayerName() const = 0;
    };
}

#endif /* !IDISPLAYMODULE_HPP_ */