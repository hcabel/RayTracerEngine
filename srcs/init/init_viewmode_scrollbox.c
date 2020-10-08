/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_viewmode_scrollbox.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:12:16 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/08 17:01:58 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int malloc_scrollbox(t_scrollbox *sb, unsigned int amount)
{
	unsigned int	i;

	sb->amount = amount;
	sb->current = 0;
	if ((sb->list = (t_button*)malloc(sizeof(t_button) * (amount + 1))) == NULL)
		return (MALLOC_ERROR);
	ft_bzero(sb->list, sizeof(t_button) * (amount + 1));
	return (GOOD);
}

static void	init_scrollbar(t_scrollbox *scrollbox)
{
	unsigned int	button_size;
	unsigned int	displayable_button_amount;

	button_size = VIEWMODE_AREA_SIZE - VIEWMODE_BUTTONS_MARGIN * 2 -
		SCROLLBAR_SIZE;
	displayable_button_amount = scrollbox->scrollbar_area.w /
		(button_size + VIEWMODE_BUTTONS_MARGIN);
	scrollbox->scrollbar_button.area.w = scrollbox->scrollbar_area.w -
		(SCROLLBOX_VIEWMODE_BUTTON_AMOUNT - displayable_button_amount)
		* (scrollbox->scrollbar_area.w / SCROLLBOX_VIEWMODE_BUTTON_AMOUNT);
	scrollbox->scrollbar_button.area.h = SCROLLBAR_SIZE;
	scrollbox->scrollbar_button.area.x = 0;
	scrollbox->scrollbar_button.area.y = VIEWMODE_AREA_SIZE
		- SCROLLBAR_SIZE;
	scrollbox->scrollbar_button.color =
		VIEWMODE_SCROLLBAR_BUTTON_COLOR;
}

static void	set_buttons_action_functions(t_button *list)
{
	list[0].clicked = set_lit_viewmode;
	list[1].clicked = set_unlit_viewmode;
	list[2].clicked = set_normalmap_viewmode;
	list[3].clicked = set_iteration_viewmode;
}

int			init_viewmode_scrollboxs(t_scrollbox *scrollbox)
{
	int	error_code;

	if ((error_code = malloc_scrollbox(scrollbox,
		SCROLLBOX_VIEWMODE_BUTTON_AMOUNT)) != GOOD)
		return (error_code);
	scrollbox->amount = SCROLLBOX_VIEWMODE_BUTTON_AMOUNT;
	scrollbox->area.h = VIEWMODE_AREA_SIZE;
	scrollbox->area.w = WIN_WIDTH - DETAILS_AREA_SIZE;
	scrollbox->area.x = 0;
	scrollbox->area.y = 0;
	scrollbox->color = VIEWMODE_BACKGROUND_COLOR;
	scrollbox->scrollbar_area.x = 0;
	scrollbox->scrollbar_area.y = VIEWMODE_AREA_SIZE - SCROLLBAR_SIZE;
	scrollbox->scrollbar_area.h = SCROLLBAR_SIZE;
	scrollbox->scrollbar_area.w = WIN_WIDTH - DETAILS_AREA_SIZE;
	scrollbox->scrollbar_color = VIEWMODE_SCROLLBAR_COLOR;
	init_scrollbar(scrollbox);
	set_buttons_action_functions(scrollbox->list);
	return (GOOD);
}
