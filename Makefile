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

NAME 			= pipex
NAME_BONUS		= pipex_bonus

LIBFT 			= libft.a

SRCDIR 			= srcs/
OBJDIR			= objs/
BINDIR			= bin/
INCLUDE 		= include/
LFT_PATH 		= libft/

#compilation
CC 				= gcc
CF 				= -Wall -Wextra -Werror
CFI 			= -I $(INCLUDE)
LEAK			= -g -fsanitize=address

SRC 			= pipex.c \
				pipex_utils1.c \
				pipex_utils2.c \
				pipex_error.c

SRC_BONUS		= pipex_bonus.c \
				pipex_utils1_bonus.c \
				pipex_utils2_bonus.c \
				pipex_error_bonus.c

OBJ				= $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))
OBJ_BONUS		= $(addprefix $(OBJDIR), $(notdir $(SRC_BONUS:.c=.o)))
OBLIG_FILE		= $(addprefix $(BINDIR), $(NAME))
BONUS_FILE		= $(addprefix $(BINDIR), $(NAME_BONUS))

#common commands
RM 				= rm -rf

#rules
$(OBJDIR)%.o: $(SRCDIR)%.c
				@printf "\n$(CY)Generating pipex objects...$(RC)\n"
				mkdir -p $(OBJDIR)
				$(CC) $(CF) $(CFI) -c $< -o $@
				@printf "$(GR)Object ready!$(RC)"

$(NAME): 		$(OBLIG_FILE)

$(OBLIG_FILE):	$(OBJ) | $(LIBFT) 
				@printf "\n$(CY)Generating pipex executable...$(RC)\n"
				mkdir -p $(BINDIR)
				$(CC) $(CF) $(OBJ) -L $(LFT_PATH) -lft -o $(OBLIG_FILE)
				$(RM) $(BONUS_FILE)
				cp $(OBLIG_FILE) $(NAME)
				@printf "$(GR)Done!$(RC)\n\n"

$(NAME_BONUS):	$(BONUS_FILE)

$(BONUS_FILE):	$(OBJ_BONUS) | $(LIBFT)
				@printf "\n$(CY)Generating pipex bonus executable...$(RC)\n"
				mkdir -p $(BINDIR)
				$(CC) $(CF) $(OBJ_BONUS) -L $(LFT_PATH) -lft -o $(BONUS_FILE)
				$(RM) $(OBLIG_FILE)
				cp $(BONUS_FILE) $(NAME)
				@printf "$(GR)Done!$(RC)\n\n"

$(LIBFT):
				@printf "\n$(CY)Generating Libft...$(RC)\n"
				@make -C $(LFT_PATH)
				@printf "$(GR)Libft created!$(RC)\n"

all: 			$(NAME)

bonus: 			$(NAME_BONUS)

re: 			fclean all

rebonus: 		fclean bonus

clean:
				@printf "\n$(YE)Cleaning all object files from libft...$(RC)\n"
				@make clean -C $(LFT_PATH)
				@printf "$(RE)Libft objects removed!$(RC)\n\n"
				$(RM) $(OBJ) $(OBJDIR)
				$(RM) $(OBJ_BONUS) $(OBJDIR_BONUS)
				@printf "$(RE)Pipex objects removed!$(RC)\n\n"

fclean: 		clean
				@printf "\n$(YE)Cleaning all executables...$(RC)\n"
				$(RM) $(OBJDIR)
				$(RM) $(BINDIR)
				$(RM) $(NAME)
				@make fclean -C $(LFT_PATH)
				@printf "$(RE)Executables removed!$(RC)\n\n"

.PHONY:			all bonus clean fclean re rebonus $(NAME)

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m