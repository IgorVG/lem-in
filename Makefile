# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/14 16:59:10 by igarbuz           #+#    #+#              #
#    Updated: 2019/06/27 14:03:25 by ibaran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# make of printf must only prepare .o objects using dependencies from libft

NAME		=	lem-in

USER		=	`whoami`

SRC_NAME	=	lemin.c \
				check_input.c \
				checks_for_check_input.c \
				append_graph.c \
				append_graph_lib.c \
				append_graph_lib_checks.c \
				error_handler.c \
				g_tofree.c \
				initialize.c \
				find_paths.c \
				init_for_paths.c \
				check_count_for_paths.c \
				move_remove_for_paths.c \
				add_to_previous.c \
				copy_before_or_after.c \
				set_reset_for_paths.c \
				find_shortest.c \
				retain_input.c \
				move_ants.c \
				print_ants.c \
				calc_steps.c \
				viewer.c \
				draw_ants.c \
				draw_control.c \
				draw_map.c

HEAD_NAME	= 	lemin.h

LIB_NAME	=	libft.a

PRINTF_NAME	=	libftprintf.a

OBJ_NAME	=	$(SRC_NAME:.c=.o)

SRC_PATH	=	./srcs

HEAD_PATH	=	./includes

LIB_PATH	=	./libft

CFLAGS		=	-Wall -Wextra -Werror

SDL_INC		=	/Users/$(USER)/.brew/Cellar/sdl2/2.0.9_1/include/SDL2/
SDL_TTF_INC	=	/Users/$(USER)/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2/
SDL			=	/Users/$(USER)/.brew/Cellar/sdl2/2.0.9_1/lib/
SDL_TTF		=	/Users/$(USER)/.brew/Cellar/sdl2_ttf/2.0.15/lib/

PRINTF_PATH	=	./printf

OBJ_PATH	=	./obj

SRC			=	$(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ			=	$(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))

HEAD		=	$(addprefix $(HEAD_PATH)/, $(HEAD_NAME))

LIBFT		=	$(LIB_PATH)/$(LIB_NAME)

PRINTF		=	$(PRINTF_PATH)/$(PRINTF_NAME)

CC			=	gcc

CPPFLAGS	=	-I$(HEAD_PATH) -I$(LIB_PATH) -I$(PRINTF_PATH) \
				-I$(SDL_INC) -I$(SDL_TTF_INC)

LIBS		=	-lft -L$(LIB_PATH) -lftprintf -L$(PRINTF_PATH) -lSDL2 \
				-L$(SDL) -lSDL2_ttf -L$(SDL_TTF)

all: $(NAME)

$(NAME): obj $(OBJ) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(LIBS) $(CPPFLAGS) $(OBJ) -o $(NAME)
obj:
	@$(MAKE) -sC $(LIB_PATH)
	@$(MAKE) -sC $(PRINTF_PATH)
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEAD)
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(LIBFT):
	@$(MAKE) -sC $(LIB_PATH)

$(PRINTF):
	@$(MAKE) -sC $(PRINTF_PATH)

norm:
	norminette $(SRC) $(HEAD) | grep -B1 $(RED)"Error*"$(RESET)

clean:
	@$(MAKE) -sC $(LIB_PATH) clean
	@$(MAKE) -sC $(PRINTF_PATH) clean
	rm -f $(OBJ) $@
	rm -rf $(OBJ_PATH) $@

fclean: clean
	@$(MAKE) -sC $(LIB_PATH) fclean
	@$(MAKE) -sC $(PRINTF_PATH) fclean
	rm -f $(NAME) $@

debug: CFLAGS += -g
debug: re

re: fclean all

.PHONY: all clean fclean re norm debug
