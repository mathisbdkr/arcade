/*
** EPITECH PROJECT, 2024
** test_lib
** File description:
** LibSfml
*/

#include "LibSfml.hpp"

arcade::libSfml::libSfml()
{
    return;
}

void arcade::libSfml::init(const std::unordered_map<std::string, std::pair<Color, std::string>> pattern)
{
    x = BASE_X;
    y = BASE_Y;
    squareSize = 25;
    if (!_font.loadFromFile(FONT_PATH.c_str())) {
        fprintf(stderr, "error: font not found\n");
        exit(84);
    }
    pickColor(pattern);
    _keyClose = arcade::OTHER;
    window.create(sf::VideoMode(1920, 1080), WINDOW_TITLE.c_str());
    nextChar = true;
    spriteLoaded = true;
    if (!backgroundTexture.loadFromFile(BACKGROUND_PATH)) {
        spriteLoaded = false;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }
    
    return;
}

void arcade::libSfml::changeColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap)
{
    charMap.clear();
    pickColor(patternMap);
}

sf::RectangleShape arcade::libSfml::madeRectangle(sf::Color color, float size)
{
    sf::RectangleShape rect;
    rect.setSize(getPosition(size, size));
    rect.setFillColor(color);
    return rect;
}

void arcade::libSfml::pickColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap)
{
    for (auto tt = patternMap.begin(); tt != patternMap.end(); tt++) {
        if (tt->second.first == arcade::BLACK) {
            charMap.insert({tt->first, {madeRectangle(RGB(0,0,0), squareSize),tt->second.second}});
        }
        if (tt->second.first == arcade::WHITE) {
            charMap.insert({tt->first, {madeRectangle(RGB(255,255,255), squareSize / 8),tt->second.second}});
        }
        if (tt->second.first == arcade::RED) {
            charMap.insert({tt->first, {madeRectangle(RGB(255,0,0), squareSize),tt->second.second}});
        }
        if (tt->second.first == arcade::BLUE) {
            charMap.insert({tt->first, {madeRectangle(RGB(0,0,100), squareSize), tt->second.second}});
        }
        if (tt->second.first == arcade::GREEN) {
            charMap.insert({tt->first, {madeRectangle(RGB(0,255,0), squareSize), tt->second.second}});
        }
        if (tt->second.first == arcade::YELLOW) {
            charMap.insert({tt->first, {madeRectangle(RGB(255,240,0), squareSize), tt->second.second}});
        }
        if (tt->second.first == arcade::GRAY) {
            charMap.insert({tt->first, {madeRectangle(RGB(50,50,50), squareSize), tt->second.second}});
        }
        if (tt->second.first == arcade::CYAN) {
            charMap.insert({tt->first, {madeRectangle(RGB(74,86,237), squareSize / 4), tt->second.second}});
        }
    }
}

void arcade::libSfml::stop() {
    window.close();
}

arcade::KeyPressed arcade::libSfml::getKey() const
{
    arcade::KeyPressed key = arcade::KeyPressed::OTHER;
    if (_keyClose == CLOSE_BUTTON) {
        return arcade::CLOSE_BUTTON;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true) {
        return arcade::KeyPressed::UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == true) {
        return arcade::KeyPressed::DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true) {
        return arcade::KeyPressed::LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true) {
        return arcade::KeyPressed::RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) == true) {
        return arcade::KeyPressed::N;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) == true) {
        return arcade::KeyPressed::P;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) == true) {
        return arcade::KeyPressed::G;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) == true) {
        return arcade::KeyPressed::R;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true) {
        return arcade::KeyPressed::SPACE;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) == true && _gameName.compare("menu") != 0) {
        return arcade::KeyPressed::M;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) == true) {
        return arcade::KeyPressed::BACKSPACE;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) == true) {
        return arcade::KeyPressed::ENTER;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true) {
        return arcade::KeyPressed::BACKSPACE;
    }
    return key;
}

void arcade::libSfml::setKey(arcade::KeyPressed newValue)
{
    _key = newValue;
}

void arcade::libSfml::incertCharToPlayerName(void)
{
    sf::Keyboard::Key k = event.key.code;
    if (!k) {
        return;
    }
    if ((k <= sf::Keyboard::Z && k >= sf::Keyboard::A) || k == sf::Keyboard::BackSpace) {
        if (sf::Keyboard::isKeyPressed(k) && nextChar == true) {
            if (k == sf::Keyboard::BackSpace && _playerName.size() > 0) {
                _playerName.pop_back();
                nextChar = false;
                return;
            }
            char c = k + 'a';
            _playerName.push_back(c);
            nextChar = false;
        } else {
            nextChar = true;
        }
    }
}

