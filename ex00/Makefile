# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afournie <afournie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/20 11:54:43 by afournie          #+#    #+#              #
#    Updated: 2026/09/22 10:43:57 by afournie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		= .
OBJ_DIR		= obj

SRC			=	main.cpp			\
				ScalarConverter.cpp	\

INC			= ScalarConverter.hpp

OBJ			= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

CC			= c++
CFLAGS		= -std=c++98 -Wall -Wextra -Werror -Wshadow

RM			= rm -rf

NAME		= ex00

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
