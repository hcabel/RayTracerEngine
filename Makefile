# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 22:46:07 by hcabel            #+#    #+#              #
#    Updated: 2020/10/24 14:01:29 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG				=	yes

NAME				=	rt
LIB_NAME			=	ftprintf SDL2

OBJECT_FOLDER		=	objects
SOURCES_FOLDER		=	srcs
INCLUDES_FOLDER		=	include

# find srcs -type f | rev | cut -d '/' -f1 | rev | sort -d
SRCS				=	aabb_algo.c					\
						coordinates_utils.c			\
						create_lists.c				\
						details_panel.c				\
						draw_call.c					\
						exit.c						\
						free.c						\
						init.c						\
						init_components.c			\
						init_interfaces.c			\
						init_details_panel.c		\
						init_viewmode_panel.c		\
						input.c						\
						keyboard_input.c			\
						loop.c						\
						main.c						\
						matrix44.c					\
						mouse_press_input.c			\
						mouse_move_input.c			\
						normal_map.c				\
						parse_camera_parameters.c	\
						parse_components.c			\
						parse_lights_parameters.c	\
						parse_objects_parameters.c	\
						parse_parameter_values.c	\
						parse_primary_infos.c		\
						parsing.c					\
						raymarching.c				\
						raymarching_thread.c		\
						rotations.c					\
						sdf_1.c						\
						thread_utils.c				\
						trace_ray.c					\
						vector_2.c					\
						vector2d.c					\
						vector4d.c					\
						vector.c					\
						vector_init.c				\
						viewmode_button_clicked.c	\
						init_viewmode_buttons.c		\
						viewmode_panel.c			\
						viewport_panel.c			\
						shape_selector_display.c	\
						light_ray.c					\
						uncompress_tga.c			\
						tga_reader.c				\
						fill_uncompressed_data.c	\
						interface_images.c			\


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

LIBS				=	$(foreach lib, $(LIB_NAME), -L $(lib) -l$(lib)) -lm -pthread

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
