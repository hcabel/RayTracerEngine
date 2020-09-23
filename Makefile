# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 22:46:07 by hcabel            #+#    #+#              #
#    Updated: 2020/09/23 23:12:35 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG				=	yes

ifeq ($(DEBUG), yes)
	FLAGS			=	-g
	COLOR			=	\033[31m
else
	FLAGS			=	-Wall -Wextra -Werror
	COLOR			=	\033[32m
endif

NAME				=	rt

NAME_FOLDER_OBJECT 	= 	objects

PATH_SOURCES		=	./srcs/
PATH_INCLUDES		=	./includes/
PATH_OBJECT			=	$(NAME_FOLDER_OBJECT)/

LIST_INCLUDES		=	rt.h	\
						types.h

LIST_BASIC			=	main.c

SOURCES				=	$(addprefix $(PATH_SOURCES), $(LIST_BASIC))
OBJECTS				=	$(addprefix $(PATH_OBJECT), $(LIST_BASIC:.c=.o))

INCLUDES			=	$(PATH_INCLUDES) ./SDL2/include/ ./libft/includes/
LIB					=	-L ./SDL2/build -lSDL2 ./libft/libftprintf.a

.PHONY:		re clean fclean all relibft refclean libft
.SILENT:	re fclean clean all relibft refclean libft	\
				$(NAME) $(OBJECTS) $(NAME_FOLDER_OBJECT)

all: libft $(NAME)

libft:
	make -C libft/

$(NAME): $(NAME_FOLDER_OBJECT) $(OBJECTS)
	echo "[Create] Binary"
	gcc -o $(NAME) $(OBJECTS) $(LIB)

$(PATH_OBJECT)%.o: $(PATH_SOURCES)%.c
	echo "	CC	$<"
	gcc -o $@ $(FLAGS) $(addprefix -I, $(INCLUDES)) -c $<

$(NAME_FOLDER_OBJECT):
	echo "[Create] Object folder"
	mkdir -p $(NAME_FOLDER_OBJECT)

clean:
	make -C libft/ clean
	echo "[Remove] Object folder"
	rm -rf $(NAME_FOLDER_OBJECT)

fclean:
	make -C libft/ fclean
	echo "[Remove] Binary"
	rm -f $(NAME)
	echo "[Remove] Object folder"
	rm -rf $(NAME_FOLDER_OBJECT)

re: relibft refclean $(NAME)

refclean:
	echo "[Remove] Binary"
	rm -f $(NAME)
	echo "[Remove] Object folder"
	rm -rf $(NAME_FOLDER_OBJECT)

relibft:
	make -C libft/ re
