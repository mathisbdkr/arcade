/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** snake
*/

#include "LibSnake.hpp"

arcade::LibSnake::LibSnake()
{
    init();
}

void arcade::LibSnake::init()
{

    map = {
        "###############################",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#             <==8            #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "###############################"
    };
    _gameName = "Snake";
    score = 0;
    mapSize = 1;
    direction = DROITE;
    SnakeLenght = 4;
    fillVector();
    srand(time(NULL));
    placeFood();
}

std::array<std::string, 23> arcade::LibSnake::getMap() const
{
    return map;
}

std::pair<std::size_t, std::size_t> arcade::LibSnake::getIndexes() const
{
    return {0,0};
}

std::size_t arcade::LibSnake::getMapCellSize() const
{
    return mapSize;
}

std::string arcade::LibSnake::getGameName() const
{
    return _gameName;
}

std::size_t arcade::LibSnake::getScore() const
{
    return score;
}

int arcade::LibSnake::findPlayer()
{
    size_t y = 0;
    size_t x = 0;
    size_t y_map = 20;
    size_t x_map = 31;

    for (y = 0; y != y_map; y++) {
        for(x = 0; x != x_map; x++)
            if (map[y][x] == '8') {
                playerY = y;
                playerX = x;
            }
    }
    return 0;
}

void arcade::LibSnake::placeFood()
{
    size_t foodY = rand() % 22;
    size_t foodX = rand() % 31;
    while (isAvailableFood(map.at(foodY).at(foodX)) != true) {
        foodY = rand() % 22;
        foodX = rand() % 31;
    }
    //std::cout << "food "<< foodY << foodX << std ::endl;
    map[foodY][foodX] = '|';
}

void arcade::LibSnake::fillVector()
{
    getQueue();
    size_t y = queueY;
    size_t x = queueX;
    for (std::size_t i = 0; i < SnakeLenght; i++)
        MyVector.push_back(std::make_pair(1, 2));
    for(std::size_t i = 0; i < MyVector.size(); i++) {
         MyVector[i].first = y;
         MyVector[i].second = x;
         x++;
     }
}

void arcade::LibSnake::getQueue()
{
    size_t y = 0;
    size_t x = 0;
    size_t y_map = 20;
    size_t x_map = 31;

    for (y = 0; y != y_map; y++) {
        for(x = 0; x != x_map; x++)
            if (map[y][x] == '<') {
                queueY = y;
                queueX = x;
            }
    }
}

bool arcade::LibSnake::isAvailable(char c)
{
    if (c == '#')
        return false;
    if (c == '<')
        return false;
    if (c == '=')
        return false;
    return true;
}

bool arcade::LibSnake::isAvailableFood(char c)
{
    if (c == '#')
        return false;
    if (c == '<')
        return false;
    if (c == '=')
        return false;
    if (c == '8')
        return false;
    return true;
}

void arcade::LibSnake::getSnakeLenght()
{
    if (MyVector.empty() == false)
        SnakeLenght = MyVector.size();
}

std::unordered_map<std::string, std::pair<arcade::Color, std::string>> arcade::LibSnake::getPattern() const
{
    std::unordered_map<std::string, std::pair<arcade::Color, std::string>> pattern;
    pattern.insert({" ", {arcade::DEFAULT, ""}});
    pattern.insert({"#", {arcade::GRAY, ""}});
    pattern.insert({"o", {arcade::WHITE, ""}});
    pattern.insert({"O", {arcade::CYAN, ""}});
    pattern.insert({"|", {arcade::RED, ""}});
    pattern.insert({"8", {arcade::BLUE, ""}});
    pattern.insert({"=", {arcade::GREEN, ""}});
    pattern.insert({"<", {arcade::GREEN, ""}});
    return pattern;
}

