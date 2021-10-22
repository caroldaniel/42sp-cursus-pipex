# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 14:28:33 by cado-car          #+#    #+#              #
#    Updated: 2021/10/22 18:35:01 by cado-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex
LIBFT 		= libft.a

LFT_PATH 	= ./libft/
INCLUDES 	= ./include/
SRCDIR 		= ./srcs/
SRC 		= pipex.c \
				pipex_utils1.c \
				pipex_utils2.c \
				pipex_error.c

VPATH		:= $(SRCDIR)\

OBJDIR		= ./objs/
OBJ			= $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))

#compilation
CF 			= -Wall -Wextra -Werror
CC 			= gcc
CFI 		= -I $(INCLUDES)

#common commands
RM 			= rm -f

#rules
$(OBJDIR)%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CF) -g $(CFI) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFT)
	@printf "\n$(CY)Generating pipex executable...$(RC)\n"
	$(CC) $(CF) -o $(NAME) $(OBJ) -L $(LFT_PATH) -lft
	@printf "$(GR)Done!$(RC)\n\n"

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
	$(RM) -rf $(OBJ) $(OBJDIR)

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