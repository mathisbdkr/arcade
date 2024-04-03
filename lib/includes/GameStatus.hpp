/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** GameStatus
*/

#ifndef GAMESTATUS_HPP_
#define GAMESTATUS_HPP_

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

#endif /* !GAMESTATUS_HPP_ */