# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acottier <acottier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 13:55:41 by acottier          #+#    #+#              #
#    Updated: 2018/09/19 13:36:16 by acottier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[0;33m
NC		=\033[0m

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME 		= libft_malloc_$(HOSTTYPE).so
FLAGS 		= -Wall -Wextra -Werror -g3

SRC_PATH	= sources
OBJ_PATH	= objects

SRC_NAMES 	=	malloc.c \
				free.c \
				realloc.c \
				show_alloc_mem.c \
				allocation_dump.c \
				utilities.c \
				utilities2.c \
				utilities3.c 
				
OBJ_NAMES 	= $(SRC_NAMES:.c=.o)

SRC			= $(addprefix $(SRC_PATH)/,$(SRC_NAMES))
OBJ			= $(addprefix $(OBJ_PATH)/,$(OBJ_NAMES))

.PHONY: all clean fclen re fast

all : $(NAME)

$(NAME) : $(OBJ)
	@(time gcc -shared $(FLAGS) $^ -o $@) 2> time.txt
	@printf "${GREEN}Malloc library compilation finished:${NC} "
	@printf "${YELLOW}"
	@cat time.txt | head -2 | tail -1
	@printf "${NC}"
	@rm time.txt
	@ln -fs $(NAME) libft_malloc.so

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) && gcc $(FLAGS) -o $@ -c $<

clean :
	@rm -rf $(OBJ_PATH)
	@printf "${RED}Malloc library object files deleted.${NC}\n"

fclean : clean
	@rm -f $(NAME) libft_malloc.so
	@printf "${RED}Malloc library deleted.${NC}\n"

re : fclean all

fast : fclean
	gcc $(FLAGS) -c $(SRC)
	mkdir -p $(OBJ_PATH)
	mv $(OBJ_NAMES) $(OBJ_PATH)
	gcc -shared $(FLAGS) $(OBJ) -o $(NAME)
	ln -s $(NAME) libft_malloc.so
