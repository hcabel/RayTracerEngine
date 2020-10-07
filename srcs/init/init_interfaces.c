/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interfaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:06:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/07 17:07:58 by hcabel           ###   ########.fr       */
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

static int	init_viewmode_scrollboxs(t_scrollbox *scrollbox)
{
	int	error_code;

	if ((error_code = malloc_scrollbox(scrollbox,
		SCROLLBOX_VIEWMODE_BUTTON_AMOUNT)) != GOOD)
		return (error_code);
	scrollbox->area.h = VIEWMODE_PANEL_SIZE;
	scrollbox->area.w = WIN_WIDTH - DETAILS_PANEL_SIZE;
	scrollbox->area.x = 0;
	scrollbox->area.y = 0;
	scrollbox->color = VIEWMODE_BACKGROUND_COLOR;
	scrollbox->scrollbar_area.x = 0;
	scrollbox->scrollbar_area.y = VIEWMODE_PANEL_SIZE - SCROLLBAR_SIZE;
	scrollbox->scrollbar_area.h = SCROLLBAR_SIZE;
	scrollbox->scrollbar_area.w = WIN_WIDTH - DETAILS_PANEL_SIZE;
	scrollbox->scrollbar_color = VIEWMODE_SCROLLBAR_COLOR;
	scrollbox->scrollbar_button.area.w = SCROLLBAR_BUTTON_SIZE;
	scrollbox->scrollbar_button.area.h = 10;
	scrollbox->scrollbar_button.area.x = 0;
	scrollbox->scrollbar_button.area.y = VIEWMODE_PANEL_SIZE
		- SCROLLBAR_SIZE;
	scrollbox->scrollbar_button.color =
		VIEWMODE_SCROLLBAR_BUTTON_COLOR;
	return (GOOD);
}

static void	set_interfaces_areas(t_screen *screen)
{
	screen->viewport_area.x = DETAILS_PANEL_SIZE;
	screen->viewport_area.y = VIEWMODE_PANEL_SIZE;
	screen->viewport_area.w = WIN_WIDTH - screen->viewport_area.x;
	screen->viewport_area.h = WIN_HEIGTH - screen->viewport_area.y;
	screen->viewport_image.x = screen->viewport_area.x;
	screen->viewport_image.y = screen->viewport_area.y;
	screen->details_panel.x = 0;
	screen->details_panel.y = 0;
	screen->details_panel.w = DETAILS_PANEL_SIZE;
	screen->details_panel.h = WIN_HEIGTH;
	screen->viewmode_panel.x = DETAILS_PANEL_SIZE;
	screen->viewmode_panel.y = 0;
	screen->viewmode_panel.w = WIN_WIDTH - DETAILS_PANEL_SIZE;
	screen->viewmode_panel.h = VIEWMODE_PANEL_SIZE;
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
