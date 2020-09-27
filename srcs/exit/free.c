/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:51:15 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/26 16:54:24 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_info_struct(t_info *info)
{
	if (info->scene.shapes_amount > 0)
		ft_memdel((void**)&info->scene.shapes);
	if (info->scene.light_amount > 0)
		ft_memdel((void**)&info->scene.lights);
}
