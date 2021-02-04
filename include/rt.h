/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:45:47 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 11:31:00 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
**	Lib includes
*/
# include <CL/cl.h>
# include <pthread.h>
# include <stdlib.h>
# include "SDL.h"
# include "ft_printf.h"

/*
**	Personal includes
*/
# include "define.h"
# include "tga.h"
# include "kernel.h"
# include "interfaces.h"
# include "mathematical.h"
# include "scene.h"
# include "types.h"

/*
********************************************************************************
**	src
********************************************************************************
*/

void			set_multiple_drawcall_from_code(int code, t_info *info);
int				drawcall_execution(t_info *info);
void			drawcall_clear(t_info *info);
void			drawcall_add(t_info *info, int (*new)(t_info *info));

char			*error_to_str(int code);
int				is_fatal_error(int code);

void			kill_all_thread(t_sampling *sampling);
int				all_threads_are_done(t_sampling *sampling);
void			*thread_calculs_functions(void *p);

int				calculate_image_with_cg(t_info *info);
int				convert_scene_to_kernel_scene(t_kernel_args *kernel_args,
					t_info *info);

/*
********************************************************************************
**	src/sdf
********************************************************************************
*/

float			sdf_primary_cube(t_vector p, t_vector obj_scale);
float			sdf_primary_plane(t_vector p, t_vector obj_scale);
float			sdf_primary_cylinder(t_vector p, t_vector obj_scale);
float			sdf_primary_sphere(t_vector p, t_vector obj_scale);
float			sdf_primary_cone(t_vector p, t_vector obj_scale);

/*
********************************************************************************
**	src/init
********************************************************************************
*/
int				init(t_info *info, char *argv);

/*
********************************************************************************
**	src/init/parsing
********************************************************************************
*/

int				parsing(t_scene *scene, char *path);

int				parsing_header(t_scene *scene, int fd);

int				parse_components(t_scene *scene, int fd);

/*
********************************************************************************
**	src/init/parsing/components
********************************************************************************
*/

void			parse_camera_parameters(t_cam *cam, const char *line,
					const unsigned int line_amount);

void			parse_lights_parameters(t_light *light, const char *line,
					const unsigned int line_amount);

void			parse_objects_parameters(t_object *object, const char *line,
					const unsigned int line_amount);

/*
********************************************************************************
**	src/init/parsing/structures
********************************************************************************
*/

t_vector2d		parse_vector2d(const char *line,
					const unsigned int line_amount);
t_vector		parse_vector(const char *line, const unsigned int line_amount);

t_vector		parse_color(const char *line, const unsigned int line_amount);

/*
********************************************************************************
**	src/init/kernel
********************************************************************************
*/

int				init_kernel(t_info *info);

/*
********************************************************************************
**	src/init/interfaces
********************************************************************************
*/

int				init_interfaces(t_info *info);

int				init_top_panel_images(SDL_Renderer *renderer,
					t_top_panel *panel);
int				init_top_panel(SDL_Renderer *renderer, t_top_panel *panel,
					int ongpu);
int				init_viewmode_scrollbox(t_top_panel *panel);

int				init_left_panel(t_left_panel *panel);

/*
********************************************************************************
**	src/new/scene
********************************************************************************
*/

t_cam			new_cam(void);
t_light			new_light(void);
t_object		new_object(void);

/*
********************************************************************************
**	src/new/math
********************************************************************************
*/

t_vector		new_vector(float x, float y, float z);
t_vector		new_vector_uniform(float x);
t_vector2d		new_vector2d(float x, float y);
t_vector4d		new_vector4d(float x, float y, float z, float w);

/*
********************************************************************************
**	src/math
********************************************************************************
*/

t_vector		vector_crossproduct(t_vector a, t_vector b);
t_vector		vector_mult(t_vector v, float mult);

float			vector_length(t_vector a);
t_vector		vector_subtract(t_vector a, t_vector b);
t_vector		vector_normalize(t_vector a);
t_vector		vector_add(t_vector a, t_vector b);
float			vector_dot(t_vector a, t_vector b);

float			vector2d_length(t_vector2d a);
t_vector2d		vector2d_subtract(t_vector2d a, t_vector2d b);
t_vector2d		vector2d_normalize(t_vector2d a);
t_vector2d		vector2d_add(t_vector2d a, t_vector2d b);
float			vector2d_dot(t_vector2d a, t_vector2d b);

