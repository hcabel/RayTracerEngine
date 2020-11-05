/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:51:15 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/05 12:20:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_interface(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < VIEWMODE_SCROLLBOX_BUTTON_AMOUNT)
	{
		if (info->screen.viewmode.images[i] != NULL)
			SDL_DestroyTexture(info->screen.viewmode.images[i]);
		i++;
	}
	ft_memdel((void**)&info->screen.viewmode.scrollbox.list);
}

void	free_info_struct(t_info *info)
{
	if (info->scene.shapes_amount > 0)
		ft_memdel((void**)&info->scene.shapes);
	if (info->scene.light_amount > 0)
		ft_memdel((void**)&info->scene.lights);
	free_interface(info);
	SDL_DestroyTexture(info->screen.tex);
	SDL_DestroyTexture(info->screen.viewport.tex);
	SDL_DestroyTexture(info->screen.font);
}
