/*
** EPITECH PROJECT, 2024
** test_lib
** File description:
** LibSdl
*/

#include "LibSdl.hpp"

arcade::libSdl::libSdl()
{
    return;
}

void arcade::libSdl::init(const std::unordered_map<std::string, std::pair<Color, std::string>> pattern)
{
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    x = BASE_X;
    y = BASE_Y;
    squareSize = 25;
    TTF_Init();
    _font = TTF_OpenFont(FONT_PATH.c_str(), 28);
    oldKeyPressed = arcade::OTHER;
    _key = arcade::OTHER;
    _gameName = "";
    pickColor(pattern);
    spriteLoaded = true;
    backgroundSprite = IMG_LoadTexture(render, BACKGROUND_PATH.c_str());
    if (backgroundSprite == nullptr) {
        spriteLoaded = false;
    }
}

void arcade::libSdl::changeColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap)
{
    charMap.clear();
    pickColor(patternMap);
}

SDL_Texture* arcade::libSdl::madeRectangle(int r, int g, int b)
{
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* arcade::libSdl::madeSprite(int r, int g, int b, std::string path)
{
    SDL_Texture* texture;
    texture = IMG_LoadTexture(render, path.c_str());
    if (texture == nullptr) {
        texture = madeRectangle(r, g, b);
    }
    return texture;
}

void arcade::libSdl::pickColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap)
{
    for (auto tt = patternMap.begin(); tt != patternMap.end(); tt++) {
        if (tt->second.first == arcade::BLACK) {
            charMap.insert({tt->first, madeSprite(0,0,0, tt->second.second)});
        }
        if (tt->second.first == arcade::WHITE) {
            charMap.insert({tt->first, madeSprite(255,255,255, tt->second.second)});
        }
        if (tt->second.first == arcade::RED) {
            charMap.insert({tt->first, madeSprite(255,0,0, tt->second.second)});
        }
        if (tt->second.first == arcade::BLUE) {
            charMap.insert({tt->first, madeSprite(0,0,100, tt->second.second)});
        }
        if (tt->second.first == arcade::GREEN) {
            charMap.insert({tt->first, madeSprite(0,255,0, tt->second.second)});
        }
        if (tt->second.first == arcade::YELLOW) {
            charMap.insert({tt->first, madeSprite(255,240,0, tt->second.second)});
        }
        if (tt->second.first == arcade::GRAY) {
            charMap.insert({tt->first, madeSprite(50,50,50, tt->second.second)});
        }
        if (tt->second.first == arcade::CYAN) {
            charMap.insert({tt->first, madeSprite(74,86,237, tt->second.second)});
        }
    }
}

void arcade::libSdl::stop()
{
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
}

void arcade::libSdl::handleEvent(const std::string gameName)
{
    _gameName = gameName;
    SDL_RenderPresent(render);
    SDL_PollEvent(&event);
    if (_gameName.compare("menu") == 0) {
        switch (event.type) {
            case SDL_TEXTINPUT:
                _playerName.append(event.text.text);
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_BACKSPACE:
                        if (_playerName.size() > 0)
                            _playerName.pop_back();
                        break;
                }
        }
    }
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    if (spriteLoaded == true)
        SDL_RenderCopy(render, backgroundSprite, NULL, NULL);
}

int arcade::libSdl::getNumber(std::string str)
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

void arcade::libSdl::sortScore(std::size_t textSize)
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

void arcade::libSdl::addScoreTabToDisplay(void)
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

void arcade::libSdl::displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay)
{
    if (_font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(84);
    }
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

    int text_size = 15;
    SDL_Color White = {255, 255, 255, 255};
    for (size_t i = 0; i < _textToDiplay.size(); i++) {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_font, _textToDiplay.at(i).first.c_str(), White); 
        SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);
        SDL_Rect Message_rect;

        Message_rect.x = _textToDiplay.at(i).second.first;
        Message_rect.y = _textToDiplay.at(i).second.second;
        Message_rect.w = (_textToDiplay.at(i).first.size() * text_size);
        Message_rect.h = text_size;
        SDL_RenderCopy(render, Message, NULL, &Message_rect);
        SDL_DestroyTexture(Message);
        SDL_FreeSurface(surfaceMessage);
    }
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
}

void arcade::libSdl::checkTwoChar(std::size_t j, std::string str)
{
    SDL_Rect rect;
    rect.w = squareSize;
    rect.h = squareSize;
    rect.x = x;
    rect.y = y;
    for (auto tt = charMap.begin(); tt != charMap.end(); tt++) {
        if (tt->first.at(0) == str.at(j)) {
            if (str.at(j) == 'o') {
                rect.w = squareSize / 8;
                rect.h = squareSize / 8;
                rect.x = x + (squareSize / 2.5);
                rect.y = y + (squareSize / 2.5);
            } else if (str.at(j) == 'O') {
                rect.w = squareSize / 4;
                rect.h = squareSize / 4;
                rect.x = x + (squareSize / 3);
                rect.y = y + (squareSize / 3);
            }
            SDL_RenderCopy(render, tt->second, NULL, &rect);
            break;
        }
    }
}

void arcade::libSdl::displayMap(std::array<std::string, 23> map, std::size_t size)
{
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
    switch (event.type) {
        case SDL_QUIT:
            oldKeyPressed = arcade::CLOSE_BUTTON;
    }
}

arcade::KeyPressed arcade::libSdl::getKey() const
{
    if (oldKeyPressed != arcade::OTHER) {
        return arcade::CLOSE_BUTTON;
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT])
        return arcade::LEFT;
    if (state[SDL_SCANCODE_RIGHT])
        return arcade::RIGHT;
    if (state[SDL_SCANCODE_UP])
        return arcade::UP;
    if (state[SDL_SCANCODE_DOWN])
        return arcade::DOWN;
    if (state[SDL_SCANCODE_N])
        return arcade::N;
    if (state[SDL_SCANCODE_P])
        return arcade::P;
    if (state[SDL_SCANCODE_G])
        return arcade::G;
    if (state[SDL_SCANCODE_R])
        return arcade::R;
    if (state[SDL_SCANCODE_SEMICOLON] && _gameName.compare("menu") != 0) {
        return arcade::M;
    }
    if (state[SDL_SCANCODE_BACKSPACE])
        return arcade::BACKSPACE;
    if (state[SDL_SCANCODE_RETURN])
        return arcade::ENTER;
    return arcade::OTHER;
}

void arcade::libSdl::setKey(arcade::KeyPressed newValue)
{
    _key = newValue;
}

std::string arcade::libSdl::getPlayerName() const
{
    return _playerName;
}
