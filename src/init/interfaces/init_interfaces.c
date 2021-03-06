/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interfaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:52:31 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/29 14:46:30 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	init_viewport(t_viewport_panel *panel)
{
	panel->area.x = LEFT_PANEL_SIZE;
	panel->area.y = TOP_PANEL_SIZE;
	panel->area.w = WIN_WIDTH - LEFT_PANEL_SIZE;
	panel->area.h = WIN_HEIGTH - TOP_PANEL_SIZE;
	panel->resolution = FIRST_RESOLUTION;
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
	info->screen.area.x = 0;
	info->screen.area.y = 0;
	info->screen.area.w = WIN_WIDTH;
	info->screen.area.h = WIN_HEIGTH;
	if ((code = init_top_panel(info->renderer, &info->screen.top,
		info->ongpu)) != GOOD)
		return (code);
	if ((code = init_left_panel(&info->screen.left)) != GOOD)
		return (code);
	if ((code = init_viewport(&info->screen.viewport)) != GOOD)
		return (code);
	ft_printf("{g}	Good\n{/}");
	return (GOOD);
}
