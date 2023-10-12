# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 10:27:08 by emlamoth          #+#    #+#              #
#    Updated: 2023/10/12 12:11:25 by fbouchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	controls.c		\
		flood_fill.c	\
		init_data.c		\
		init_text.c		\
		utils.c			\
		main.c			\
		movements.c		\
		parsing.c		\
		parsing_utils.c	\
		parsing_utils2.c\
		raycast.c		\
		raycast_utils.c	\
		minimap.c		\

BONUS =	zcontrols_bonus.c		\
		zflood_fill_bonus.c		\
		zinit_data_bonus.c		\
		zinit_text_bonus.c		\
		zutils_bonus.c			\
		zmain_bonus.c			\
		zmovements_bonus.c		\
		zparsing_bonus.c		\
		zparsing_utils_bonus.c	\
		zparsing_utils2_bonus.c	\
		zraycast_bonus.c		\
		zraycast_utils_bonus.c	\
		zminimap_bonus.c		\

SRCS_DIR = ./srcs/
OBJS_DIR = ./srcs/objs_cub3D/
OBJS = $(SRCS:$(SCRS_DIR)%.c=$(OBJS_DIR)%.o)
HEADERS	:= -I ./include -I $(LIBMLX_DIR)include/

OBJS_BONUS = $(BONUS:$(SCRS_DIR)%.c=$(OBJS_DIR)%.o)

LIBFT_DIR = ./srcs/libft/
LIBFT = ./srcs/libft/libft.a

LIBMLX_DIR	:= ./MLX42/
LIBMLX	:= $(LIBMLX_DIR)/build/libmlx42.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"

NAME = cub3D

NAME_B = cub3D_bonus

CFLAGS = -Wall -Wextra -Werror

CC = gcc

GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0;0m

all: mlx $(NAME)

mlx: #dep
	(cd $(LIBMLX_DIR) && cmake -B build)
	make -C $(LIBMLX_DIR)build/

mlxb: #dep
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

$(NAME_B): $(OBJS_BONUS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBMLX) $(LIBFT) -o $(NAME_B)
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
	@rm -f $(NAME) $(NAME_B)
	@echo "${RED}CUB3D DELETED${NC}"
	@rm -rf $(LIBMLX_DIR)build/
	@echo "${RED}MLX42 DELETED${NC}"


bonus: fclean mlxb $(NAME_B)

re: fclean all

.PHONY: all clean fclean bonus re