/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 11:21:11 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	mouse_move(t_info *info, SDL_Event *event)
{
	int	result;

	result = 0;
	info->mouse.location.x = event->motion.x;
	info->mouse.location.y = event->motion.y;
	if (aabb(info->screen.top.area, info->mouse.location) == GOOD)
		result |= move_on_top_panel(&info->screen.top, info->mouse.location);
	set_multiple_drawcall_from_code(result, info);
}
