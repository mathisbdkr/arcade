/*
** EPITECH PROJECT, 2024
** test_lib
** File description:
** LibNcurses
*/

#include "LibNcurses.hpp"

arcade::libNcurses::libNcurses()
{
    return;
}

arcade::libNcurses::~libNcurses()
{
    _gameName.clear();
    _playerName.clear();
    _textToDiplay.clear();
}

void arcade::libNcurses::init(const std::unordered_map<std::string, std::pair<Color, std::string>> pattern)
{
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    start_color();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);
    win = newwin(1920 , 1080, 0, 0);
    wclear(win);
    pickColor(pattern);
    _gameName = "";
    x = 0;
    y = 0;
    pressedChar = 0;
    _keyPressed = arcade::OTHER;
}

void arcade::libNcurses::changeColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap)
{
    charMap.clear();
    pickColor(patternMap);
}

void arcade::libNcurses::pickColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap)
{
    for (auto tt = patternMap.begin(); tt != patternMap.end(); tt++) {
        if (tt->second.first == arcade::BLACK) {
            init_pair(arcade::BLACK, COLOR_BLACK, COLOR_BLACK);
            charMap.insert({tt->first, arcade::BLACK});
        }
        if (tt->second.first == arcade::WHITE) {
            init_pair(arcade::WHITE, COLOR_WHITE, COLOR_BLACK);
            charMap.insert({tt->first, arcade::WHITE});
        }
        if (tt->second.first == arcade::RED) {
            init_pair(arcade::RED, COLOR_RED, COLOR_RED);
            charMap.insert({tt->first, arcade::RED});
        }
        if (tt->second.first == arcade::BLUE) {
            init_pair(arcade::BLUE, COLOR_BLUE, COLOR_BLUE);
            charMap.insert({tt->first, arcade::BLUE});
            init_color(110, 0, 0, 250);
            init_pair(arcade::BLUE, 110, 110);
            charMap.insert({tt->first, arcade::BLUE});
        }
        if (tt->second.first == arcade::GREEN) {
            init_pair(arcade::GREEN, COLOR_GREEN, COLOR_GREEN);
            charMap.insert({tt->first, arcade::GREEN});
        }
        if (tt->second.first == arcade::YELLOW) {
            init_pair(arcade::YELLOW, COLOR_YELLOW, COLOR_YELLOW);
            charMap.insert({tt->first, arcade::YELLOW});
        }
        if (tt->second.first == arcade::GRAY) {
            init_color(100, 150, 150, 150);
            init_pair(arcade::GRAY, 100, 100);
            charMap.insert({tt->first, arcade::GRAY});
        }
        if (tt->second.first == arcade::CYAN) {
            init_pair(arcade::CYAN, COLOR_CYAN, COLOR_BLACK);
            charMap.insert({tt->first, arcade::CYAN});
        }
    }
}

void arcade::libNcurses::stop() {
    
    wclear(win);
    delwin(win);
    endwin();
}

void arcade::libNcurses::handleEvent(const std::string gameName)
{
    _gameName = gameName;
    otherGetKey();
    if (_gameName.compare("menu") == 0) {
        if ((pressedChar >= 'a' && pressedChar <= 'z') ||
        (pressedChar >= 'A' && pressedChar <= 'Z') ||
        pressedChar == '_' ||
        (pressedChar >= '0' && pressedChar <= '9')) {
            _playerName.push_back(pressedChar);
        }
        if (pressedChar == KEY_BACKSPACE) {
            _playerName.pop_back();
        }
    }
    werase(win);
}

void arcade::libNcurses::color_remove(void) {
    wattroff(win,COLOR_PAIR(RED));
    wattroff(win,COLOR_PAIR(GREEN));
    wattroff(win,COLOR_PAIR(CYAN));
    wattroff(win,COLOR_PAIR(BLACK));
    wattroff(win,COLOR_PAIR(WHITE));
    wattroff(win,COLOR_PAIR(GRAY));
    wattron(win,COLOR_PAIR(DEFAULT));
}

void arcade::libNcurses::otherGetKey(void)
{
    int c = getch();
    pressedChar = c;
    if (c == KEY_UP) {
        _keyPressed = arcade::KeyPressed::UP;
        return;
    }
    if (c == KEY_DOWN) {
        _keyPressed = arcade::KeyPressed::DOWN;
        return;
    }
    if (c == KEY_LEFT) {
        _keyPressed = arcade::KeyPressed::LEFT;
        return;
    }
    if (c == KEY_RIGHT) {
        _keyPressed = arcade::KeyPressed::RIGHT;
        return;
    }
    if (c == 'g' || c == 'G') {
        _keyPressed = arcade::KeyPressed::G;
        return;
    }
    if (c == 'n' || c == 'N') {
        _keyPressed = arcade::KeyPressed::N;
        return;
    }
    if (c == 'p' || c == 'P') {
        _keyPressed = arcade::KeyPressed::P;
        return;
    }
    if (c == 'r' || c == 'R') {
        _keyPressed = arcade::KeyPressed::R;
        return;
    }
    if (c == ' ') {
        _keyPressed = arcade::KeyPressed::SPACE;
        return;
    }
    if ((c == 'm' || c == 'M') && _gameName.compare("menu") != 0) {
        _keyPressed = arcade::KeyPressed::M;
        return;
    }
    if (c == KEY_BACKSPACE) {
        _keyPressed = arcade::KeyPressed::BACKSPACE;
        return;
    }
    if (c == 10) {
        _keyPressed = arcade::KeyPressed::ENTER;
        return;
    }
    if (c == 'q' && _gameName.compare("menu") != 0) {
        _keyPressed = arcade::BACKSPACE;
        return;
    }
    if (c == 27 && _gameName.compare("menu") == 0) {
        _keyPressed = arcade::M;
        return;
    }
}

