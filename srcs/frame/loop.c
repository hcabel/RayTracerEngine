/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:30:45 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 14:49:02 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		loop(t_info *info)
{
	t_bool	quit;
	Uint32	tick;

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
