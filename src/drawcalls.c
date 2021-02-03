/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawcalls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:20:32 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 11:50:11 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		drawcall_execution(t_info *info)
{
	int	(*current)(t_info *info);
	int	i;
	int	code;

	i = 0;
	while (i < MAX_DRAWCALL)
	{
		if (info->drawcall_list[i] != NULL)
		{
			current = info->drawcall_list[i];
			info->drawcall_list[i] = NULL;
			if ((code = current(info)) != GOOD)
				return (code);
		}
		i++;
	}
}

void	drawcall_clear(t_info *info)
{
	int	i;

	i = 0;
	while (i < MAX_DRAWCALL)
	{
		info->drawcall_list[i] = NULL;
		i++;
	}
}

void	drawcall_add(t_info *info, int (*new)(t_info *info))
{
	if (new == DRAWCALL_CHECK_VIEWPORT)
		info->drawcall_list[0] = new;
	else if (new == DRAWCALL_VIEWPORT)
		info->drawcall_list[1] = new;
	else if (new == DRAWCALL_LEFT_PANEL)
		info->drawcall_list[2] = new;
	else if (new == DRAWCALL_TOP_PANEL)
		info->drawcall_list[3] = new;
}

void	set_multiple_drawcall_from_code(int code, t_info *info)
{
	if (code > 0)
	{
		if ((code & 1) != 0)
		{
			info->screen.viewport.resolution = FIRST_RESOLUTION;
			drawcall_add(info, DRAWCALL_VIEWPORT);
		}
		if (((code >> 1) & 1) != 0)
			drawcall_add(info, DRAWCALL_TOP_PANEL);
		if (((code >> 2) & 1) != 0)
			drawcall_add(info, DRAWCALL_LEFT_PANEL);
		if (((code >> 3) & 1) != 0)
			drawcall_add(info, DRAWCALL_CHECK_VIEWPORT);
	}
}
