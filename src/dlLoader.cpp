/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** DlLoader
*/

#include "dlLoader.hpp"

bool DlLoader::isGraphicalLibExist(std::string path)
{
    for (int i = 0; i < NB_LIB_GRAPHICAL; i++) {
        if (path == allGraphicalLibraryPath[i]) {
            return true;
        }
    }
    return false;
}

bool DlLoader::isGameLibExist(std::string path)
{
    for (int i = 0; i < NB_LIB_GAME; i++) {
        if (path == allGameLibraryPath[i]) {
            return true;
        }
    }
    return false;
}

std::vector <std::string> DlLoader::getGraphicalPath(void)
{
    std::deque<std::string> path = allLibAvailable();
    std::vector <std::string> libPath;
    for (int i = 0; i < path.size(); i++) {
        if (isGraphicalLibExist(path.at(i)) == true) {
            libPath.push_back(path.at(i));
        }
    }
    return libPath;
}

std::vector <std::string> DlLoader::getGamePath(void)
{
    std::deque<std::string> path = allLibAvailable();
    std::vector <std::string> libPath;
    for (int i = 0; i < path.size(); i++) {
        if (isGameLibExist(path.at(i)) == true) {
            libPath.push_back(path.at(i));
        }
    }
    return libPath;
}

bool DlLoader::isALib(std::string path)
{
    if (path.size() < 5) {
        return false;
    }
    std::string tmp;
    for (int i = path.size() - 1; i > (path.size() - 4); i--) {
        path.erase(i, 0);
        tmp.push_back(path.at(i));
    }
    if (tmp.compare("os.") == 0) {
        return true;
    }
    return false;
}

std::deque<std::string> DlLoader::allLibAvailable (void)
{
    DIR *dir;
    struct dirent *en;
    dir = opendir("./lib/");
    std::deque<std::string> path;
    if (dir) {
        while ((en = readdir(dir)) != NULL) {
            if (isALib(en->d_name) == true)
                path.push_back(en->d_name);
        }
        closedir(dir);
    }
    return path;
}

void DlLoader::entryPointGraphical(std::string path)
{
    void *handle;
    arcade::IDisplayModule * (*do_somthing)(void);
    char *err;
    std::string realPath = "./lib/";
    realPath.append(path);
    handle = dlopen(realPath.c_str() , RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    dlerror();
    do_somthing = (arcade::IDisplayModule * (*)(void)) dlsym(handle, "entryPoint");
    err = dlerror();
    if (err != NULL) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    _IDisplayModulePair = {(*do_somthing)(), handle};
}

std::pair <arcade::IDisplayModule *,void *> DlLoader::getAIDisplayModule(int index)
{
    std::string path = getGraphicalPath().at(index);
    entryPointGraphical(path);
    return _IDisplayModulePair;
}

void DlLoader::entryPointGame(std::string path)
{
    void *handle;
    arcade::IGameModule * (*do_somthing)(void);
    char *err;
    std::string realPath = "./lib/";
    realPath.append(path);
    handle = dlopen(realPath.c_str() , RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    dlerror();
    do_somthing = (arcade::IGameModule * (*)(void)) dlsym(handle, "entryPoint");
    err = dlerror();
    if (err != NULL) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    _IGameModulePair = {(*do_somthing)(), handle};
}

std::pair <arcade::IGameModule *,void *> DlLoader::getAIGameModule(int index)
{
    std::string path;
    if (index == -1) {
        path = "arcade_menu.so";
    } else {
        path = getGamePath().at(index);
    }
    entryPointGame(path);
    return _IGameModulePair;
}
