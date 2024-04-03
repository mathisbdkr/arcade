/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** KeyPressed
*/

#ifndef KEYPRESSED_HPP_
#define KEYPRESSED_HPP_

namespace arcade
{
    enum KeyPressed
    {
        OTHER,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        R, // reset ----- done
        BACKSPACE, // exit game  ----- done
        CLOSE_BUTTON, // exit game  ----- done
        P, // previous lib graphic  ----- done
        N, // next lib graphic  ----- done
        G, // swith entre les jeux (en boucle)  ----- done
        ENTER, // alors la c dur de savoir
        M // revenir au menu si on est pas deja dedan
    };
}

#endif /* !KEYPRESSED_HPP_ */