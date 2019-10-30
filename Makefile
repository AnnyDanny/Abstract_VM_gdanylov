SRC_DIR := ./src/
OBJ_DIR := ./obj/
SRC :=  main.cpp \
        Parser.cpp \
        Lexer.cpp \
        Exceptions.cpp \
        Factory.cpp \
        Avm.cpp

HEADERS := Parser.hpp \
        IOperand.hpp \
        Common.hpp \
        Lexer.hpp \
        Exceptions.hpp \
        Factory.hpp \
        Avm.hpp

SRC := $(addprefix $(SRC_DIR), $(SRC))
OBJ := $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.cpp=.o))
NAME = avm
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++17 -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^
	@echo "\033[0;32m$@ was created"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all