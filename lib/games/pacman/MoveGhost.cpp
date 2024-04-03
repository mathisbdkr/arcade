/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** MoveGhost
*/

#include "LibPacman.hpp"

void arcade::LibPacman::getNexGhost()
{
    int nb = 0;
    while (ghostY < map.size() && nb < 4) {
        while (ghostX < map.at(ghostY).size() && nb < 4) {
            if (map.at(ghostY).at(ghostX) == 'M' || map.at(ghostY).at(ghostX) == 'F') {
                ghostPos.at(nb).first.first = ghostX;
                ghostPos.at(nb).first.second = ghostY;
                nb++;
            }
            ghostX++;
        }
        ghostX = 0;
        ghostY++;
    }
}

bool arcade::LibPacman::isAvailableGhost(char c)
{
    if (c == '#') {
        return false;
    }
    if (c == ghostChar) {
        return false;
    }
    if (c == '|') {
        return false;
    }
    if (c == 'P' && pacBuff == false) {
        gameStatus = arcade::LOOSE;
        return false;
    }
    return true;
}

void arcade::LibPacman::wallBoxGhost(void)
{
    int x = 13;
    int y = 9;
    while (y < 14) {
        while (x < 18) {
            if (map.at(y).at(x) == ghostChar) {
                return;
            }
            x++;
        }
        x = 13;
        y++;
    }
    x = 13;
    y = 9;
    while (y < 14) {
        while (x < 18) {
            if (map.at(y).at(x) != '#') {
                map.at(y).at(x) = '|';
            }
            x++;
        }
        x = 13;
        y++;
    }
    map.at(9).at(14) = '#';
    map.at(9).at(15) = '#';
    map.at(9).at(16) = '#';
}

void arcade::LibPacman::launchMooveGhost()
{
    auto timeNow = std::chrono::steady_clock::now();
    auto timeElapsed= std::chrono::duration_cast <std::chrono::milliseconds>(timeNow - timeStart);
    if (timeElapsed.count() < (10000)) {
        srand(time(NULL));
        return;
    }
    ghostCanMoove = true;
    if (timeElapsed.count() < (10400)) {
        for (int i = 0; i < 4; i++) {
            ghostX = ghostPos.at(i).first.first;
            ghostY = ghostPos.at(i).first.second;
            keyPressedGhost = arcade::UP;
            mooveGhost(arcade::UP);
            ghostPos.at(i).first.first = ghostX;
            ghostPos.at(i).first.second = ghostY;
            ghostPos.at(i).second = ' ';
        }
        return;
    }
    wallBoxGhost();
    for (int i = 0; i < 4; i++) {
        ghostID = i;
        if (ghostEat.first == ghostPos.at(i).first.first && ghostEat.second == ghostPos.at(i).first.second) {
            ghostPos.at(i).first.first = 15;
            ghostPos.at(i).first.second = 8;
            ghostEat.first = 0;
            ghostEat.second = 0;
        }
        ghostX = ghostPos.at(i).first.first;
        ghostY = ghostPos.at(i).first.second;
        
        keyGhost.at(i) = changeGhostKey(keyGhost.at(i));
        keyPressedGhost = keyGhost.at(i);
        if (ghostPos.at(i).second == 'P') {
            ghostPos.at(i).second = ' ';
        }
        keyGhost.at(i) = mooveGhost(keyGhost.at(i));
        ghostPos.at(i).first.first = ghostX;
        ghostPos.at(i).first.second = ghostY;
    }
}

arcade::KeyPressed arcade::LibPacman::mooveGhost(arcade::KeyPressed key)
{
    int defaultX = ghostX;
    int defaultY = ghostY;
    changeGhostPos(key);
    if (tpGhostSide(key, defaultX, defaultY) == true) {
        return key;
    }
    if (isAvailableGhost(map.at(ghostY).at(ghostX)) == true) {
        map[defaultY][defaultX] = ghostPos.at(ghostID).second;
        ghostPos.at(ghostID).second = map[ghostY][ghostX];
        map[ghostY][ghostX] = ghostChar;
        return key;
    }
    ghostX = defaultX;
    ghostY = defaultY;
    return key;
}

bool arcade::LibPacman::tpGhostSide(arcade::KeyPressed key, int defaultX, int defaultY)
{
    if (ghostX >= map.at(ghostY).size() && key == arcade::RIGHT) {
        ghostX = 0;
        map[defaultY][defaultX] = ghostPos.at(ghostID).second;
        ghostPos.at(ghostID).second = map[ghostY][ghostX];
        map[ghostY][ghostX] = ghostChar;
        return true;
    }
    if (isAvailableGhost(map.at(ghostY).at(ghostX)) == true) {
        if (ghostX == 0 && key == arcade::LEFT) {
            map[defaultY][defaultX] = ghostPos.at(ghostID).second;
            ghostX = map.at(ghostY).size() - 1;
            ghostPos.at(ghostID).second = map[ghostY][ghostX];
            map[ghostY][ghostX] = ghostChar;
            return true;
        }
    }
    return false;
}

void arcade::LibPacman::changeGhostPos(arcade::KeyPressed key)
{
    if (key == arcade::UP) {
        ghostY -= 1;
    }
    if (key == arcade::DOWN) {
        ghostY += 1;
    }
    if (key == arcade::LEFT) {
        ghostX -= 1;
    }
    if (key == arcade::RIGHT) {
        ghostX += 1;
    }
}

arcade::KeyPressed arcade::LibPacman::randKey(arcade::KeyPressed key1, arcade::KeyPressed key2, arcade::KeyPressed key3)
{
    int r = rand() % 3;
    if (r == 0) {
        return key1;
    }
    if (r == 1) {
        return key2;
    }
    if (r == 2) {
        return key3;
    }
    return key1;
}

arcade::KeyPressed arcade::LibPacman::changeGhostKey(arcade::KeyPressed key)
{
    arcade::KeyPressed oldKey = key;
    key = randKey(randKey(arcade::DOWN, arcade::LEFT, arcade::DOWN), randKey(arcade::RIGHT, arcade::LEFT, arcade::RIGHT), randKey(arcade::UP, arcade::LEFT, arcade::UP));
    if (oldKey == arcade::UP && key == arcade::DOWN)
        return arcade::RIGHT;
    if (oldKey == arcade::DOWN && key == arcade::UP)
        return arcade::RIGHT;
    if (oldKey == arcade::LEFT && key == arcade::RIGHT)
        return arcade::DOWN;
    if (oldKey == arcade::RIGHT && key == arcade::LEFT)
        return arcade::UP;
    return key;
}
