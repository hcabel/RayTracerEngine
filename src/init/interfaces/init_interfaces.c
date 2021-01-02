/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interfaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:52:31 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/01 20:59:51 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	init_viewport(t_viewport_panel *panel)
{
	panel->area.x = LEFT_PANEL_SIZE;
	panel->area.y = TOP_PANEL_SIZE;
	panel->area.w = WIN_WIDTH - LEFT_PANEL_SIZE;
	panel->area.h = WIN_HEIGTH - TOP_PANEL_SIZE;
	panel->resolution = 32;
	panel->sampling.kill_thread = 0;
	panel->sampling.threads_status = (1 << RAYMARCHING_THREAD) - 1;
	panel->sampling.threads_end_status = (1 << RAYMARCHING_THREAD) - 1;
	panel->image.x = panel->area.x;
	panel->image.y = panel->area.y;
	return (GOOD);
}

int			init_interfaces(t_info *info)
{
	int	code;

	ft_printf("{g}	Interfaces\n{/}");

	if ((code = init_top_panel(&info->screen.top, info->ongpu)) != GOOD)
		return (code);
	if ((code = init_left_panel(&info->screen.left)) != GOOD)
		return (code);
	if ((code = init_viewport(&info->screen.viewport)) != GOOD)
		return (code);
	/*
	if (new_Image(info->renderer, "assets/font.tga", &info->screen.font) != GOOD
		|| load_interface_images(info->renderer, &info->screen) != GOOD)
	{
		ft_printf("{y}		Error font loading\n{/}");
		return (MALLOC_ERROR);
	}
	*/
	ft_printf("{g}	Good\n{/}");
	return (GOOD);
}