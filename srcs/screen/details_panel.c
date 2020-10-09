/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details_panel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:52:54 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 13:11:04 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	new_details_panel_frame(t_info *info)
{
	int	i;

	ft_printf("[DrawCall] Details panel\n");
	SDL_LockTexture(info->screen.tex, &info->screen.details.area,
		&info->screen.pixels, &info->screen.pitch);
	i = 0;
	while (i < info->screen.details.area.w *
		info->screen.details.area.h)
	{
		((unsigned int*)info->screen.pixels)[i % info->screen.details.area.w +
			(i / info->screen.details.area.w * WIN_WIDTH)] = 0x333333FF;
		i++;
	}
	SDL_UnlockTexture(info->screen.tex);
	SDL_RenderCopy(info->renderer, info->screen.tex, NULL, NULL);
	SDL_RenderPresent(info->renderer);
}
