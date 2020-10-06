/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:30:45 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/06 16:41:51 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		loop(t_info *info)
{
	t_bool	quit;
	Uint32	tick;

	if (RAYMARCHING_THREAD <= 0)
		return (O_THREAD_ERROR);
	quit.bool = 0;
	while (quit.bool == 0)
	{
		tick = SDL_GetTicks();
		hook_event(&quit, info);
		draw_calls_execution(info);
		SDL_Delay((1000 / (float)60) - (tick - SDL_GetTicks()));
	}
	return (GOOD);
}