int arcade::LibSnake::changePlayerPos(std::string str)
{
    if (map[playerY][playerX] == '|') {
        placeFood();
        score++;
        if (str.compare("droite") == 0)
            MyVector.insert(MyVector.begin(), std::make_pair(MyVector[0].first, (MyVector[0].second) - 1));
        if (str.compare("gauche") == 0)
            MyVector.insert(MyVector.begin(), std::make_pair(MyVector[0].first, (MyVector[0].second) + 1));
        if (str.compare("haut") == 0)
            MyVector.insert(MyVector.begin(), std::make_pair((MyVector[0].first) + 1, MyVector[0].second));
        if (str.compare("bas") == 0)
            MyVector.insert(MyVector.begin(), std::make_pair((MyVector[0].first - 1), MyVector[0].second));
        SnakeLenght++;
    }
    map[playerY][playerX] = '8';
    if (map[MyVector[0].first][MyVector[0].second] != '#')
        map[MyVector[0].first][MyVector[0].second] = ' ';
    for(std::size_t i = 0; i < (MyVector.size() - 1); i++) {
        MyVector[i].first = MyVector[i + 1].first;
        MyVector[i].second = MyVector[i + 1].second;
        }
    map[MyVector[0].first][MyVector[0].second] = '<';
    for(std::size_t i = 1; i < (MyVector.size() - 1); i++) {
        map[MyVector[i].first][MyVector[i].second] = '=';
        }
    return 0;
}

int arcade::LibSnake::moovePlayer(arcade::KeyPressed key)
{
    if (key == arcade::RIGHT && (direction != GAUCHE && direction != DROITE)) {
        if (isAvailable(map.at(playerY).at(playerX + 1)) == true) {
            direction = DROITE;
            playerX++;
            changePlayerPos("droite");
            MyVector[SnakeLenght - 1].second++;
            return 1;
        } else return -1;
    }

    if (key == arcade::UP && (direction != BAS && direction != HAUT)) {
        if (isAvailable(map.at(playerY - 1).at(playerX)) == true) {
            direction = HAUT;
            playerY--;
            changePlayerPos("haut");
            MyVector[SnakeLenght - 1].first--;
            return 1;
        } else return -1;
    }
    if (key == arcade::DOWN && (direction != HAUT && direction != BAS)) {
        if (isAvailable(map.at(playerY + 1).at(playerX)) == true) {
            direction = BAS;
            playerY++;
            changePlayerPos("bas");
            MyVector[SnakeLenght - 1].first++;
            return 1;
        } else return -1;
    }
    if (key == arcade::LEFT && (direction != DROITE  && direction != GAUCHE)) {
        if (isAvailable(map.at(playerY).at(playerX - 1)) == true) {
            direction = GAUCHE;
            playerX--;
            changePlayerPos("gauche");
            MyVector[SnakeLenght - 1].second--;
            return 1;
        } else return -1;
    }
    return 0;
}

int arcade::LibSnake::moove()
{
    if (direction == DROITE) {
            if (isAvailable(map.at(playerY).at(playerX + 1)) == true) {
            playerX++;
            changePlayerPos("droite");
            MyVector[SnakeLenght - 1].second++;
        } else return -1;
    }
    if (direction == GAUCHE) {
            if (isAvailable(map.at(playerY).at(playerX - 1)) == true) {
            playerX--;
            changePlayerPos("gauche");
            MyVector[SnakeLenght - 1].second--;
        } else return -1;
    }
    if (direction == BAS) {
            if (isAvailable(map.at(playerY + 1).at(playerX)) == true) {
            playerY++;
            changePlayerPos("bas");
            MyVector[SnakeLenght - 1].first++;
        } else return -1;
    }
    if (direction == HAUT) {
            if (isAvailable(map.at(playerY - 1).at(playerX)) == true) {
            playerY--;
            changePlayerPos("haut");
            MyVector[SnakeLenght - 1].first--;
        } else return -1;
    }
    return 0;
}

arcade::GameStatus arcade::LibSnake::updateMap(arcade::KeyPressed key)
{
    findPlayer();
    getSnakeLenght();
    getQueue();
    int move = moovePlayer(key);

    if (move == -1) {
        return arcade::LOOSE;
    }
    if (move == 0) {
        if (moove() == -1)
            return arcade::LOOSE;
    }
    return arcade::PLAYING;
}

std::vector<std::pair<std::string, std::pair<int, int>>> arcade::LibSnake::getText() const
{
    std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay;
    textToDisplay.push_back({_gameName, {800, 150}});
    std::string scoreTxt;
    scoreTxt = "Score : ";
    scoreTxt.append(std::to_string(score));
    textToDisplay.push_back({scoreTxt, {1000, 150}});
    return textToDisplay;
}

void arcade::LibSnake::resetGame()
{
    MyVector.clear();
    init();
}
