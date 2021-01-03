/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clicked_viewmode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:30:02 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/02 20:42:50 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		game_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == GAME_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = GAME_VIEWMODE;
	return (GOOD);
}

int		editor_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == EDITOR_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = EDITOR_VIEWMODE;
	return (GOOD);
}

int		unlit_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == UNLIT_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = UNLIT_VIEWMODE;
	return (GOOD);
}

int		iteration_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == ITERATION_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = ITERATION_VIEWMODE;
	return (GOOD);
}

int		normal_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == NORMAL_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = NORMAL_VIEWMODE;
	return (GOOD);
}
