/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** main
*/

#include "core.hpp"
#include "errorHandling.hpp"
#include <iostream>

void displayUsage(void)
{
    std::cout << "./arcade [Lib]" << std::endl << std::endl;
    std::cout << "[Lib] :\tpath to the graphical library used at the start of arcade" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        displayUsage();
        return 84;
    }
    try {
        Core core(argc, argv);
        core.gameLoop();
    } catch (const LibError& e) {
        std::cerr << "unexpected error: " << e.what() << std::endl;
        return 84;
    } catch (const SaveError& e) {
        std::cerr << "unexpected error: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
