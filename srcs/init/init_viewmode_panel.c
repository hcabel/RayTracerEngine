/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_viewmode_panel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:12:16 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 13:20:50 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_scrollbar(t_buttons_scrollbox *viewmode)
{
	unsigned int	button_size;
	unsigned int	displayable_button_amount;

	button_size = VIEWMODE_AREA_SIZE - VIEWMODE_BUTTONS_MARGIN * 2 -
		SCROLLBAR_SIZE;
	displayable_button_amount = viewmode->scrollbar_area.w /
		(button_size + VIEWMODE_BUTTONS_MARGIN);
	viewmode->scrollbar_button.area.w = viewmode->scrollbar_area.w -
		(VIEWMODE_SCROLLBOX_BUTTON_AMOUNT - displayable_button_amount)
		* (viewmode->scrollbar_area.w / VIEWMODE_SCROLLBOX_BUTTON_AMOUNT);
	viewmode->scrollbar_button.area.h = SCROLLBAR_SIZE;
	viewmode->scrollbar_button.area.x = 0;
	viewmode->scrollbar_button.area.y = VIEWMODE_AREA_SIZE
		- SCROLLBAR_SIZE;
	viewmode->scrollbar_button.color =
		VIEWMODE_SCROLLBAR_BUTTON_COLOR;
}

int			init_viewmode_panel(t_viewmode_panel *viewmode)
{
	int	error_code;

	if ((error_code = malloc_scrollbox(&viewmode->scrollbox,
		VIEWMODE_SCROLLBOX_BUTTON_AMOUNT)) != GOOD)
		return (error_code);
	viewmode->scrollbox.amount = VIEWMODE_SCROLLBOX_BUTTON_AMOUNT;
	viewmode->scrollbox.area.h = VIEWMODE_AREA_SIZE;
	viewmode->scrollbox.area.w = WIN_WIDTH - DETAILS_AREA_SIZE;
	viewmode->scrollbox.area.x = 0;
	viewmode->scrollbox.area.y = 0;
	viewmode->scrollbox.color = VIEWMODE_BACKGROUND_COLOR;
	viewmode->scrollbox.scrollbar_area.x = 0;
	viewmode->scrollbox.scrollbar_area.y = VIEWMODE_AREA_SIZE - SCROLLBAR_SIZE;
	viewmode->scrollbox.scrollbar_area.h = SCROLLBAR_SIZE;
	viewmode->scrollbox.scrollbar_area.w = WIN_WIDTH - DETAILS_AREA_SIZE;
	viewmode->scrollbox.scrollbar_color = VIEWMODE_SCROLLBAR_COLOR;
	init_scrollbar(&viewmode->scrollbox);
	if ((error_code = viewmode_init_buttons(&viewmode->scrollbox)) != GOOD)
		return (error_code);
	return (GOOD);
}
