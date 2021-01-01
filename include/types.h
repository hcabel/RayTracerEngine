/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:46:53 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/31 18:28:02 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "interfaces.h"
# include "define.h"
# include "tga.h"
# include "scene.h"

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
	long long			threads_end_status;
	int					kill_thread;
}						t_sampling;

typedef struct			s_viewport_panel
{
	SDL_Rect			area;
	SDL_Rect			image;
	SDL_Texture			*tex;
	int					pitch;
	void				*pixels;
	unsigned int		resolution;
	t_sampling			sampling;
}						t_viewport_panel;

typedef struct			s_screen
{
	SDL_Texture			*tex;
	int					pitch;
	t_viewport_panel	viewport;
	t_left_panel		left;
	t_top_panel			top;
	SDL_Texture			*font;
}						t_screen;

typedef struct			s_mouse
{
	int					dragged;
	int					down;
	t_vector2d			startloc;
	t_vector			target_base_3dvector;
	t_vector2d			location;
}						t_mouse;

typedef struct			s_info
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	int					(*drawcall_list[MAX_DRAWCALL])(t_info *info);
	t_screen			screen;
	t_scene				scene;
	t_mouse				mouse;
	pthread_t			hook;
	t_kernel_gpu		kernel;
	int					ongpu;
	int					gpuinitialised;
}						t_info;

typedef struct			s_parsing
{
	unsigned int		line_amount;
	unsigned int		shapes_index;
	unsigned int		light_index;
}						t_parsing;

typedef struct			s_ray_hit
{
	int					hit;
	t_vector			location;
	t_object			*hit_object;
	float				distance;
	unsigned int		recursion;
}						t_ray_hit;

#endif
