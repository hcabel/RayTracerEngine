/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:27:09 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/31 19:07:32 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	drawcall_execution(t_info *info)
{
	int	(*current)(t_info *info);
	int	i;
	int	code;

	i = 0;
	while (i < MAX_DRAWCALL)
	{
		if (info->drawcall_list[i] != NULL)
		{
			current = info->drawcall_list[i];
			info->drawcall_list[i] = NULL;
			if ((code = current(info)) != GOOD)
				return (code);
		}
		i++;
	}
}

void		drawcall_clear(t_info *info)
{
	int	i;

	i = 0;
	while (i < MAX_DRAWCALL)
	{
		info->drawcall_list[i] = NULL;
		i++;
	}
}

void		drawcall_add(t_info *info, int (*new)(t_info *info))
{
	if (new == DRAWCALL_CHECK_VIEWPORT)
		info->drawcall_list[0] = new;
	else if (new == DRAWCALL_VIEWPORT)
		info->drawcall_list[1] = new;
	else if (new == DRAWCALL_LEFT_PANEL)
		info->drawcall_list[2] = new;
	else if (new == DRAWCALL_TOP_PANEL)
		info->drawcall_list[3] = new;
}

static int	loop(t_info *info)
{
	int		quit;
	int		code;
	Uint32	tick;

	if (RAYMARCHING_THREAD <= 0)
		return (O_THREAD_ERROR);
	quit = 0;
	while (quit == 0)
	{
		tick = SDL_GetTicks();
		if ((code = drawcall_execution(info)) != GOOD)
		{
			if (is_fatal_error(code) == GOOD)
				return (code);
			ft_printf("{y}DrawCall Warning : %s\n{/}", error_to_str(code));
		}
		if ((code = hook_event(&quit, info)) != GOOD)
		{
			if (is_fatal_error(code) == GOOD)
				return (code);
			ft_printf("{y}Event Warning : %s\n{/}", error_to_str(code));
		}
		SDL_Delay(fmaxf(0, (1000 / 120) - (SDL_GetTicks() - tick)));
	}
	return (GOOD);
}

int			main(int argc, char **argv)
{
	t_info	info;
	int		code_error;

	(void)argc;
	if ((code_error = init(&info, argv[1])) != GOOD)
		return (program_exit(&info, code_error));
	if ((code_error = loop(&info)) != GOOD)
		return (program_exit(&info, code_error));
	return (program_exit(&info, GOOD));
}