/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_details_panel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:12:16 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 13:19:32 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_scrollbar(t_buttons_scrollbox *details)
{
	unsigned int	button_size;
	unsigned int	displayable_button_amount;

	button_size = DETAILS_AREA_SIZE - DETAILS_BUTTONS_MARGIN * 2 -
		SCROLLBAR_SIZE;
	displayable_button_amount = details->scrollbar_area.h /
		(button_size + DETAILS_BUTTONS_MARGIN);
	details->scrollbar_button.area.w = details->scrollbar_area.h -
		(DETAILS_SCROLLBOX_BUTTON_AMOUNT - displayable_button_amount)
		* (details->scrollbar_area.h / DETAILS_SCROLLBOX_BUTTON_AMOUNT);
	details->scrollbar_button.area.h = SCROLLBAR_SIZE;
	details->scrollbar_button.area.x = 0;
	details->scrollbar_button.area.y = DETAILS_AREA_SIZE
		- SCROLLBAR_SIZE;
	details->scrollbar_button.color =
		DETAILS_SCROLLBAR_BUTTON_COLOR;
}

int			init_details_panel(t_details_panel *scrollbox)
{
	/*int	error_code;

	if ((error_code = malloc_scrollbox(details,
		DETAILS_SCROLLBOX_BUTTON_AMOUNT)) != GOOD)
		return (error_code);
	details->amount = DETAILS_SCROLLBOX_BUTTON_AMOUNT;
	details->area.h = WIN_HEIGTH;
	details->area.w = DETAILS_AREA_SIZE;
	details->area.x = 0;
	details->area.y = 0;
	details->color = DETAILS_BACKGROUND_COLOR;
	details->scrollbar_area.x = DETAILS_AREA_SIZE - SCROLLBAR_SIZE;
	details->scrollbar_area.y = 0;
	details->scrollbar_area.h = WIN_HEIGTH;
	details->scrollbar_area.w = SCROLLBAR_SIZE;
	details->scrollbar_color = DETAILS_SCROLLBAR_COLOR;
	init_scrollbar(details);;*/
	return (GOOD);
}
