/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:45:47 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/07 14:09:12 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
**	Lib includes
*/
# include <pthread.h>
# include <stdlib.h>
# include "SDL.h"
# include "ft_printf.h"

/*
**	Personal includes
*/
# include "mathematical.h"
# include "types.h"
# include "interfaces.h"

/*
********************************************************************************
**	frame Directory
********************************************************************************
*/

/*
**	loop.c
*/
int				loop(t_info *info);

/*
**	draw_call.c
*/
void			draw_calls_clear_list(t_info *info);
void			draw_calls_add(t_info *info, void (*new)(t_info *info));
void			draw_calls_execution(t_info *info);

/*
********************************************************************************
**	player Directory
********************************************************************************
*/

/*
**	hook.c
*/
void			hook_event(t_bool *quit, t_info *info);

/*
********************************************************************************
**	screen Directory
********************************************************************************
*/

/*
**	viewport.c
*/
void			new_viewport_frame(t_info *info);
void			check_viewport_render(t_info *info);

/*
**	details_panel.c
*/
void			new_details_panel_frame(t_info *info);

/*
**	view_mode_panel.c
*/
void			new_viewmode_panel_frame(t_info *info);

/*
********************************************************************************
**	exit Directory
********************************************************************************
*/

/*
**	error.c
*/
int				program_exit(t_info *info, int code);


/*
**	free.c
*/
void			free_info_struct(t_info *info);

/*
********************************************************************************
**	parsing Directory
********************************************************************************
*/

/*
**	parsing.c
*/
int				parsing(t_scene *scene, char *path);

/*
**	parse_primary_infos.c
*/
int				parse_component_amount(t_scene *scene, int fd);

/*
**	parse_components.c.c
*/
int				parse_components(t_scene *scene, int fd);

/*
**	parse_objects_parameters.c
*/
void			parse_objects_parameters(t_object *object, char *line,
					unsigned int line_amount);

/*
**	parse_lights_parameters.c
*/
void			parse_lights_parameters(t_light *light, char *line,
					unsigned int line_amount);

/*
**	parse_camera_parameters.c
*/
void			parse_camera_parameters(t_cam *cam, char *line,
					unsigned int line_amount);

/*
**	parse_parameter_values.c
*/
t_vector		parse_vector(char *line, unsigned int line_amount);
t_vector2d		parse_vector2d(char *line, unsigned int line_amount);
t_vector		parse_color(char *line, unsigned int line_amount);

/*
********************************************************************************
**	init Directory
********************************************************************************
*/

/*
**	init.c
*/
int				init(t_info *info, char *argv);

/*
**	init_components.c
*/
void			initcam(t_cam *cam);
void			initlight(t_light *light);
void			initobject(t_object *obj);

/*
**	create_lists.c
*/
int				create_light_list(t_scene *scene);
int				create_object_list(t_scene *scene);

/*
**	init_interfaces.c
*/
int				init_interfaces(t_screen *screen);

/*
**	viewmode_init_buttons.c
*/
int		viewmode_init_buttons(t_scrollbox *viewmode);

/*
********************************************************************************
**	ray Directory
********************************************************************************
*/

/*
**	raymarching.c
*/
unsigned int	raymarching(t_scene *scene, t_vector dir);

/*
**	trace_ray.c
*/
t_ray_result	trace_ray(t_scene *scene, t_vector start_location,
					t_vector dir, float max_distance);

/*
********************************************************************************
**	threads Directory
********************************************************************************
*/

/*
**	thread_utils.c
*/
int				all_threads_are_done(t_sampling *sampling);

/*
**	raymarching_thread.c
*/
void			*thread_calculs_functions(void *p);

/*
********************************************************************************
**	Signed_Distance_Functions Directory
********************************************************************************
*/

/*
**	sdf_1.c
*/
float			sdf_cube(t_vector p, t_vector obj_scale);
float			sdf_plane(t_vector p, t_vector obj_scale);
float			sdf_cylinder(t_vector p, t_vector obj_scale);
float			sdf_sphere(t_vector p, t_vector obj_scale);
float			sdf_cone(t_vector p, t_vector obj_scale);

/*
********************************************************************************
**	effects Directory
********************************************************************************
*/

/*
**	normal_map.c
*/
t_vector	get_normal_map(t_vector p, t_scene *scene, t_object *hit_obj);
t_vector	normal_map_to_rgb(t_vector normal);


#endif
