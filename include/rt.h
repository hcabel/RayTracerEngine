/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:45:47 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/27 18:22:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
**	Lib includes
*/
# include "SDL.h"
# include "ft_printf.h"

/*
**	Personal includes
*/
# include "mathematical.h"
# include "types.h"

/*
**	Modifyable define
*/
# define WINDOW_NAME "RayTracer Engine"
# define WIN_HEIGTH 700
# define WIN_WIDTH 500

/*
**	Code understanding define
*/
# define FAILED -1
# define GOOD 0
# define UNKNOWN_ERROR 1
# define MALLOC_ERROR 2
# define SDL_ERROR 3

# define UPDATE_VIEWPORT new_viewport_frame_render

/*
********************************************************************************
**	frame Directory
********************************************************************************
*/

/*
**	loop.c
*/
int			loop(t_info *info);

/*
**	draw_call.c
*/
void		draw_calls_clear_list(t_info *info);
void		draw_calls_add(t_info *info, void (*new)(t_info *info));
void		draw_calls_execution(t_info *info);

/*
********************************************************************************
**	player Directory
********************************************************************************
*/

/*
**	hook.c
*/
void		hook_event(t_bool *quit, t_info *info);

/*
********************************************************************************
**	viewport Directory
********************************************************************************
*/

/*
**	viewport.c
*/
void		new_viewport_frame_render(t_info *info);

/*
********************************************************************************
**	exit Directory
********************************************************************************
*/

/*
**	error.c
*/
int			program_exit(t_info *info, int code);


/*
**	free.c
*/
void		free_info_struct(t_info *info);

/*
********************************************************************************
**	parsing Directory
********************************************************************************
*/

/*
**	parsing.c
*/
int			parsing(t_scene *scene, char *path);

/*
**	parse_primary_infos.c
*/
int			parse_component_amount(t_scene *scene, int fd);

/*
**	parse_components.c.c
*/
int			parse_components(t_scene *scene, int fd);

/*
**	parse_objects_parameters.c
*/
char		*parse_objects_parameters(t_object *obj, int fd,
				unsigned int *line_amount, char *line);

/*
**	parse_lights_parameters.c
*/
char	*parse_lights_parameters(t_light *light, int fd,
	unsigned int *line_amount, char *line);

/*
**	parse_parameter_values.c
*/
t_vector	parse_vector(char *line, unsigned int line_amount);
t_vector2d	parse_vector2d(char *line, unsigned int line_amount);
t_vector	parse_color(char *line, unsigned int line_amount);

/*
********************************************************************************
**	init Directory
********************************************************************************
*/

/*
**	init.c
*/
int			init(t_info *info, char *argv);

/*
**	init_components.c
*/
void		initcam(t_cam *cam);
void		initlight(t_light *light);
void		initobject(t_object *obj);

/*
**	create_lists.c
*/
int			create_light_list(t_scene *scene);
int			create_object_list(t_scene *scene);

#endif
