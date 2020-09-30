/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:52:54 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/30 13:55:16 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	new_hud_frame_render(t_info *info)
{
	int	i;

	ft_printf("[DrawCall] Hud...	");
	SDL_LockTexture(info->screen.tex, &info->screen.hud, &info->screen.pixels,
		&info->screen.pitch);
	i = 0;
	while (i < info->screen.hud.w * info->screen.hud.h)
	{
		((unsigned int*)info->screen.pixels)[i % info->screen.hud.w + (i / info->screen.hud.w * WIN_WIDTH)] = 0x333333FF;
		i++;
	}
	SDL_UnlockTexture(info->screen.tex);
	SDL_RenderCopy(info->renderer, info->screen.tex, NULL, NULL);
	SDL_RenderPresent(info->renderer);
	ft_printf("End\n");
}
