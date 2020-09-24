/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:46:14 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/24 23:07:36 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	loop(t_info *info)
{
	t_bool	quit;
	t_bool	update;

	quit.bool = 0;
	while (quit.bool == 0)
	{
		update.bool = 0;
		hook_event(&quit, &update);
		new_viewport_frame_render(info);
	}
	return (GOOD);
}

static int	init_sdl(t_info *info)
{
	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_TIMER) != GOOD )
		return (SDL_ERROR);
	if (!(info->window = SDL_CreateWindow(WINDOW_NAME,SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGTH, SDL_WINDOW_SHOWN)))
		return (SDL_ERROR);
	if (!(info->renderer = SDL_CreateRenderer(info->window, 0, 0)))
		return (SDL_ERROR);
	return(GOOD);
}

int			main(int argc, char **argv)
{
	t_info	info;
	int		code_error;

	if ((code_error = init_sdl(&info)) != GOOD)
		return (program_exit(&info, code_error));
	if ((code_error = loop(&info)) != GOOD)
		return (program_exit(&info, code_error));
	return (program_exit(&info, GOOD));
}
