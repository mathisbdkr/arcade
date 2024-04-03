/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-wilson.bordichon
** File description:
** errorHandling
*/

#ifndef ERRORHANDLING_HPP_
    #define ERRORHANDLING_HPP_

    #include <string>

class LibError : public std::exception {
    public:
        LibError();
        const char *what() const noexcept;
    private:
        std::string _errorMessage;
};

class SaveError : public std::exception {
    public:
        SaveError();
        const char *what() const noexcept;
    private:
        std::string _errorMessage;
};

#endif /* !ERRORHANDLING_HPP_ */
