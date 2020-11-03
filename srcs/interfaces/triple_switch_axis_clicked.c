/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triple_switch_axis_clicked.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 10:23:22 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/03 10:48:18 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_transphorm_axis_x(t_info *info)
{
	if (info->scene.transphorm_axis != 'x')
	{
		info->screen.details.triple_switch_axis.selected_button = 1;
		info->scene.transphorm_axis = 'x';
	}
	else
	{
		info->screen.details.triple_switch_axis.selected_button = 0;
		info->scene.transphorm_axis = 0;
	}
	return (GOOD);
}

int		set_transphorm_axis_y(t_info *info)
{
	if (info->scene.transphorm_axis != 'y')
	{
		info->screen.details.triple_switch_axis.selected_button = 2;
		info->scene.transphorm_axis = 'y';
	}
	else
	{
		info->screen.details.triple_switch_axis.selected_button = 0;
		info->scene.transphorm_axis = 0;
	}
	return (GOOD);
}

int		set_transphorm_axis_z(t_info *info)
{
	if (info->scene.transphorm_axis != 'z')
	{
		info->screen.details.triple_switch_axis.selected_button = 3;
		info->scene.transphorm_axis = 'z';
	}
	else
	{
		info->screen.details.triple_switch_axis.selected_button = 0;
		info->scene.transphorm_axis = 0;
	}
	return (GOOD);
}
