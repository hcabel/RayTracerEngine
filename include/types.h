/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:46:53 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/30 14:00:47 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/*
**	Modifyable define
*/
# define WINDOW_NAME "RayTracer Engine"
# define WIN_HEIGTH 720
# define WIN_WIDTH 1080

# define RAY_LOOP 500
# define CPU_THREAD 24
# define FIRST_RESOLUTION 32

/*
**	Code understanding define
*/
# define WIN_AREAS 2
# define RAYMARCHING_THREAD (CPU_THREAD - WIN_AREAS - 1)

# define FAILED - 1
# define GOOD 0
# define UNKNOWN_ERROR 1
# define MALLOC_ERROR 2
# define SDL_ERROR 3

# define UPDATE_VIEWPORT viewport_frame_updates
# define UPDATE_HUD new_hud_frame_render

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
	SDL_Rect			hud;
	unsigned int		resolution;
}						t_screen;

typedef struct s_info	t_info;

struct					s_info
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	void				(*update_function_list[WIN_AREAS])
							(t_info *info);
	t_screen			screen;
	t_scene				scene;
	pthread_t			window_area_renderer;
};

typedef struct			s_parsing
{
	unsigned int	line_amount;
	unsigned int	shapes_index;
	unsigned int	light_index;
}						t_parsing;

typedef struct			t_thread
{
	int					start_index;
	t_screen			*screen;
	t_scene				*scene;
}						t_thread;

#endif
