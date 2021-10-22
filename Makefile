# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 14:28:33 by cado-car          #+#    #+#              #
#    Updated: 2021/10/22 15:38:10 by cado-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex
LIBFT 		= libft.a

LFT_PATH 	= ./libft/
INCLUDES 	= ./include
SRCDIR 		= ./srcs/

SRC 		= $(SRCDIR)pipex.c \
				$(SRCDIR)pipex_utils1.c \
				$(SRCDIR)pipex_utils2.c \
				$(SRCDIR)pipex_error.c

OBJ=$(notdir $(SRC:.c=.o))
#OBJ= fdf.o

#compilation
CF 			= -Wall -Wextra -Werror
CC 			= clang
CFI 		= -I$(INCLUDES)

#common commands
RM =rm -f

#rules
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@printf "\n$(CY)Generating pipex executable...$(RC)\n"
	$(CC) $(CF) -o $(NAME) $(OBJ) -L $(LFT_PATH) -lft
	mkdir objs
	mv $(OBJ) objs/
	@printf "$(GR)Done!$(RC)\n\n"

$(OBJ): $(SRC)
	@printf "\n$(CY)Compiling source files...$(RC)\n"
	$(CC) $(CF) -g -c -I ./includes/ $(SRC)
	@printf "$(GR)Objects ready!$(RC)\n\n"

$(LIBFT):
	@printf "\n$(GR)Generating Libft...$(RC)\n"
	@make -C $(LFT_PATH)
	@printf "$(GR)Libft created!$(RC)\n\n"

bonus: all

re: fclean all

rebonus: fclean bonus

clean:
	@printf "\n$(YE)Cleaning all object files from libft...$(RC)\n"
	@make clean -C $(LFT_PATH)
	@printf "$(GR)Libft objects removed!$(RC)\n\n"
	$(RM) -rf $(OBJ) objs/

fclean: clean
	@printf "\n$(YE)Cleaning all additional objects and libraries...$(RC)\n"
	$(RM) -rf $(NAME) objs/
	@make fclean -C $(LFT_PATH)
	@printf "$(GR)All libraries and executables removed!$(RC)\n\n"

.PHONY: clean fclean re rebonus all bonus

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m