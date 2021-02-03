/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clicked_viewmode_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:35:48 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/29 14:43:36 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		distance_fog_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == DISTANCE_FOG_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = DISTANCE_FOG_VIEWMODE;
	ft_printf("{g}Distance fog viewmode\n{/}");
	return (GOOD);
}

int		direct_illumination_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == DIRECT_ILLUMINATION_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = DIRECT_ILLUMINATION_VIEWMODE;
	ft_printf("{g}Direct illumination viewmode\n{/}");
	return (GOOD);
}

int		global_illumination_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == GLOBAL_ILLUMINATION_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = GLOBAL_ILLUMINATION_VIEWMODE;
	ft_printf("{g}Global illumination viewmode\n{/}");
	return (GOOD);
}

int		glossy_illumination_viewmode_button_clicked(t_info *info)
{
	if (info->scene.cam.viewmode == GLOSSY_ILLUMINATION_VIEWMODE)
		return (FAILED);
	info->scene.cam.viewmode = GLOSSY_ILLUMINATION_VIEWMODE;
	ft_printf("{g}Glossy illumination viewmode\n{/}");
	return (GOOD);
}
