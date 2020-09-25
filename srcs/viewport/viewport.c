/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:12:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/25 12:46:26 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	new_viewport_frame_render(t_info *info)
{
	int	i;

	ft_printf("[DrawCall] Viewport\n");
	SDL_RenderClear(info->renderer);
	SDL_SetRenderDrawColor(info->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	i = 0;
	while (++i < 100)
	{
		if (i == 50)
			SDL_SetRenderDrawColor(info->renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawPoint(info->renderer, i, i);
	}
	SDL_SetRenderDrawColor(info->renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderPresent(info->renderer);
}
