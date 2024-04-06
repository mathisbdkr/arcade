<img src="/doc/src/assets/Arcade.gif" height="400" width="900"/>

# Credit

Membre du groupe:
- Mathis Brehm
- Bradley Malbrouck
- Wilson Bordichon

Membre du 2eme groupe:
- Eva Legrand
- Yanis Harkouk

# Documentation Arcade

Cette documentation a pour but de comprendre le fonctionnement du projet et comment intégrer vos jeux et librairies graphiques

# Table des matières

- [Core](#core)
    - [Diagramme de classe](#diagramme-de-classe)
    - [Fonctionnement du core](#fonctionnement-du-core)
    - [DlLoader](#dlloader)

- [Interfaces](#interfaces)
    - [IGameModule](#igamemodule)
    - [IDisplayModule](#idisplaymodule)

- [Classes](#classes)
    - [Classe : libNcurses](#classe--libncurses)
    - [Classe : libSfml](#classe--libsfml)
    - [Classe : libSdl](#classe--libsdl)
    - [Classe : LibMenu](#classe--libmenu)
    - [Classe : LibPacman](#classe--libpacman)
    - [Classe : LibSnake](#classe--libsnake)
    - [Classe : LibError](#classe--liberror)

- [Enum](#enum)
    - [Enum : KeyPressed](#enum--keypressed)
    - [Enum : Color](#enum--color)
    - [Enum : GameStatus](#enum--gamestatus)

- [Librairies](#librairies)
    - [Librairies graphiques](#librairies-graphiques)
        - [Les librairies graphique compatible](#les-librairies-graphique-compatible)
        - [Implémenter une nouvelle librairie graphique](#implémenter-une-nouvelle-librairie-graphique)
        - [NCURSES](#ncurses)
        - [SFML](#sfml)
        - [SDL2](#sdl2)
    - [Librairies de jeux](#librairies-de-jeux)
        - [Implémenter une nouveau jeu](#implémenter-un-nouveau-jeu)
        - [Pacman](#pacman)
        - [Snake](#snake)

- [Compiler et lancer le programme](#compiler-et-lancer-le-programme)

# Core

## Diagramme de classe

<img src="DIAGRAMME/" width="400"/>

## Fonctionnement du core

Le Coeur du programme est initialisé dans le fichier `core.cpp`. Il permet le chargement de la librairie graphique indiqué par l’utilisateur et le chargement de toutes les autres librairies graphiques en cas de besoin. Il crée une liste des librairies situées dans un dossier spécifique. Ces librairies seront donc utilisables par le programme.

> Core.hpp

``` c++
class Core {
    public:
        Core(int argc, char **argv);
        ~Core();
        void gameLoop(void);
    private:
        arcade::IDisplayModule *_graphicalLib;
        arcade::IDisplayModule *_DefaultGraphicalLib;
        arcade::IGameModule *_gameLib;
        std::pair <arcade::IDisplayModule *,void *> _graphicalLibAndHandler;
        std::pair <arcade::IGameModule *,void *> _gameLibAndHandler;
        std::size_t _libGraphicalLen;
        std::size_t _libGameLen;
        int _graphicalLibIndex;
        int _gameLibIndex;
        arcade::KeyPressed _key;
        int _gameSpeed;
        DlLoader *_dlLoader;
        int pass = 0;
        std::string playerName;

        int closeEvent(void);
        void quitMenu(void);
        arcade::GameStatus winAndLooseEvent(arcade::GameStatus status);
        void changeGraphicalLib(void);
        void changeGameLib(void);
        int getLibIndex(std::string path);
        void changeLibrary();
        int changeLibIndex(int index, int change, std::size_t nbLib);
        void saveScore(std::string playerName, std::string gameName, std::size_t score);
};
```

## DlLoader

La classe `DlLoader`, permet de charger les librairies graphiques et les jeux.

> DlLoader.hpp

``` c++
class DlLoader {
    public:
        DlLoader() {};
        ~DlLoader() {};
        std::vector <std::string> getGraphicalPath(void);
        std::vector <std::string> getGamePath(void);
        std::pair <arcade::IDisplayModule *,void *>getAIDisplayModule(int index);
        std::pair <arcade::IGameModule *,void *> getAIGameModule(int index);
    private:
        std::deque<std::string> allLibAvailable (void);
        bool isGraphicalLibExist(std::string path);
        bool isGameLibExist(std::string path);
        bool isALib (std::string path);
        void entryPointGraphical(std::string path);
        void entryPointGame(std::string path);

        std::pair <arcade::IDisplayModule *,void *> _IDisplayModulePair;
        std::pair <arcade::IGameModule *,void *> _IGameModulePair;
};
```

## Interfaces
### IGameModule

L'interface `IGameModule`, permet de récupérer les informations données par les librairies de jeux comme par exemple la map, le score... et de les mettre à jour à chaque itération.

> IGameModule.hpp

``` C++
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
            virtual std::unordered_map<std::string, Color> getPattern() const = 0;
            virtual std::vector<std::pair<std::string, std::pair<int, int>>> getText() const = 0;
            virtual void incrementTime() = 0;
            virtual GameStatus updateMap(KeyPressed key) = 0;
            virtual std::pair<std::size_t, std::size_t> getIndexes() const = 0;
            virtual void initText(const std::vector<std::string>, const std::vector<std::string>) = 0;
            virtual std::string getGameName() const = 0;
            virtual std::size_t getScore() const = 0;
    };
}
```

### IDisplayModule

L'interface `IDisplayModule` permet l'affichage d'une librairie de jeu

> IDisplayModule.hpp

``` C++
namespace arcade
{
    class IDisplayModule
    {
        public:
            IDisplayModule() = default;
            ~IDisplayModule() = default;

            virtual void init(const std::unordered_map<std::string, Color> pattern) = 0;
            virtual void stop() = 0;
            virtual void game(const std::string gameName) = 0;
            virtual void changeColor(const std::unordered_map<std::string, Color> patternMap) = 0;
            virtual void displayText(const std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) = 0;
            virtual void displayMap(const std::array<std::string, 23> map, const std::size_t size) = 0;
            virtual KeyPressed getKey() const = 0;
            virtual void setKey(const KeyPressed newValue) = 0;
            virtual std::string getPlayerName() const = 0;
    };
}
```

## Classes
### Classe : libNcurses

La classe `libNcurses`, définit la librairie graphique Ncurses qui va servir à afficher les jeux une fois le programme lancé et la librairie Ncurses sélectionnée.

> libNcurses.hpp

``` c++
namespace arcade
{
    class libNcurses : virtual public arcade::IDisplayModule{
        public:
            libNcurses();
            ~libNcurses();
            void init(const std::unordered_map<std::string, Color> pattern) override;
            void stop() override;
            void game(const std::string gameName) override;
            void displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) override;
            void displayMap(std::array<std::string, 23> map, std::size_t size) override;
            arcade::KeyPressed getKey() const override;
            void setKey(arcade::KeyPressed newValue) override;
            void changeColor(const std::unordered_map<std::string, Color> patternMap) override;
            std::string getPlayerName() const override;
        private:
            WINDOW *win;
            int x;
            int y;
            std::map<std::string, arcade::Color> charMap;
            std::string _gameName;
            std::string _playerName;
            arcade::KeyPressed _keyPressed;
            int pressedChar;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDiplay;

            void sortScore(std::size_t textSize);
            int getNumber(std::string);
            void addScoreTabToDisplay(void);
            void otherGetKey(void);
            void pickColor(const std::unordered_map<std::string, Color> patternMap);
            void color_remove(void);
            void checkTwoChar(std::size_t j, std::string str);
    };
};
```

### Classe : libSfml

La classe `libSfml`, définit la librairie graphique SFML qui va servir à afficher les jeux une fois le programme lancé et la librairie SFML sélectionnée.

> LibSfml.hpp

``` c++
namespace arcade
{
    class libSfml : virtual public arcade::IDisplayModule{
        public:
            libSfml();
            ~libSfml() {};
            void init(const std::unordered_map<std::string, Color> pattern) override;
            void stop() override;
            void game(const std::string gameName) override;
            void displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) override;
            void displayMap(std::array<std::string, 23> map, std::size_t size) override;
            arcade::KeyPressed getKey() const override;
            void setKey(arcade::KeyPressed newValue) override;
            void changeColor(const std::unordered_map<std::string, Color> patternMap) override;
            std::string getPlayerName() const override;
        private:
            sf::RenderWindow window;
            float x;
            float y;
            float squareSize;
            sf::Event event;
            sf::Font _font;
            std::map<std::string, sf::RectangleShape> charMap;
            std::string _gameName;
            std::string _playerName;
            arcade::KeyPressed _keyClose;
            arcade::KeyPressed _key;
            bool nextChar;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDiplay;

            void sortScore(std::size_t textSize);
            int getNumber(std::string);
            void pickColor(const std::unordered_map<std::string, Color> patternMap);
            void addScoreTabToDisplay(void);
            void incertCharToPlayerName(void);
            sf::RectangleShape madeRectangle(sf::Color color, float size);
            bool displayRoundShape(sf::RectangleShape rect, char c);
            void checkTwoChar(std::size_t j, std::string str);
            sf::Vector2f getPosition(float x, float y);
            sf::Color RGB(int r, int g, int b);
    };
};
```

### Classe : libSdl

La classe `libSdl`, définit la librairie graphique Sdl2 qui va servir à afficher les jeux une fois le programme lancé et la librairie Sdl2 sélectionnée.

> libSdl.hpp

``` c++
namespace arcade
{
    class libSdl : virtual public arcade::IDisplayModule{
        public:
            libSdl();
            ~libSdl() {};
            void init(const std::unordered_map<std::string, Color> pattern) override;
            void stop() override;
            void game(const std::string gameName) override;
            void displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) override;
            void displayMap(std::array<std::string, 23> map, std::size_t size) override;
            arcade::KeyPressed getKey() const override;
            void setKey(arcade::KeyPressed newValue) override;
            void changeColor(const std::unordered_map<std::string, Color> patternMap) override;
            std::string getPlayerName() const override;
        private:
            SDL_Window* window;
            SDL_Event event;
            SDL_Renderer* render;
            float x;
            float y;
            float squareSize;
            TTF_Font* _font;
            KeyPressed oldKeyPressed;
            KeyPressed _key;
            std::map<std::string, SDL_Texture*> charMap;
            std::string _gameName;
            std::string _playerName;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDiplay;

            void sortScore(std::size_t textSize);
            int getNumber(std::string);
            void addScoreTabToDisplay(void);
            void pickColor(const std::unordered_map<std::string, Color> patternMap);
            void checkTwoChar(std::size_t j, std::string str);
            SDL_Texture* madeRectangle(int r, int g, int b);
    };
};
```

### Classe : LibMenu

La classe `LibMenu`, permet de définir le menu afin que l'utilisateur sélectionne le jeu auquel il souhaite jouer ainsi que la librairie dans laquelle il souhaite afficher le jeu.

> LibMenu.hpp

``` c++
namespace arcade {
    class LibMenu : virtual public arcade::IGameModule {
        public:
            LibMenu();
            ~LibMenu() {};
            void resetGame() override;
            std::array<std::string, 23> getMap() const override;
            std::size_t getMapCellSize() const override;
            std::unordered_map<std::string, Color> getPattern() const override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() const override;
            void incrementTime() override {};
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::pair<std::size_t, std::size_t> getIndexes() const override;
            void initText(const std::vector<std::string>, const std::vector<std::string>) override;
            std::string getGameName() const override;
            std::size_t getScore() const override;
        private:
            std::vector<std::string> _gameLibName;
            std::vector<std::string> _graphicalName;
            std::array<std::string, 23> map;
            std::size_t _SelectedGameIndex;
            std::size_t _SelectedLibIndex;
            int _libTypeSelected;

            int changeLibIndex(int index, int change, int nbLib);
    };
}
```

### Classe : LibPacman

La classe `LibPacman`, définit le jeu Pacman qui pourra être lancé à partir du menu disponible dans le jeu avec l'une des librairies graphiques disponibles.

> LibPacman.hpp

``` c++
namespace arcade {
    class LibPacman : virtual public arcade::IGameModule {
        public:
            LibPacman();
            ~LibPacman() {};
            void resetGame() override;
            std::array<std::string, 23> getMap() const override;
            std::size_t getMapCellSize() const override;
            std::unordered_map<std::string, Color> getPattern() const override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() const override;
            void incrementTime() override {};
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::pair<std::size_t, std::size_t> getIndexes() const override;
            void initText(const std::vector<std::string>, const std::vector<std::string>) override {};
            std::string getGameName() const override;
            std::size_t getScore() const override;
        private:
            void init();
            int findPlayer();
            void updateKeyPressed(arcade::KeyPressed key);
            bool isAvailable(char c);
            void moovePlayer(arcade::KeyPressed key);
            bool tpPlayerSide(arcade::KeyPressed key, int defaultX, int defaultY);
            void changePlayerPos(arcade::KeyPressed key);
            void moovePlayerBis(arcade::KeyPressed key);
            void addScore(char c);
            void changeGhostState(void);
            void isGameWin(void);

            void launchMooveGhost();
            void getNexGhost();
            bool tpGhostSide(arcade::KeyPressed key, int defaultX, int defaultY);
            void changeGhostPos(arcade::KeyPressed key);
            arcade::KeyPressed randKey(arcade::KeyPressed key1, arcade::KeyPressed key2, arcade::KeyPressed key3);
            arcade::KeyPressed changeGhostKey(arcade::KeyPressed key);
            arcade::KeyPressed mooveGhost(arcade::KeyPressed key);
            bool isAvailableGhost(char c);
            void wallBoxGhost(void);

            std::array<std::string, 23> map;
            std::string _gameName;
            std::size_t mapSize;
            std::size_t playerX;
            std::size_t playerY;
            GameStatus gameStatus;
            KeyPressed keyPressed;
            KeyPressed keyPressedGhost;
            int score;
            bool pacBuff;
            std::chrono::_V2::steady_clock::time_point timeEatBuff;
            KeyPressed oldkeyPressed;

            std::size_t ghostX;
            std::size_t ghostY;
            std::array<arcade::KeyPressed, 4> keyGhost = {arcade::UP, arcade::UP, arcade::UP, arcade::UP};
            std::array<std::pair<std::pair<std::size_t, std::size_t>, char>, 4> ghostPos;
            std::pair<std::size_t, std::size_t> ghostEat;
            int ghostID;
            char ghostChar;
            bool ghostCanMoove;
            
            std::chrono::_V2::steady_clock::time_point timeStart;
    };
}
```

### Classe : LibSnake

La classe `LibSnake`, définit le jeu Snake qui pourra être lancé à partir du menu disponible dans le jeu avec l'une des librairies graphiques disponibles.

> LibSnake.hpp

``` c++
namespace arcade {
    class LibSnake : virtual public arcade::IGameModule {
        public:
            LibSnake();
            ~LibSnake() {};
            void resetGame() override;
            std::array<std::string, 23> getMap() const override;
            std::size_t getMapCellSize() const override;
            std::unordered_map<std::string, Color> getPattern() const override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() const override;
            void incrementTime() override {};
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::pair<std::size_t, std::size_t> getIndexes() const override;
            void initText(const std::vector<std::string>, const std::vector<std::string>) override {};
            std::string getGameName() const override;
            std::size_t getScore() const override;
        protected:
        private:
            void getQueue();
            void findPlayer();
            bool isAvailable(char c);
            bool isAvailableFood(char c);
            void getSnakeLenght();
            void init();
            int moovePlayer(arcade::KeyPressed Key);
            int moove();
            void changePlayerPos();
            void placeFood(size_t y = 50, size_t x = 50);
            void fillVector();

            size_t speed;
            size_t scoreCopy;
            size_t foodY;
            size_t foodX;
            std::string _gameName;
            std::vector<std::pair<int, int>> MyVector;
            KeyPressed keyPressed;
            std::size_t queueY;
            std::size_t queueX;
            std::size_t playerX;
            std::size_t playerY;
            std::size_t mapSize;
            std::size_t SnakeLenght;
            std::array<std::string, 23> map;
            enum Direction {
                DROITE,
                HAUT,
                GAUCHE,
                BAS
            };
            Direction direction;
            size_t score;
    };
}
```

### Classe : LibError

La classe `LibError`, permet une gestion d'erreur centralisée pour tout le programme.

> LibError.hpp

``` c++
class LibError : public std::exception {
    public:
        LibError();
        const char *what() const noexcept;
    private:
        std::string _errorMessage;
};
```

## Enum
### Enum : KeyPressed

L'enum `KeyPressed`, permet de représenter les quelques touches du clavier sélectionné afin de faire des actions prédéfinies comme le déplacement, le changement de libraire graphique en pleine partie, ou même le changement de jeu.

> KeyPressed.hpp

``` c++
namespace arcade
{
    enum KeyPressed
    {
        OTHER,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        R,
        BACKSPACE,
        CLOSE_BUTTON,
        P,
        N,
        G,
        ENTER,
        M
    };
}
```

### Enum : Color

L'enum `Color`, permet l'utilisation de certaines couleurs prédéfinies pour l'affichage des jeux.

> Color.hpp

``` c++
namespace arcade
{
    enum Color
    {
        DEFAULT,
        BLACK,
        WHITE,
        RED,
        BLUE,
        GREEN,
        YELLOW,
        GRAY,
        CYAN
    };
}
```

### Enum : GameStatus

L'enum `GameStatus`, permet de représenter les différents status du jeu sélectionnés, ainsi avec cet enum, nous pouvons faire des actions en conséquence comme par exemple quitter le jeu lorsque le joueur a perdu.

> GameStatus.hpp

``` c++
namespace arcade
{
    enum GameStatus
    {
        PLAYING,
        WON,
        WON_AND_RELOADED,
        LOOSE,
        QUIT,
        NO_ACTIVITY,
        RESET
    };
}
```

# Librairies
Les `librairies`sont essentielles dans le projet, nous allons vous expliquer comment utiliser les librairies déjà implémentées, et comment en implémenter des nouvelles.
## Librairies graphiques

### Les librairies graphique compatible :

``` c++
    arcade_sfml.so,
    arcade_sdl2.so,
    arcade_ncurses.so,
    arcade_qt5.so,
    arcade_ndk++.so,
    arcade_aalib.so,
    arcade_libcaca.so,
    arcade_allegro5.so,
    arcade_xlib.so,
    arcade_gtk+.so,
    arcade_irrlicht.so,
    arcade_opengl.so,
    arcade_vulkan.so
```

### Implémenter une nouvelle librairie graphique

- Créez un nouveau répertoir dans `lib/graphical/le_nom_de_votre_nouvelle_librairie_graphique`
- Placez y vos fichiers constituant votre librairie graphique
- Ajouter un Makefile qui va compiler vos fichier de code, ce Makefile doit créer une libraire dynamique commencant avec le préfixe `arcade_` et se términant par le suffixe `.so` 

Exemple :

`arcade_gtk+.so`

- Cette librairie dynamique doit être deplacé à la racine du dossier `lib`
- Ajouter dans le Makfile principale dans la rélge `graphicals` une ligne qui va compiler le Makefile de votre librairie graphique

Exemple :

> Makefile

``` Makefile
graphicals:
	...
	cd ./lib/graphical/le_nom_de_votre_nouvelle_libraire_graphique/ && make
```

- Après avoir exécuté ces étapes, vous n'aurez plus qu'a lancé le programme en choisissant une jeu et votre librairie graphique.

### Ncurses

La librairie `Ncurses` est définie dans le fichier :
> LibNcurses.hpp&nbsp;&nbsp;&nbsp;[voir](#classe--libncurses)

### SFML

La librairie `SFML` est définie dans le fichier : 
> LibSfml.hpp&nbsp;&nbsp;&nbsp;[voir](#classe--libsfml)

### SDL2

La librairie `SDL2` est définie dans le fichier : 
> LibSdl.hpp&nbsp;&nbsp;&nbsp;[voir](#classe--libsdl)

## Librairies de jeux
### Implémenter un nouveau jeu

- Créez un nouveau répertoir dans `lib/games/le_nom_de_votre_nouveau_jeu `
- Placez y vos fichiers constituant votre jeu
- Ajouter un Makefile qui va compiler vos fichier de code, ce Makefile doit créer une libraire dynamique commencant avec le préfixe `arcade_` et se términant par le suffixe `.so` 

Exemple :

`arcade_centipede.so`

- Cette librairie dynamique doit être deplacé à la racine du dossier `lib`
- Ajouter dans le Makfile principale dans la rélge `graphicals` une ligne qui va compiler le Makefile de votre librairie graphique

Exemple :

> Makefile

``` Makefile
games:
	...
	cd ./lib/games/centipede/ && make
```

- Après avoir exécuté ces étapes, vous n'aurez plus qu'a lancé le programme en choisissant votre jeu et une librairie graphique.

### Pacman

Le jeu `Pacman` est définie dans le fichier :
> LibPacmpan.hpp&nbsp;&nbsp;&nbsp;[voir](#classe--libpacman)

### Snake

Le jeu `Snake` est définie dans le fichier :
> LibSnake.hpp&nbsp;&nbsp;&nbsp;[voir](#classe--libsnake)

## Compiler et lancer le programme

A la racine du projet, vous pouvez faire la commande `make` afin de compiler le core et les différentes librairies, ensuite vous pouvez lancer le programme avec le binaire `arcade` ainsi qu'avec une [libraire graphique](#librairies-graphiques) disponible dans `lib/`.

Exemple :

``` Bash
[root@bd8bdd9c0458 home]# make
...
[root@bd8bdd9c0458 home]# ls
arcade  doc  lib  Makefile  src
[root@bd8bdd9c0458 home]# ./arcade lib/
arcade_menu.so     arcade_ncurses.so  arcade_pacman.so   arcade_sdl2.so     arcade_sfml.so     arcade_snake.so    games/             graphical/         includes/
[root@bd8bdd9c0458 home]# ./arcade lib/arcade_ncurses.so
```
