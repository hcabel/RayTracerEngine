/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clicked_viewmode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:30:02 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/03 11:39:52 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		game_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == GAME_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = GAME_VIEWMODE;
	ft_printf("{g}Game viewmode\n{/}");
	return (GOOD);
}

int		editor_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == EDITOR_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = EDITOR_VIEWMODE;
	ft_printf("{g}Editor viewmode\n{/}");
	return (GOOD);
}

int		unlit_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == UNLIT_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = UNLIT_VIEWMODE;
	ft_printf("{g}Unlit viewmode\n{/}");
	return (GOOD);
}

int		iteration_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == ITERATION_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = ITERATION_VIEWMODE;
	ft_printf("{g}Iteration viewmode\n{/}");
	return (GOOD);
}

int		normal_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == NORMAL_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = NORMAL_VIEWMODE;
	ft_printf("{g}Normal viewmode\n{/}");
	return (GOOD);
}
