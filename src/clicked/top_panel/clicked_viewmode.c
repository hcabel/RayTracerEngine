/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clicked_viewmode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:30:02 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/31 13:23:46 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		viewmode_button_1_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == 0)
		return (FAILED);
	info->scene.cam.viewmode = 0;
	return (GOOD);
}

int		viewmode_button_2_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == 1)
		return (FAILED);
	info->scene.cam.viewmode = 1;
	return (GOOD);
}

int		viewmode_button_3_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == 2)
		return (FAILED);
	info->scene.cam.viewmode = 2;
	return (GOOD);
}

int		viewmode_button_4_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == 3)
		return (FAILED);
	info->scene.cam.viewmode = 3;
	return (GOOD);
}

int		viewmode_button_5_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == 4)
		return (FAILED);
	info->scene.cam.viewmode = 4;
	return (GOOD);
}
