/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:19:37 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 12:21:20 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	init_sdl(t_info *info)
{
	ft_printf("{g}	SDL{y}\n");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != GOOD)
		return (FAILED);
	ft_printf("{g}		Create window{y}\n");
	if (!(info->window = SDL_CreateWindow(WINDOW_NAME, 0, 0, WIN_WIDTH,
		WIN_HEIGTH, SDL_WINDOW_RESIZABLE)))
		return (FAILED);
	if (!(info->renderer = SDL_CreateRenderer(info->window,
		-1, SDL_RENDERER_ACCELERATED)))
		return (FAILED);
	ft_printf("{g}		Create textures{y}\n");
	if (!(info->screen.tex = SDL_CreateTexture(info->renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		WIN_WIDTH, WIN_HEIGTH)))
		return (SDL_TEXTURE_CREATION_ERROR);
	if (!(info->screen.viewport.tex = SDL_CreateTexture(info->renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		WIN_WIDTH, WIN_HEIGTH)))
		return (SDL_TEXTURE_CREATION_ERROR);
	ft_printf("{g}	Good{y}\n");
	return (GOOD);
}

static void	init_scene(t_info *info)
{
	info->scene.light_amount = 0;
	info->scene.shapes_amount = 0;
	info->scene.cam.viewmode = 0;
	info->scene.target = NULL;
	info->scene.target_type = 0;
	info->screen.viewport.sampling.kill_thread = 0;
	info->scene.transphorm_axis = 0;
	info->scene.transphorm_method = 0;
	info->scene.sdf_list[0] = sdf_primary_sphere;
	info->scene.sdf_list[1] = sdf_primary_cone;
	info->scene.sdf_list[2] = sdf_primary_cube;
	info->scene.sdf_list[3] = sdf_primary_cylinder;
	info->scene.sdf_list[4] = sdf_primary_plane;
}

static void	init_mouse_structure(t_mouse *mouse)
{
	mouse->dragged = 0;
	mouse->down = 0;
	mouse->location = new_vector2d(0, 0);
	mouse->startloc = new_vector2d(0, 0);
	mouse->target_base_3dvector = new_vector(0, 0, 0);
}

static void	init_info_structure(t_info *info)
{
	info->ongpu = ON_GPU;
	drawcall_clear(info);
	drawcall_add(info, DRAWCALL_LEFT_PANEL);
	drawcall_add(info, DRAWCALL_TOP_PANEL);
	drawcall_add(info, DRAWCALL_VIEWPORT);
	pthread_mutex_init(&info->screen.viewport.sampling.mutex, NULL);
	info->gpuinitialised = 0;
	info->screen.viewport.sampling.threads_end_status =
		(1 << RAYMARCHING_THREAD) - 1;
	info->screen.viewport.sampling.threads_status =
		info->screen.viewport.sampling.threads_end_status;
	info->screen.viewport.resolution = 1;
	info->screen.tex = NULL;
	info->screen.viewport.tex = NULL;
	info->screen.font = NULL;
	init_mouse_structure(&info->mouse);
	init_scene(info);
}

int			init(t_info *info, char *argv)
{
	int	code_error;

	ft_printf("{g}Init :\n");
	init_info_structure(info);
	if (info->ongpu == 1 && (code_error = init_kernel(info)) != GOOD)
		return (code_error);
	if ((code_error = init_sdl(info)) != GOOD)
	{
		ft_printf("{r}	%s\n", SDL_GetError());
		return (SDL_ERROR);
	}
	if ((code_error = parsing(&info->scene, argv)) != GOOD)
		return (code_error);
	if ((code_error = init_interfaces(info)) != GOOD)
		return (code_error);
	ft_printf("{g}Good\n{/}");
	return (GOOD);
}