float			vector4d_length(t_vector4d a);
t_vector4d		vector4d_subtract(t_vector4d a, t_vector4d b);
t_vector4d		vector4d_normalize(t_vector4d a);
t_vector4d		vector4d_add(t_vector4d a, t_vector4d b);
float			vector4d_dot(t_vector4d a, t_vector4d b);

t_vector		get_ray_direction(t_vector2d coordinates, t_vector2d rot,
					float angle, SDL_Rect area);
t_vector		rotation(t_vector src, t_vector2d f);
t_vector		rotate_y(t_vector r, float v);

int				aabb(SDL_Rect r, t_vector2d pixel_location);

t_vector2d		get_pixel_coordinates(unsigned int i, unsigned int width);

/*
********************************************************************************
**	src/tga
********************************************************************************
*/

int				uncompress_tga(t_tga *file);
int				convert_to_argb(t_tga *file);
void			fill_uncompresed_data(t_vector2d index, unsigned char *original,
					unsigned char *new_data, int bpp);
int				setup_contents(t_tga *file, int fd);
int				read_header(t_tga *file, int fd);
int				new_tga_image(SDL_Renderer *renderer, char *path,
					SDL_Texture **texture);
t_tga			new_tga(char *path);

/*
********************************************************************************
**	src/drawcall
********************************************************************************
*/

int				drawcall_viewport(t_info *info);
int				drawcall_check_viewport(t_info *info);

int				drawcall_top_panel(t_info *info);
int				display_viewmode_images(SDL_Renderer *renderer,
					t_top_panel *panel);

int				drawcall_left_panel(t_info *info);

/*
********************************************************************************
**	src/input
********************************************************************************
*/

int				hook_event(int *quit, t_info *info);

void			keyboard_press(int *quit, t_info *info, SDL_Event *event);

/*
********************************************************************************
**	src/input/mouse
********************************************************************************
*/

void			mouse_wheel(t_info *info, SDL_Event *event);

/*
********************************************************************************
**	src/input/mouse/press
********************************************************************************
*/

int				mouse_press(t_info *info);
int				press_on_top_panel(t_vector2d loc, t_info *info);
int				press_on_left_panel(t_vector2d loc, t_info *info);

/*
********************************************************************************
**	src/input/mouse/move
********************************************************************************
*/

void			mouse_move(t_info *info, SDL_Event *event);
int				move_on_top_panel(t_top_panel *viewmode,
					t_vector2d cursorlocation);
int				move_on_left_panel(t_vector2d loc, t_left_panel *panel);

/*
********************************************************************************
**	src/input/resize
********************************************************************************
*/

int				resize_window(t_info *info);
void			resize_top_panel(t_vector2d window_size, t_top_panel *panel);

/*
********************************************************************************
**	src/clicked/top_panel
********************************************************************************
*/

int				game_viewmode_button_clicked(t_info *info);
int				editor_viewmode_button_clicked(t_info *info);
int				unlit_viewmode_button_clicked(t_info *info);
int				iteration_viewmode_button_clicked(t_info *info);
int				normal_viewmode_button_clicked(t_info *info);

int				distance_fog_viewmode_button_clicked(t_info *info);
int				direct_illumination_viewmode_button_clicked(t_info *info);
int				global_illumination_viewmode_button_clicked(t_info *info);
int				glossy_illumination_viewmode_button_clicked(t_info *info);

int				gpu_switch_clicked(t_info *info, t_switch *button);

/*
********************************************************************************
**	src/raymarching
********************************************************************************
*/

float			phong_lighting(t_scene *scene, t_vector oldir,
					t_ray_hit *ray, int index);
unsigned int	raymarching(t_scene *scene, t_vector dir);
t_ray_hit		trace_ray(t_scene *scene, t_vector start_location, t_vector dir,
					float max_distance);
t_vector		normal_map_to_rgb(t_vector normal);
t_vector		get_normal_map(t_vector p, t_scene *scene);

/*
********************************************************************************
**	src/exit
********************************************************************************
*/

int				program_exit(t_info *info, int code);

void			free_info_struct(t_info *info);

#endif
