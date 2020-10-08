/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interfaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:06:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/08 17:01:02 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_interfaces_areas(t_screen *screen)
{
	screen->viewport_area.x = DETAILS_AREA_SIZE;
	screen->viewport_area.y = VIEWMODE_AREA_SIZE;
	screen->viewport_area.w = WIN_WIDTH - screen->viewport_area.x;
	screen->viewport_area.h = WIN_HEIGTH - screen->viewport_area.y;
	screen->viewport_image.x = screen->viewport_area.x;
	screen->viewport_image.y = screen->viewport_area.y;
	screen->details_area.x = 0;
	screen->details_area.y = 0;
	screen->details_area.w = DETAILS_AREA_SIZE;
	screen->details_area.h = WIN_HEIGTH;
	screen->viewmode_area.x = DETAILS_AREA_SIZE;
	screen->viewmode_area.y = 0;
	screen->viewmode_area.w = WIN_WIDTH - DETAILS_AREA_SIZE;
	screen->viewmode_area.h = VIEWMODE_AREA_SIZE;
}

int			init_interfaces(t_screen *screen)
{
	int	code_error;

	set_interfaces_areas(screen);
	if ((code_error = init_viewmode_scrollboxs(&screen->viewmode_content)) != GOOD)
		return (code_error);
	if ((code_error = viewmode_init_buttons(&screen->viewmode_content)) != GOOD)
		return (code_error);
	return (GOOD);
}
