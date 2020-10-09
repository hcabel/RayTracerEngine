/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interfaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:06:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 13:12:42 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_interfaces_areas(t_screen *screen)
{
	screen->viewport.area.x = DETAILS_AREA_SIZE;
	screen->viewport.area.y = VIEWMODE_AREA_SIZE;
	screen->viewport.area.w = WIN_WIDTH - screen->viewport.area.x;
	screen->viewport.area.h = WIN_HEIGTH - screen->viewport.area.y;
	screen->viewport.image.x = screen->viewport.area.x;
	screen->viewport.image.y = screen->viewport.area.y;
	screen->details.area.x = 0;
	screen->details.area.y = 0;
	screen->details.area.w = DETAILS_AREA_SIZE;
	screen->details.area.h = WIN_HEIGTH;
	screen->viewmode.area.x = DETAILS_AREA_SIZE;
	screen->viewmode.area.y = 0;
	screen->viewmode.area.w = WIN_WIDTH - DETAILS_AREA_SIZE;
	screen->viewmode.area.h = VIEWMODE_AREA_SIZE;
}

int			init_interfaces(t_screen *screen)
{
	int	code_error;

	set_interfaces_areas(screen);
	if ((code_error = init_viewmode_panel(&screen->viewmode)) != GOOD)
		return (code_error);
	if ((code_error = init_details_panel(&screen->details)) != GOOD)
		return (code_error);
	return (GOOD);
}

int			malloc_scrollbox(t_buttons_scrollbox *sb, unsigned int amount)
{
	unsigned int	i;

	sb->amount = amount;
	sb->current = 0;
	if ((sb->list = (t_button*)malloc(sizeof(t_button) * (amount + 1))) == NULL)
		return (MALLOC_ERROR);
	ft_bzero(sb->list, sizeof(t_button) * (amount + 1));
	return (GOOD);
}
