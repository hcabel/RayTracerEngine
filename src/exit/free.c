/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:51:15 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/31 13:10:46 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_interface(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < VIEWMODE_BUTTON_AMOUNT)
	{
		if (info->screen.top.viewmode.button_images[i] != NULL)
			SDL_DestroyTexture(info->screen.top.viewmode.button_images[i]);
		ft_memdel((void**)&info->screen.top.viewmode.viewmode_list[i]);
		i++;
	}
	ft_memdel((void**)&info->screen.top.viewmode.button_images);
	ft_memdel((void**)&info->screen.top.viewmode.viewmode_list);

}

void	free_info_struct(t_info *info)
{
	if (info->scene.shapes_amount > 0)
		ft_memdel((void**)&info->scene.shapes);
	if (info->scene.light_amount > 0)
		ft_memdel((void**)&info->scene.lights);
	//free_interface(info);
	if (info->screen.tex)
		SDL_DestroyTexture(info->screen.tex);
	if (info->screen.viewport.tex)
		SDL_DestroyTexture(info->screen.viewport.tex);
	if (info->screen.font)
		SDL_DestroyTexture(info->screen.font);
}
