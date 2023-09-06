# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 10:27:08 by emlamoth          #+#    #+#              #
#    Updated: 2023/09/06 17:03:13 by emlamoth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c					\
	
LIBFT_DIR = ./srcs/libft/
LIBFT = ./srcs/libft/libft.a
SRCS_DIR = ./srcs/
OBJS_DIR = ./srcs/objs_cub3d/
OBJS = $(SRCS:$(SCRS_DIR)%.c=$(OBJS_DIR)%.o)

NAME = cub3d

CFLAGS = -Wall -Wextra -Werror

CC = gcc

GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0;0m

all:$(NAME)

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	
$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "${GREEN}MINISHELL COMPILED${NC}"

leak: CFLAGS += -g
leak: all
	@reset
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.txt ./cub3d
		
clean:
	@$(MAKE) clean -C ./srcs/libft
	@rm -rf $(OBJS_DIR)
	@echo "${RED}CUB3D OBJECTS DELETED${NC}"

fclean: clean
	@$(MAKE) fclean -C ./srcs/libft
	@rm -f $(NAME)
	@echo "${RED}CUB3D DELETED${NC}"

bonus: all

re: fclean all

.PHONY: all clean fclean bonus re