/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** coreLibActions
*/

#include "core.hpp"
#include "errorHandling.hpp"

int Core::changeLibIndex(int index, int change, std::size_t nbLib)
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

int Core::getLibIndex(std::string path)
{
    int index = -1;
    std::vector<std::string> allGraphicalLib = _dlLoader->getGraphicalPath();
    for (int i = 0; i < NB_LIB_GRAPHICAL; i++) {
        if (path.find(allGraphicalLibraryPath[i]) != std::string::npos) {
            index = i;
        }
    }
    for (std::size_t i = 0; i < allGraphicalLib.size(); i++) {
        if (allGraphicalLib.at(i).compare(allGraphicalLibraryPath[index]) == 0) {
            return i;
        }
    }
    return -1;
}

void Core::changeGraphicalLib(void)
{
    _graphicalLib->stop();
    _graphicalLibAndHandler = _dlLoader->getAIDisplayModule(_graphicalLibIndex);
    _graphicalLib = _graphicalLibAndHandler.first;
    _graphicalLib->init(_gameLib->getPattern());
    pass = 1;
}

void Core::changeGameLib(void)
{
    saveScore(playerName, _gameLib->getGameName(), _gameLib->getScore());
    _gameLibAndHandler = _dlLoader->getAIGameModule(_gameLibIndex);
    _gameLib = _gameLibAndHandler.first;
    _graphicalLib->changeColor(_gameLib->getPattern());
    pass = 1;
}

void Core::changeLibrary()
{
    if (_gameLibIndex == -1) {
        return;
    }
    if (_key == arcade::N && pass == 0) {
        _graphicalLibIndex = changeLibIndex(_graphicalLibIndex, 1, _libGraphicalLen);
        changeGraphicalLib();
    }
    if (_key != arcade::N && pass == 1) {
        pass = 0;
    }
    if (_key == arcade::P && pass == 0) {
        _graphicalLibIndex = changeLibIndex(_graphicalLibIndex, -1, _libGraphicalLen);
        changeGraphicalLib();
    }
    if (_key != arcade::P && pass == 1) {
        pass = 0;
    }
    if (_key == arcade::G && pass == 0) {
        _gameLibIndex = changeLibIndex(_gameLibIndex, 1, _libGameLen);
        _gameSpeed = 150;
        changeGameLib();
    }
    if (_key != arcade::G && pass == 1) {
        pass = 0;
    }
    if (_key == arcade::M && pass == 0) {
        saveScore(playerName, _gameLib->getGameName(), _gameLib->getScore());
        _gameLibIndex = -1;
        _graphicalLib->stop();
        _graphicalLib = _DefaultGraphicalLib;
        changeGameLib();
        _gameLib->initText(_dlLoader->getGraphicalPath(), _dlLoader->getGamePath());
        _graphicalLib->init(_gameLib->getPattern());
        _graphicalLib->setKey(arcade::OTHER);
        _gameSpeed = 150;
    }
    if (_key != arcade::M && pass == 1) {
        pass = 0;
    }
    if (_key == arcade::R && pass == 0) {
        _gameLib->resetGame();
        pass = 1;
    }
    if (_key != arcade::R && pass == 1) {
        pass = 0;
    }
}
