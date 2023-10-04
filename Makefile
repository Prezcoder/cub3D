# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 10:27:08 by emlamoth          #+#    #+#              #
#    Updated: 2023/10/04 14:48:25 by emlamoth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c			\
		parsing.c		\
		init.c			\
		flood_fill.c	\
		raycast.c		\
		raycast2.c		\
		controls.c		\
		movements.c		\

SRCS_DIR = ./srcs/
OBJS_DIR = ./srcs/objs_cub3D/
OBJS = $(SRCS:$(SCRS_DIR)%.c=$(OBJS_DIR)%.o)
HEADERS	:= -I ./include -I $(LIBMLX_DIR)include/

LIBFT_DIR = ./srcs/libft/
LIBFT = ./srcs/libft/libft.a

LIBMLX_DIR	:= ./srcs/MLX42/
LIBMLX	:= $(LIBMLX_DIR)/build/libmlx42.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror

CC = gcc

GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0;0m

all: mlx $(NAME) 

mlx: #dep
	(cd $(LIBMLX_DIR) && cmake -B build)
	make -C $(LIBMLX_DIR)build/

dep:
	brew install glfw
	brew install cmake

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	
$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBMLX) $(LIBFT) -o $(NAME)
	@echo "${GREEN}CUB3D COMPILED${NC}"

leak: CFLAGS += -g
leak: all
	@reset
	valgrind --leak-check=full --show-leak-kinds=all ./cub3D ./maps/map01.cub
		
clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "${RED}CUB3D OBJECTS DELETED${NC}"
	@$(MAKE) clean -C $(LIBMLX_DIR)build/
	@echo "${RED}MLX42 DELETED${NC}"

fclean: clean
	@$(MAKE) fclean -C ./srcs/libft
	@rm -f $(NAME)
	@echo "${RED}CUB3D DELETED${NC}"
	@rm -rf $(LIBMLX_DIR)build/
	@echo "${RED}MLX42 DELETED${NC}"


bonus: all

re: fclean all

.PHONY: all clean fclean bonus re