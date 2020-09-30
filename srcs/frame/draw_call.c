/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:47:20 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/30 14:06:33 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_calls_execution(t_info *info)
{
	int	i;

	i = 0;
	while (i < WIN_AREAS)
	{
		if (info->update_function_list[i] != NULL)
		{
			if ( info->update_function_list[i] == UPDATE_VIEWPORT)
			{
				pthread_create(&info->window_area_renderer, NULL,
					UPDATE_VIEWPORT, (void*)info);
			}
			else
				info->update_function_list[i](info);
		}
		i++;
	}
}

void	draw_calls_clear_list(t_info *info)
{
	int	i;

	i = 0;
	while (i < WIN_AREAS)
	{
		info->update_function_list[i] = NULL;
		i++;
	}
}

void	draw_calls_add(t_info *info, void (*new)(t_info *info))
{
	int	i;

	i = 0;
	while (i < WIN_AREAS)
	{
		if (info->update_function_list[i] == NULL)
			break ;
		else
			i++;
	}
	info->update_function_list[i] = new;
}
