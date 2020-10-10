/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_viewmode_buttons.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:01:00 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/10 12:24:58 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_buttons_action_functions(t_button *list)
{
	list[0].clicked = set_lit_viewmode;
	list[1].clicked = set_unlit_viewmode;
	list[2].clicked = set_normalmap_viewmode;
	list[3].clicked = set_iteration_viewmode;
}

int		viewmode_init_buttons(t_buttons_scrollbox *viewmode)
{
	unsigned int	i;
	unsigned int	button_size;
	t_vector		color_tmp;

	button_size = VIEWMODE_AREA_SIZE - VIEWMODE_BUTTONS_MARGIN * 2 -
		SCROLLBAR_SIZE;
	i = 0;
	while (i < viewmode->amount)
	{
		viewmode->list[i].area.w = button_size;
		viewmode->list[i].area.h = button_size;
		viewmode->list[i].area.x = i * (button_size + VIEWMODE_BUTTONS_MARGIN)
			+ viewmode->area.x + VIEWMODE_BUTTONS_MARGIN;
		viewmode->list[i].area.y = VIEWMODE_BUTTONS_MARGIN;
		viewmode->list[i].color = BUTTON_COLOR;
		viewmode->list[i].hover_color = BUTTON_HOVER_COLOR;
		viewmode->list[i].ishover.bool = 0;
		i++;
	}
	set_buttons_action_functions(viewmode->list);
	return (GOOD);
}
