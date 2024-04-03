/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** core
*/

#include "core.hpp"
#include "errorHandling.hpp"

Core::Core(int argc, char **argv)
{
    _dlLoader = new DlLoader;
    _graphicalLibIndex = getLibIndex(argv[1]);
    if (_graphicalLibIndex == -1) {
        throw LibError();
    }
    _graphicalLibAndHandler = _dlLoader->getAIDisplayModule(_graphicalLibIndex);
    _graphicalLib = _graphicalLibAndHandler.first;
    _libGraphicalLen = _dlLoader->getGraphicalPath().size();
    _libGameLen = _dlLoader->getGamePath().size();

    _key = arcade::OTHER;
    _gameSpeed = 150;
    _gameLibIndex = -1;
    _gameLibAndHandler = _dlLoader->getAIGameModule(_gameLibIndex);
    _gameLib = _gameLibAndHandler.first;
    _gameLib->initText(_dlLoader->getGraphicalPath(), _dlLoader->getGamePath());
    _graphicalLib->init(_gameLib->getPattern());
    _DefaultGraphicalLib = _graphicalLib;
    pass = 0;
}

Core::~Core()
{
    saveScore(playerName, _gameLib->getGameName(), _gameLib->getScore());
    dlclose(_gameLibAndHandler.second);
    dlclose(_graphicalLibAndHandler.second);
}

void Core::saveScore(std::string playerName, std::string gameName, std::size_t score)
{
    if (_gameLibIndex < 0 || score <= 0 || gameName.compare("menu") == 0) {
        return;
    }
    std::string fileName = "./lib/games/score/";
    fileName.append(gameName);
    fileName.append("_score.mbw");
    std::ofstream file(fileName, std::ios::app);
    if (file.is_open()) {
        std::string scoreLine = std::to_string(score);
        scoreLine.append(" : ");
        scoreLine.append(playerName);
        scoreLine.append("\n");
        file.write(scoreLine.c_str(), scoreLine.size());
        file.close();
    } else {
        throw SaveError();
    }
}

int Core::closeEvent(void)
{
    if (_key == arcade::CLOSE_BUTTON) {
        return 1;
    }
    if (_key == arcade::BACKSPACE && _gameLib->getGameName().compare("menu") != 0) {
        _graphicalLib->stop();
        return 1;
    }
    if (_key == arcade::M && _gameLib->getGameName().compare("menu") == 0) {
        _graphicalLib->stop();
        return 1;
    }
    return 0;
}

void Core::quitMenu(void)
{
    if (_gameLibIndex == -1 && _key == arcade::ENTER) {
        playerName = _graphicalLib->getPlayerName();
        if (playerName.size() < 1) {
            playerName = "DefaultPlayer";
        }
        std::pair<std::size_t, std::size_t> indexPair = _gameLib->getIndexes();
        _gameLibIndex = indexPair.second;
        _graphicalLibIndex = indexPair.first;
        changeGraphicalLib();
        changeGameLib();
    }
}

arcade::GameStatus Core::winAndLooseEvent(arcade::GameStatus status)
{
    if (status == arcade::WON_AND_RELOADED) {
        status = arcade::PLAYING;
        _gameLib->resetGame();
        _gameSpeed -= 15;
    }
    if (status == arcade::LOOSE) {
        status = arcade::PLAYING;
        _graphicalLib->setKey(arcade::OTHER);
        _key = arcade::M;
        changeLibrary();
    }
    return status;
}

void Core::gameLoop(void)
{
    auto time1 = std::chrono::steady_clock::now();
    arcade::GameStatus status = arcade::PLAYING;
    while (status == arcade::PLAYING) {
        _graphicalLib->game(_gameLib->getGameName());
        auto time2 = std::chrono::steady_clock::now();
        auto elapsed= std::chrono::duration_cast <std::chrono::milliseconds>(time2 - time1);
        if (elapsed.count() >= _gameSpeed) {
            _key = _graphicalLib->getKey();
            if (closeEvent() == 1) {
                break;
            }
            status = _gameLib->updateMap(_key);
            quitMenu();
            changeLibrary();
            _graphicalLib->setKey(arcade::OTHER);
            time1 = std::chrono::steady_clock::now();
        }
        _graphicalLib->displayMap(_gameLib->getMap(), _gameLib->getMapCellSize());
        status = winAndLooseEvent(status);
        _graphicalLib->displayText(_gameLib->getText());
    }
}