arcade::KeyPressed arcade::libNcurses::getKey() const
{
    return _keyPressed;
}

void arcade::libNcurses::setKey(arcade::KeyPressed newValue)
{
    if (_keyPressed != arcade::BACKSPACE)
        _keyPressed = newValue;
}

void arcade::libNcurses::checkTwoChar(std::size_t j, std::string str)
{
    for (auto tt = charMap.begin(); tt != charMap.end(); tt++) {
        if (tt->first.at(0) == str.at(j)) {
            wattron(win,COLOR_PAIR(tt->second));
            if (str.at(j) == 'o') {
                mvwprintw(win, y, x, "*");
            } else if (str.at(j) == 'O') {
                mvwprintw(win, y, x, "O");
            } else {
                mvwprintw(win, y, x, " ");
            }
        }
    }
}

void arcade::libNcurses::displayMap(std::array<std::string, 23> map, std::size_t size)
{
    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < (map.at(i).size()); j += size) {
            for (size_t k = 0; k < size; k++) {
                checkTwoChar(j, map.at(i));
                x += 1;
            }
            color_remove();
        }
        x = BASE_X;
        y += 1;
    }
    x = BASE_X;
    y = BASE_Y;
}

int arcade::libNcurses::getNumber(std::string str)
{
    std::string strNbr;
    for (std::size_t i = 0; i < str.size(); i++) {
        if (str.at(i) <=  '9' && str.at(i) >= '0') {
            strNbr.push_back(str.at(i));
        } else {
            break;
        }
    }
    return atoi(strNbr.c_str());
}

void arcade::libNcurses::sortScore(std::size_t textSize)
{
    int max = 0;
    std::size_t index = 0;
    int x_score = 800;
    int y_score = 200;
    std::vector<std::pair<std::string, std::pair<int, int>>> tmpToDisplay;
    for (size_t i = 0; i < textSize; i++) {
        tmpToDisplay.push_back(_textToDiplay.at(i));
    }
    
    for (size_t i = textSize; i < _textToDiplay.size(); i++) {
        for (size_t j = textSize; j < _textToDiplay.size(); j++) {
            if (max <= getNumber(_textToDiplay.at(j).first)) {
                max = getNumber(_textToDiplay.at(j).first);
                index = j;
            }
        }
        tmpToDisplay.push_back(_textToDiplay.at(index));
        tmpToDisplay.at(i).second.first = x_score;
        tmpToDisplay.at(i).second.second = y_score;
        _textToDiplay.at(index).first = "0 \n";
        max = 0;
        y_score += 68;
    }
    _textToDiplay.clear();
    for (size_t i = textSize; i < tmpToDisplay.size() && i < (10 + textSize); i++) {
        _textToDiplay.push_back(tmpToDisplay.at(i));
    }
}

void arcade::libNcurses::addScoreTabToDisplay(void)
{
    std::fstream my_file;
    std::string fileName = "./lib/games/score/";
    fileName.append(_gameName);
    fileName.append("_score.mbw");
    my_file.open(fileName.c_str(), std::ios::in);

    std::size_t textSize = _textToDiplay.size();
    if (my_file.is_open()) {
        char mychar;
        std::string line;
        while (my_file) {
            mychar = my_file.get();
            line.push_back(mychar);
            if (mychar == '\n') {
                _textToDiplay.push_back({line, {0, 0}});
                line.clear();
            }
        }
    }
	my_file.close();
    sortScore(textSize);
}

void arcade::libNcurses::displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay)
{
    wattron(win,COLOR_PAIR(DEFAULT));
    _textToDiplay = textToDisplay;
    if (_gameName.compare("menu") == 0) {
        _textToDiplay.push_back({_playerName, {0,0}});
    } else {
        addScoreTabToDisplay();
    }
    for (std::size_t i = 0; i < textToDisplay.size(); i++) {
        _textToDiplay.push_back(textToDisplay.at(i));
    }
    for (size_t i = 0; i < _textToDiplay.size(); i++) {
        mvwprintw(win, (_textToDiplay.at(i).second.second * 0.03), (_textToDiplay.at(i).second.first * 0.06), "%s", _textToDiplay.at(i).first.c_str());
    }
    wrefresh(win);
}

std::string arcade::libNcurses::getPlayerName() const
{
    return _playerName;
}
