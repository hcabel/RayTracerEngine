/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:45:47 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 17:54:12 by hcabel           ###   ########.fr       */
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
**	input.c
*/
void			hook_event(t_bool *quit, t_info *info);

/*
**	keyboard_input.c
*/
void			keyboard_input(t_bool *quit, t_info *info, SDL_Event *event);

/*
**	mouse_press_input.c
*/
void			mouse_press_input(t_bool *quit, t_info *info, SDL_Event *event);

/*
**	mouse_move_input.c
*/
void			mouse_move_input(t_bool *quit, t_info *info, SDL_Event *event);

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
int				malloc_scrollbox(t_buttons_scrollbox *sb, unsigned int amount);

/*
**	viewmode_init_buttons.c
*/
int				viewmode_init_buttons(t_buttons_scrollbox *viewmode);

/*
**	init_viewmode_panel.c
*/
int				init_viewmode_panel(t_viewmode_panel *viewmode);

/*
**	init_details_panel.c
*/
int				init_details_panel(t_details_panel *scrollbox);

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
t_ray_hit		trace_ray(t_scene *scene, t_vector start_location,
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

/*
********************************************************************************
**	math Directory
********************************************************************************
*/

/*
**	matrix44.c
*/
t_matrix44f	new_matrix44f(t_vector4d a, t_vector4d b, t_vector4d c,
				t_vector4d d);
t_matrix44f	matrix_mult(t_matrix44f a, t_matrix44f b);

/*
**	vector.c
*/
float		vector_dot(t_vector a, t_vector b);
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_normalize(t_vector a);
t_vector	vector_subtract(t_vector a, t_vector b);
float		vector_length(t_vector a);

/*
**	vector_2.c
*/
t_vector	vector_mult(t_vector v, float mult);
t_vector	vector_crossproduct(t_vector a, t_vector b);

/*
**	vector2d.c
*/
float		vector2d_dot(t_vector2d a, t_vector2d b);
t_vector2d	vector2d_add(t_vector2d a, t_vector2d b);
t_vector2d	vector2d_normalize(t_vector2d a);
t_vector2d	vector2d_subtract(t_vector2d a, t_vector2d b);
float		vector2d_length(t_vector2d a);


/*
**	vector4d.c
*/
float		vector4d_dot(t_vector4d a, t_vector4d b);
t_vector4d	vector4d_add(t_vector4d a, t_vector4d b);
t_vector4d	vector4d_normalize(t_vector4d a);
t_vector4d	vector4d_subtract(t_vector4d a, t_vector4d b);
float		vector4d_length(t_vector4d a);

/*
**	vector_init.c
*/
t_vector	new_vector(float x, float y, float z);
t_vector2d	new_vector2d(float x, float y);
t_vector4d	new_vector4d(float x, float y, float z, float w);

/*
**	rotations.c
*/
t_vector	rotate_y(t_vector r, float v);
t_vector	rotation(t_vector src, t_vector2d f);
t_vector	get_ray_direction_from_coordinate(t_vector2d coordinates,
				t_cam *cam, unsigned int wid, unsigned int height);

/*
**	coordinates_utils.c
*/
t_vector2d	get_pixel_coordinates(unsigned int i, unsigned int width);

/*
**	aabb_algo.c
*/
int			aabb(SDL_Rect r, t_vector2d pixel_location);

/*
********************************************************************************
**	Interfaces directory
********************************************************************************
*/

/*
**	viewmode_button_clicked.c
*/
int		set_lit_viewmode(t_info *info);
int		set_unlit_viewmode(t_info *info);
int		set_iteration_viewmode(t_info *info);
int		set_normalmap_viewmode(t_info *info);

#endif
