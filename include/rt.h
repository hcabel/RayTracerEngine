/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:45:47 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/25 19:35:04 by hcabel           ###   ########.fr       */
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
# define GOOD 0
# define UNKNOWN_ERROR 1
# define MALLOC_ERROR 2
# define SDL_ERROR 3
# define PARSING_ERROR 4

# define UPDATE_VIEWPORT new_viewport_frame_render

/*
********************************************************************************
**	frame Directory
********************************************************************************
*/

/*
**	loop.c
*/
int		loop(t_info *info);

/*
**	draw_call.c
*/
void	draw_calls_clear_list(t_info *info);
void	draw_calls_add(t_info *info, void (*new)(t_info *info));
void	draw_calls_execution(t_info *info);

/*
********************************************************************************
**	player Directory
********************************************************************************
*/

/*
**	hook.c
*/
void	hook_event(t_bool *quit, t_info *info);

/*
********************************************************************************
**	viewport Directory
********************************************************************************
*/

/*
**	viewport.c
*/
void	new_viewport_frame_render(t_info *info);

/*
********************************************************************************
**	exit Directory
********************************************************************************
*/

/*
**	error.c
*/
int		program_exit(t_info *info, int code);


/*
**	free.c
*/
void	free_info_struct(t_info *info);

/*
********************************************************************************
**	parsing Directory
********************************************************************************
*/

/*
**	parsing.c
*/
int		parsing(t_scene *scene, char *path);

/*
********************************************************************************
**	init Directory
********************************************************************************
*/

/*
**	init.c
*/
int		init(t_info *info, char *argv);

/*
**	init_scene.c
*/
int		initcam(t_cam *cam);
int		initlight(t_light *light);
int		initobject(t_object *obj);

/*
********************************************************************************
**	parsing Directory
********************************************************************************
*/

/*
**	get_infos.c
*/

int			parse_component_amount(t_scene *scene, int fd);

#endif
