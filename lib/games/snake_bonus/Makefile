##
## EPITECH PROJECT, 2024
## B-OOP-400-PAR-4-1-arcade-wilson.bordichon
## File description:
## Makefile
##

msg:
	@echo -e "\x1b[1m\x1b[38;2;0;0;255m ####                #                     ####                        #     #                 #  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;42;0;213m#      ####    ###   # #     ###          #    #  ###   ## #   #####         #       ###       #  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;84;0;171m ####  #   #      #  ##     #   #         #      #   #  # # #  #    # ##     #      #   #   ####  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;126;0;129m     # #   #   ####  ##     ####          #      #   #  # # #  #    #  #     #      ####   #   #  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;168;0;87m#    # #   #  #   #  # #    #             #    # #   #  # # #  #####   #     #      #      #   #  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;210;0;45m ####  #   #   ####  #  #    ####          ####   ###   # # #  #      ###     ##     ####   ####  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;252;0;3m                                                               #                                  \x1b[0m"

SRC =	./LibSnake.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++

CXXFLAGS = -Wall -Wextra -fPIC

LDFLAGS = -shared

FLAGS_DEBUG = -g3

BIN_NAME = arcade_qix.so

all: $(OBJ) msg
	$(CXX) -c $(CXXFLAGS) $(SRC)
	$(CXX) $(LDFLAGS) -o $(BIN_NAME) $(OBJ)
	mv $(BIN_NAME) ../../

debug: CFLAGS += $(FLAGS_DEBUG)
debug: all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN_NAME)

re: fclean all

.PHONY: clean fclean re
