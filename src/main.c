/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:27:09 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 15:14:07 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

	if (argc > 2)
		ft_printf("{y}Too many args only the first will be used{/}\n");
	code_error = 0;
	if ((code_error = init(&info, argv[1])) != GOOD)
		return (program_exit(&info, code_error));
	if ((code_error = loop(&info)) != GOOD)
		return (program_exit(&info, code_error));
	return (program_exit(&info, GOOD));
}
