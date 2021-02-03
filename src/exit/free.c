/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:51:15 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 15:30:18 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_scene(t_info *info)
{
	printf("Free scene\n");
	if (info->scene.shapes_amount > 0)
		ft_memdel((void**)&info->scene.shapes);
	if (info->scene.light_amount > 0)
		ft_memdel((void**)&info->scene.lights);
}

static void	free_interface(t_info *info)
{
	unsigned int	i;

	printf("Free interface\n");
	i = 0;
	while (i < TOP_PANEL_ICON_AMOUNT)
	{
		if (info->screen.top.icon[i] != NULL)
			SDL_DestroyTexture(info->screen.top.icon[i]);
		i++;
	}
	//ft_memdel((void**)&info->screen.top.viewmode.viewmode_list);
}

void		free_info_struct(t_info *info)
{
	printf("Free info struct\n");
	free_scene(info);
	free_interface(info);
	printf("Free texture\n");
	if (info->screen.tex)
		SDL_DestroyTexture(info->screen.tex);
	if (info->screen.viewport.tex)
		SDL_DestroyTexture(info->screen.viewport.tex);
	if (info->screen.font)
		SDL_DestroyTexture(info->screen.font);
}
