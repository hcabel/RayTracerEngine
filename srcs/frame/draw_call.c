/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:47:20 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/25 11:52:03 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_calls_execution(t_info *info)
{
	int	i;

	i = 0;
	while (i < UPGRADE_FUNCTION_AMOUNT)
	{
		if (info->update_function_list[i] != NULL)
			info->update_function_list[i](info);
		i++;
	}
}

void	draw_calls_clear_list(t_info *info)
{
	int	i;

	i = 0;
	while (i < UPGRADE_FUNCTION_AMOUNT)
	{
		info->update_function_list[i] = NULL;
		i++;
	}
}

void	draw_calls_add(t_info *info, void (*new)(t_info *info))
{
	int	i;

	i = 0;
	while (i < UPGRADE_FUNCTION_AMOUNT)
	{
		if (info->update_function_list[i] == NULL)
			break ;
		else
			i++;
	}
	info->update_function_list[i] = new;
}
