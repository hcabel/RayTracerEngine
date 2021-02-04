/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:01:24 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 11:19:28 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			drawcall_left_panel(t_info *info)
{
	unsigned int	color;
	unsigned int	i;
	t_vector2d		coord;

	ft_printf("[DrawCall] Left panel\n");
	SDL_LockTexture(info->screen.tex, &info->screen.left.area,
		&info->screen.left.pixels, &info->screen.pitch);
	i = 0;
	while (i < (unsigned int)info->screen.left.area.w
		* (unsigned int)info->screen.left.area.h)
	{
		coord = get_pixel_coordinates(i, info->screen.left.area.w);
		color = LEFT_PANEL_BACKGROUND_COLOR;
		((unsigned int*)info->screen.left.pixels)[(int)coord.y
			* info->screen.top.area.w + (int)coord.x] = color;
		i++;
	}
	SDL_UnlockTexture(info->screen.tex);
	SDL_RenderCopy(info->renderer, info->screen.tex,
		&info->screen.left.area, &info->screen.left.area);
	SDL_RenderPresent(info->renderer);
	return (GOOD);
}
