/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:47:20 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/06 12:50:09 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_calls_execution(t_info *info)
{
	void	(*current)(t_info *info);
	int		i;

	i = 0;
	while (i < MAX_DRAWCALL)
	{
		if (info->update_function_list[i] != NULL)
		{
			current = info->update_function_list[i];
			info->update_function_list[i] = NULL;
			current(info);
		}
		i++;
	}
}

void	draw_calls_clear_list(t_info *info)
{
	int	i;

	i = 0;
	while (i < MAX_DRAWCALL)
	{
		info->update_function_list[i] = NULL;
		i++;
	}
}

void	draw_calls_add(t_info *info, void (*new)(t_info *info))
{
	int	i;

	i = 0;
	while (i < MAX_DRAWCALL)
	{
		if (info->update_function_list[i] == NULL
			|| info->update_function_list[i] == new)
			break ;
		else
			i++;
	}
	if (info->update_function_list[i] == NULL)
		info->update_function_list[i] = new;
}
