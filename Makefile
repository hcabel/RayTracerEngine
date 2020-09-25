# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 22:46:07 by hcabel            #+#    #+#              #
#    Updated: 2020/09/25 19:35:26 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG				=	yes

NAME				=	rt
LIB_NAME			=	ftprintf SDL2

OBJECT_FOLDER		=	objects
SOURCES_FOLDER		=	srcs
INCLUDES_FOLDER		=	include

SRCS				=	main.c			\
						hook.c			\
						viewport.c		\
						free.c			\
						exit.c			\
						loop.c			\
						draw_call.c		\
						vector.c		\
						vector2d.c		\
						parsing.c		\
						init.c			\
						init_scene.c	\
						vector_utils.c	\
						get_infos.c		\

ifeq ($(DEBUG), yes)
	FLAGS			=	-g
else
	FLAGS			=	-Wall -Wextra -Werror
endif

NL					=	$

HEADER				=	$(shell find $(INCLUDES_FOLDER) -type f | grep "\.h$(NL)")									\
						$(foreach libname, $(LIB_NAME), $(shell find $(libname)/include -type f | grep "\.h$(NL)"))

INC_PATH			=	$(shell find . -type d | grep "/include")

PATH_SOURCES		=	$(shell find $(SOURCES_FOLDER) -type d )

SOURCES				=	$(addprefix $(PATH_SOURCES), $(LIST_BASIC))		\
						$(addprefix $(PATH_PLAYER), $(LIST_PLAYER))

OBJECTS				=	$(addprefix $(OBJECT_FOLDER)/, $(SRCS:.c=.o))

LIBS				=	$(foreach lib, $(LIB_NAME), -L $(lib) -l$(lib)) -lm

vpath %.c $(foreach dir, $(PATH_SOURCES), $(dir):)

.PHONY:		re clean fclean all relib refclean lib
.SILENT:	re fclean clean all relib refclean lib	\
				$(NAME) $(OBJECTS) $(OBJECT_FOLDER)

all: lib $(NAME)
	echo "[Binary Updated]\n"

lib:
	$(foreach lib, $(LIB_NAME), make -C $(lib);)

$(NAME): $(OBJECT_FOLDER) $(OBJECTS)
	echo "[Create] Binary"
	gcc -o $(NAME) $(OBJECTS) $(LIBS)

$(OBJECT_FOLDER)/%.o: %.c $(HEADER) Makefile
	echo "	CC	$<"
	gcc -o $@ $(FLAGS) -c $< $(addprefix -I, $(INC_PATH))

$(OBJECT_FOLDER):
	echo "[Create] Object folder"
	mkdir -p $(OBJECT_FOLDER)

clean:
	make -C libft/ clean
	echo "[Remove] Object folder"
	rm -rf $(OBJECT_FOLDER)

fclean:
	make -C libft/ fclean
	echo "[Remove] Binary"
	rm -f $(NAME)
	echo "[Remove] Object folder"
	rm -rf $(OBJECT_FOLDER)

re: relib refclean $(NAME)

refclean:
	echo "[Remove] Binary"
	rm -f $(NAME)
	echo "[Remove] Object folder"
	rm -rf $(OBJECT_FOLDER)

relib:
	make -C ftprintf/ re
