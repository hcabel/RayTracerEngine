/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:46:53 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 10:38:44 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "interfaces.h"

/*
**	Modifyable define
*/
# define WINDOW_NAME "RayTracer Engine"
# define WIN_HEIGTH 800
# define WIN_WIDTH 1180

# define RAY_LOOP 100
# define CPU_THREAD 20
# define FIRST_RESOLUTION 24
# define VIEW_DISTANCE 200
# define RAY_PRECIS 0.0005

# define DETAILS_AREA_SIZE 200
# define VIEWMODE_AREA_SIZE 50

/*
**	Code understanding define
*/
# define MAX_DRAWCALL 5
# define RAYMARCHING_THREAD (CPU_THREAD - 1)

# define FAILED -1
# define GOOD 0
# define UNKNOWN_ERROR 1
# define MALLOC_ERROR 2
# define SDL_ERROR 3
# define O_THREAD_ERROR 4

# define DRAWCALL_CHECK_VIEWPORT check_viewport_render
# define DRAWCALL_VIEWPORT new_viewport_frame
# define DRAWCALL_DETAILS_PANEL new_details_panel_frame
# define DRAWCALL_VIEWMODE_PANEL new_viewmode_panel_frame

typedef struct			s_bool
{
	unsigned			bool:1;
}						t_bool;

typedef struct			s_object
{
	t_vector			location;
	t_vector2d			rotation;
	t_vector			scale;
	t_vector			color;
	float				(*sdf)(t_vector, t_vector);
}						t_object;

typedef struct			s_light
{
	t_vector			location;
	t_vector2d			rotation;
	float				intensity;
}						t_light;

typedef struct			s_cam
{
	t_vector			location;
	t_vector2d			rotation;
	t_vector			forward;
	unsigned int		viewmode;
}						t_cam;

typedef struct			s_scene
{
	t_object			*shapes;
	t_light				*lights;
	t_cam				cam;
	unsigned int		shapes_amount;
	unsigned int		light_amount;
}						t_scene;

typedef struct			s_screen
{
	SDL_Texture			*tex;
	void				*pixels;
	int					pitch;
	SDL_Rect			viewport_area;
	SDL_Rect			viewport_image;
	SDL_Rect			details_area;
	SDL_Rect			viewmode_area;
	t_scrollbox			viewmode_content;
	unsigned int		resolution;
}						t_screen;

typedef struct			s_thread
{
	unsigned int		start_index;
	t_info				*info;
}						t_thread;

typedef struct			s_sampling
{
	pthread_t			threads[RAYMARCHING_THREAD];
	t_thread			threads_infos[RAYMARCHING_THREAD];
	pthread_mutex_t		mutex;
	long long			threads_status;
}						t_sampling;

typedef struct			s_info
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	void				(*update_function_list[MAX_DRAWCALL])
							(t_info *info);
	t_screen			screen;
	t_scene				scene;
	pthread_t			hook;
	t_sampling			sampling;
}						t_info;

typedef struct			s_parsing
{
	unsigned int		line_amount;
	unsigned int		shapes_index;
	unsigned int		light_index;
}						t_parsing;

typedef struct			s_ray_hit
{
	t_bool				hit;
	t_vector			location;
	t_object			*hit_object;
	float				distance;
	unsigned int		recursion;
}						t_ray_hit;

#endif
