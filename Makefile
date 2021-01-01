# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 22:46:07 by hcabel            #+#    #+#              #
#    Updated: 2020/12/31 14:24:24 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG				=	yes

NAME				=	rt
LIB_NAME			=	ftprintf SDL2 OpenCL

OBJECT_FOLDER		=	objects
SOURCES_FOLDER		=	src
INCLUDES_FOLDER		=	include

# find src -type f | rev | cut -d '/' -f1 | rev | sort -d
SRCS				=	aabb_algo.c						\
						coordinates_utils.c				\
						error.c							\
						exit.c							\
						free.c							\
						init.c							\
						input.c							\
						kernel_init.c					\
						keyboard.c						\
						main.c							\
						matrix44.c						\
						mouse_move.c					\
						mouse_move_on_left_panel.c		\
						mouse_move_on_top_panel.c		\
						mouse_press.c					\
						mouse_press_on_left_panel.c		\
						mouse_press_on_top_panel.c		\
						new_components.c				\
						new_vector.c					\
						parsing.c						\
						parsing_camera_component.c		\
						parsing_color_structures.c		\
						parsing_header.c				\
						parsing_light_component.c		\
						parsing_object_component.c		\
						parsing_scene.c					\
						parsing_vector_structures.c		\
						primary.c						\
						rotation.c						\
						threads.c						\
						vector_2.c						\
						vector2d.c						\
						vector4d.c						\
						vector.c						\
						left_panel.c					\
						top_panel.c						\
						viewport_panel.c				\
						init_interfaces.c				\
						init_top_panel.c				\
						init_left_panel.c				\
						clicked_viewmode.c				\
						mouse_wheel.c					\
						resize_window.c					\
						cpu_render.c					\
						trace_ray.c						\
						normal_map.c					\
						light_ray.c						\
						gpu.c

ifeq ($(DEBUG), yes)
	FLAGS			=	-g
else
	FLAGS			=	-Wall -Wextra -Werror -g
endif

NL					=	$

HEADER				=	$(shell find $(INCLUDES_FOLDER) -type f | grep "\.h$(NL)")									\
						$(foreach libname, $(LIB_NAME), $(shell find $(libname)/include -type f | grep "\.h$(NL)"))

INC_PATH			=	$(shell find . -type d | grep "/include")

PATH_SOURCES		=	$(shell find $(SOURCES_FOLDER) -type d )

OBJECTS				=	$(addprefix $(OBJECT_FOLDER)/, $(SRCS:.c=.o))

LIBS				=	-lm -pthread									\
						-L ftprintf -l ftprintf							\
						-L OpenCL/lib -l OpenCL							\
						-L SDL2 -lSDL2 -D_GNU_SOURCE=1 -D_REENTRANT -ldl

vpath %.c $(foreach dir, $(PATH_SOURCES), $(dir):)

.PHONY:		re clean fclean all relib refclean lib
.SILENT:	re fclean clean all relib refclean lib	\
				$(NAME) $(OBJECTS) $(OBJECT_FOLDER)

all: lib $(NAME)
	echo "[Binary Updated]\n"

lib:
	#$(foreach lib, $(LIB_NAME), make -C $(lib);)

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
