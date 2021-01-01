/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_left_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:50:46 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/29 12:10:37 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		init_left_panel(t_left_panel *panel)
{
	panel->area.x = 0;
	panel->area.y = TOP_PANEL_SIZE;
	panel->area.w = LEFT_PANEL_SIZE;
	panel->area.h = WIN_HEIGTH - TOP_PANEL_SIZE;

	return (GOOD);
}