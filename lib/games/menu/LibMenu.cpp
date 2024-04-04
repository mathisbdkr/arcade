/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** LibPacman
*/

#include "LibMenu.hpp"

arcade::LibMenu::LibMenu()
{
    map = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };
    _SelectedGameIndex = 0;
    _SelectedLibIndex = 0;
    _libTypeSelected = 0;
}

void arcade::LibMenu::initText(std::vector<std::string> gameLibName, std::vector<std::string> graphicalName)
{
    _gameLibName = gameLibName;
    _graphicalName = graphicalName;
}

std::size_t arcade::LibMenu::getScore() const
{
    return -1;
}

std::string arcade::LibMenu::getGameName() const
{
    return "menu";
}

void arcade::LibMenu::resetGame()
{
}

std::array<std::string, 23> arcade::LibMenu::getMap() const
{
    return map;
}

std::size_t arcade::LibMenu::getMapCellSize() const
{
    return 1;
}

int arcade::LibMenu::changeLibIndex(int index, int change, int nbLib)
{
    if ((index + change) < nbLib && (index + change) >= 0) {
        return (index + change);
    }
    if (index == (nbLib - 1) && change > 0) {
        return 0;
    }
    if (index == 0 && change < 0) {
        return (nbLib - 1);
    }
    return index;
}

arcade::GameStatus arcade::LibMenu::updateMap(arcade::KeyPressed key)
{
    int gameIndex = _SelectedGameIndex;
    int libIndex = _SelectedLibIndex;
    int gameLibSize = _gameLibName.size();
    int graphLibSize = _graphicalName.size();
    if (key == arcade::UP) {
        if (_libTypeSelected == 0)
            _SelectedGameIndex = changeLibIndex(gameIndex, -1, gameLibSize);
        if (_libTypeSelected == 1)
            _SelectedLibIndex = changeLibIndex(libIndex, -1, graphLibSize);
    }
    if (key == arcade::DOWN) {
        if (_libTypeSelected == 0)
            _SelectedGameIndex = changeLibIndex(gameIndex, 1, gameLibSize);
        if (_libTypeSelected == 1)
            _SelectedLibIndex = changeLibIndex(libIndex, 1, graphLibSize);
    }
    if (key == arcade::LEFT) {
        _libTypeSelected = 0;
    }
    if (key == arcade::RIGHT) {
        _libTypeSelected = 1;
    }
    return arcade::PLAYING;
}

std::vector<std::pair<std::string, std::pair<int, int>>> arcade::LibMenu::getText() const
{
    std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay;
    int x = 600;
    int y = 280;
    if (_libTypeSelected == 1) {
        x = 1000;
    }
    textToDisplay.push_back({"     ||", {x + 50, y}});
    y += 25;
    textToDisplay.push_back({"     ||", {x + 50, y}});
    y += 25;
    textToDisplay.push_back({"     ||", {x + 50, y}});
    y += 25;
    textToDisplay.push_back({"    \\||/", {x + 50, y}});
    y += 25;
    textToDisplay.push_back({"     \\/", {x + 50, y}});
    y += 60;
    x = 600;
    int defaultY = y;
    for (std::size_t i = 0; i < _gameLibName.size(); i++) {
        std::string actualLib = _gameLibName.at(i);
        if (_SelectedGameIndex == i) {
            actualLib.append(" <--");
        }
        textToDisplay.push_back({actualLib, {x, y}});
        y += 75;
    }
    y = defaultY;
    x = 1000;
    for (std::size_t i = 0; i < _graphicalName.size(); i++) {
        std::string actualLib = _graphicalName.at(i);
        if (_SelectedLibIndex == i) {
            actualLib.append(" <--");
        }
        textToDisplay.push_back({actualLib, {x, y}});
        y += 75;
    }
    return textToDisplay;
}

std::pair<std::size_t, std::size_t> arcade::LibMenu::getIndexes() const
{
    return {_SelectedGameIndex, _SelectedLibIndex};
}

std::unordered_map<std::string, std::pair<arcade::Color, std::string>> arcade::LibMenu::getPattern() const
{
    std::unordered_map<std::string, std::pair<arcade::Color, std::string>> pattern;
    pattern.insert({" ", {arcade::DEFAULT, ""}});
    return pattern;
}