void arcade::libSfml::handleEvent(const std::string gameName)
{
    _gameName = gameName;
    if (_gameName.compare("menu") == 0) {
        incertCharToPlayerName();
    }
    window.pollEvent(event);
    if (event.type == sf::Event::Closed) {
        window.close();
        _keyClose = CLOSE_BUTTON;
    }
    window.display();
    window.clear();
    if (spriteLoaded == true) {
        window.draw(backgroundSprite);
    }
}

void arcade::libSfml::setLastDirection(arcade::KeyPressed key)
{
    if (key == arcade::UP) {
        _lastDirection = arcade::UP;
    }
    if (key == arcade::DOWN) {
        _lastDirection = arcade::DOWN;
    }
    if (key == arcade::RIGHT) {
        _lastDirection = arcade::RIGHT;
    }
    if (key == arcade::LEFT) {
        _lastDirection = arcade::LEFT;
    }
}

void arcade::libSfml::displaySpriteItem(sf::RectangleShape rect, sf::Texture tmp)
{
    sf::Sprite sprite;
    sprite.setTexture(tmp);
    sf::Vector2f pos = rect.getPosition();
    sprite.setRotation(0);
    if (_lastDirection == arcade::UP) {
        sprite.setRotation(270);
        pos.y += squareSize;
    }
    if (_lastDirection == arcade::DOWN) {
        sprite.setRotation(90);
        pos.x += squareSize;
    }
    if (_lastDirection == arcade::LEFT) {
        sprite.setRotation(180);
        pos.x += squareSize;
        pos.y += squareSize;
    }
    sprite.setPosition(pos);
    window.draw(sprite);
}

void arcade::libSfml::checkTwoChar(std::size_t j, std::string str)
{

    for (auto tt = charMap.begin(); tt != charMap.end(); tt++) {
        if (tt->first.at(0) == str.at(j)) {
            sf::RectangleShape rect = tt->second.first;
            rect.setPosition(getPosition(x, y));
            if (str.at(j) == 'o') {
                rect.setPosition(getPosition(x + (squareSize / 2.5), y + (squareSize / 2.5)));
            } else if (str.at(j) == 'O') {
                rect.setPosition(getPosition(x + (squareSize / 3), y + (squareSize / 3)));
            }

            setLastDirection(getKey());
            if (tt->second.second.size() > 2) {
                sf::Texture tmp;
                if (tmp.loadFromFile(tt->second.second) == true) {
                    arcade::KeyPressed defaultKey = _lastDirection;
                    if (str.at(j) == '|' || str.at(j) == 'M' || str.at(j) == 'F') {
                        _lastDirection = arcade::RIGHT;
                    }
                    displaySpriteItem(rect, tmp);
                    _lastDirection = defaultKey;
                    break;
                } else {
                    tt->second.second.clear();
                }
            } else {
                window.draw(rect);
            }
        }
    }
}

void arcade::libSfml::displayMap(std::array<std::string, 23> map, std::size_t size)
{
    sf::RectangleShape rect;
    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < (map.at(i).size()); j += size) {
            checkTwoChar(j, map.at(i));
            x += squareSize;
        }
        x = BASE_X;
        y += squareSize;
    }
    x = BASE_X;
    y = BASE_Y;
}

int arcade::libSfml::getNumber(std::string str)
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

void arcade::libSfml::sortScore(std::size_t textSize)
{
    int max = 0;
    std::size_t index = 0;
    int x_score = 1550;
    int y_score = 350;
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
        y_score += 50;
    }
    _textToDiplay.clear();
    for (size_t i = textSize; i < tmpToDisplay.size() && i < (10 + textSize); i++) {
        _textToDiplay.push_back(tmpToDisplay.at(i));
    }
}

void arcade::libSfml::addScoreTabToDisplay(void)
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

void arcade::libSfml::displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay)
{
    sf::Text txt;
    _textToDiplay = textToDisplay;
    if (_gameName.compare("menu") == 0) {
        _textToDiplay.push_back({"Player name :", {600,700}});
        _textToDiplay.push_back({_playerName, {800,700}});
    } else {
        addScoreTabToDisplay();
    }
    for (std::size_t i = 0; i < textToDisplay.size(); i++) {
        _textToDiplay.push_back(textToDisplay.at(i));
    }

    for (size_t i = 0; i < _textToDiplay.size(); i++) {
        txt.setFont(_font);
        txt.setCharacterSize(15);
        txt.setFillColor(sf::Color::White);
        txt.setPosition(getPosition(_textToDiplay.at(i).second.first, _textToDiplay.at(i).second.second));
        txt.setString(_textToDiplay.at(i).first.c_str());
        window.draw(txt);
    }
}

sf::Color arcade::libSfml::RGB(int r, int g, int b)
{
    sf::Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

sf::Vector2f arcade::libSfml::getPosition(float x, float y)
{
    sf::Vector2f vector;

    vector.x = x;
    vector.y = y;
    return (vector);
}

std::string arcade::libSfml::getPlayerName() const
{
    return _playerName;
}
