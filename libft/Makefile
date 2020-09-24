# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 18:27:31 by hcabel            #+#    #+#              #
#    Updated: 2020/09/24 11:37:53 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG				=	no

ifeq ($(DEBUG), yes)
	FLAGS			=	-g
	COLOR			=	\033[31m
else
	FLAGS			=	-Wall -Wextra -Werror
	COLOR			=	\033[32m
endif

NAME				=	libftprintf.a

NAME_FOLDER_OBJECT 	= 	objects

PATH_SOURCES		=	srcs/
PATH_INCLUDE		=	includes/

PATH_OBJECT			=	$(NAME_FOLDER_OBJECT)/

PATH_STR			=	$(PATH_SOURCES)str/
PATH_LST			=	$(PATH_SOURCES)lst/
PATH_PUT			=	$(PATH_SOURCES)put/
PATH_IS				=	$(PATH_SOURCES)is/
PATH_MEM			=	$(PATH_SOURCES)mem/
PATH_PRINTF			=	$(PATH_SOURCES)printf/
PATH_OTHER			=	$(PATH_SOURCES)others/

LIST_STR			=	ft_strlen.c		\
						ft_strdup.c		\
						ft_strcpy.c		\
						ft_strncpy.c	\
						ft_strcat.c		\
						ft_strncat.c	\
						ft_strlcat.c	\
						ft_strchr.c		\
						ft_strrchr.c	\
						ft_strstr.c		\
						ft_strnstr.c	\
						ft_strcmp.c		\
						ft_strncmp.c	\
						ft_strnew.c		\
						ft_strdel.c		\
						ft_strclr.c		\
						ft_striter.c	\
						ft_striteri.c	\
						ft_strmap.c		\
						ft_strmapi.c	\
						ft_strequ.c		\
						ft_strnequ.c	\
						ft_strsub.c		\
						ft_strjoin.c	\
						ft_strtrim.c	\
						ft_strsplit.c	\
						ft_strndup.c

LIST_LST			=	ft_lstnew.c		\
						ft_lstdelone.c	\
						ft_lstdel.c		\
						ft_lstadd.c		\
						ft_lstiter.c	\
						ft_lstmap.c

LIST_PUT			=	ft_putchar.c	\
						ft_putstr.c		\
						ft_putendl.c	\
						ft_putnbr.c		\
						ft_putchar_fd.c	\
						ft_putstr_fd.c	\
						ft_putendl_fd.c	\
						ft_putnbr_fd.c

LIST_OTHER			=	ft_bzero.c		\
						ft_atoi.c		\
						ft_atoi_base.c	\
						ft_toupper.c	\
						ft_tolower.c	\
						ft_itoa.c		\
						ft_sqrt.c		\
						ft_baselen.c	\
						ft_itoa_base.c	\
						ft_nbrlen.c		\
						get_next_line.c	\
						ft_convert_base.c

LIST_IS				=	ft_isalpha.c	\
						ft_isdigit.c	\
						ft_isalnum.c	\
						ft_isascii.c	\
						ft_isprint.c	\
						ft_is_prime.c

LIST_MEM			=	ft_memset.c		\
						ft_memcpy.c		\
						ft_memccpy.c	\
						ft_memmove.c	\
						ft_memchr.c		\
						ft_memcmp.c		\
						ft_memalloc.c	\
						ft_memdel.c

LIST_PRINTF			=	colour.c			\
						ft_printf.c			\
						pf_dispatch.c		\
						pf_parse_flags.c	\
						ft_ftoa.c			\
						get_variable.c		\
						pf_modify_value.c	\
						utils.c

SOURCES				=	$(addprefix $(PATH_STR), $(LIST_STR))		\
						$(addprefix $(PATH_LST), $(LIST_LST))		\
						$(addprefix $(PATH_PUT), $(LIST_PUT))		\
						$(addprefix $(PATH_OTHER), $(LIST_OTHER))	\
						$(addprefix $(PATH_IS), $(LIST_IS))			\
						$(addprefix $(PATH_PRINTF), $(LIST_PRINTF))	\
						$(addprefix $(PATH_MEM), $(LIST_MEM))

OBJECTS				=	$(addprefix $(PATH_OBJECT), $(LIST_STR:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_LST:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_PUT:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_OTHER:.c=.o))	\
						$(addprefix $(PATH_OBJECT), $(LIST_IS:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_PRINTF:.c=.o))	\
						$(addprefix $(PATH_OBJECT), $(LIST_MEM:.c=.o))

INCLUDES			=	$(addprefix -I, $(PATH_INCLUDE))

.PHONY:		re clean fclean all
.SILENT:	re fclean clean all \
				$(NAME) $(OBJECTS) $(NAME_FOLDER_OBJECT)

all: $(NAME)
	echo "[Lib Checked]"

$(NAME): $(NAME_FOLDER_OBJECT) $(OBJECTS)
	echo "[Create] Lib $(NAME)"
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

$(PATH_OBJECT)%.o: $(PATH_STR)%.c Makefile $(PATH_INCLUDE)/libft.h $(PATH_INCLUDE)/ft_printf.h
	echo "	CC	$<"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_LST)%.c Makefile $(PATH_INCLUDE)/libft.h $(PATH_INCLUDE)/ft_printf.h
	echo "	CC	$<"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_PUT)%.c Makefile $(PATH_INCLUDE)/libft.h $(PATH_INCLUDE)/ft_printf.h
	echo "	CC	$<"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_IS)%.c Makefile $(PATH_INCLUDE)/libft.h $(PATH_INCLUDE)/ft_printf.h
	echo "	CC	$<"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_MEM)%.c Makefile $(PATH_INCLUDE)/libft.h $(PATH_INCLUDE)/ft_printf.h
	echo "	CC	$<"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_OTHER)%.c Makefile $(PATH_INCLUDE)/libft.h $(PATH_INCLUDE)/ft_printf.h
	echo "	CC	$<"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_PRINTF)%.c Makefile $(PATH_INCLUDE)/libft.h $(PATH_INCLUDE)/ft_printf.h
	echo "	CC	$<"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(NAME_FOLDER_OBJECT):
	echo "[Create] Object folder"
	mkdir -p $(NAME_FOLDER_OBJECT)

clean:
	echo "[Remove] Object folder"
	rm -rf $(NAME_FOLDER_OBJECT)

fclean: clean
	echo "[Remove] Lib"
	rm -f $(NAME)

re: fclean all
