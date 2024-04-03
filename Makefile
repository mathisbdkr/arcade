##
## EPITECH PROJECT, 2023
## test
## File description:
## Makefile
##
msg:
	@echo -e "\x1b[1m\x1b[38;2;0;0;255m ####                               ####                        #     #                 #  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;42;0;213m#    #  ###    ###    ###          #    #  ###   ## #   #####         #       ###       #  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;84;0;171m#      #   #  #      #   #         #      #   #  # # #  #    # ##     #      #   #   ####  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;126;0;129m#      #   #  #      ####          #      #   #  # # #  #    #  #     #      ####   #   #  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;168;0;87m#    # #   #  #      #             #    # #   #  # # #  #####   #     #      #      #   #  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;210;0;45m ####   ###   #       ####          ####   ###   # # #  #      ###     ##     ####   ####  \x1b[0m"
	@echo -e "\x1b[1m\x1b[38;2;252;0;3m                                                        #                                  \x1b[0m"

SRC = ./src/core.cpp	\
	./src/dlLoader.cpp	\
	./src/errorHandling.cpp	\
	./src/main.cpp	\
	./src/coreLibActions.cpp

OBJ = $(SRC:.cpp=.o)

CFLAGS = -Wall -Wextra -I lib/includes

BIN_NAME = arcade

CC = g++

core: $(OBJ) msg
	$(CC) -o $(BIN_NAME) $(OBJ) $(CFLAGS)

graphicals:
	cd ./lib/graphical/libSfml/ && make re
	cd ./lib/graphical/libSdl/ && make re
	cd ./lib/graphical/libNcurses/ && make re

games:
	cd ./lib/games/pacman/ && make re
	cd ./lib/games/snake/ && make re
	cd ./lib/games/menu/ && make re

all: core graphicals games

clean:
	rm -f $(OBJ)
	cd ./lib/graphical/libSfml/ && make clean
	cd ./lib/graphical/libSdl/ && make clean
	cd ./lib/graphical/libNcurses/ && make clean
	cd ./lib/games/pacman/ && make clean
	cd ./lib/games/snake/ && make clean
	cd ./lib/games/menu/ && make clean

fclean: clean
	rm -f $(BIN_NAME)

re: fclean all

.PHONY: clean fclean re
